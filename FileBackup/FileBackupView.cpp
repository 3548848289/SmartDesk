#include "include/FileBackupView.h"
#include "ui/ui_FileBackupView.h"

FileBackupView::FileBackupView(QWidget *parent) : QWidget(parent), ui(new Ui::FileBackupView)
    , serverManager(ServerManager::instance()) , dbservice(dbService::instance("./SmartDesk.db")) {
    ui->setupUi(this);
    ui->backupList->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->fileListComboBox->setMinimumContentsLength(20);

    connect(serverManager, &ServerManager::onFilesListUpdated, this, &FileBackupView::updateFileList);

    connect(serverManager, &ServerManager::returnStatus, this, [this](bool exists) {
        this->exists = exists;
    });
    loadFileNames();
}

FileBackupView::~FileBackupView()
{
    delete ui;
}

void FileBackupView::loadFileNames()
{
    ui->fileListComboBox->clear();
    ui->backupList->clear();
    QList<QString> fileNames = dbservice.dbBackup().getAllFileNames();
    for (const QString &filePath : fileNames) {
        if (QFile::exists(filePath)) {
            ui->fileListComboBox->addItem(filePath, filePath);
        } else {
            QIcon missingIcon = QIcon::fromTheme(
                "dialog-warning", QIcon(":/usedimage/tips.png"));
            ui->fileListComboBox->addItem(missingIcon, filePath, filePath);
            int itemIndex = ui->fileListComboBox->count() - 1;
            ui->fileListComboBox->setItemData(itemIndex, "missing", Qt::UserRole);
        }
    }
}

void FileBackupView::updateFileList(const QString filepath)
{
    int index = ui->fileListComboBox->findText(filepath);
    if (index != -1)
        ui->fileListComboBox->setCurrentIndex(index);
    else
        qDebug() << "File not found in the combobox.";
}

void FileBackupView::on_fileListComboBox_currentIndexChanged(int index) {
    if (index != -1) {
        if (ui->fileListComboBox->itemData(index) == "missing") {
            QMessageBox::warning(this, "文件缺失", "您选择的文件已经缺失，请更改源文件路径或选择其他文件。");
        }
        choosed_file = ui->fileListComboBox->currentText();
        ui->fileListComboBox->setToolTip(choosed_file);
        QList<QString> backupFileNames = dbservice.dbBackup().getBackupFileNames(choosed_file);
        ui->backupList->clear();

        QIcon missingIcon = QIcon::fromTheme("dialog-warning", QIcon(":/usedimage/tips.png"));

        for (QString &backupFileName : backupFileNames) {

            QFileInfo fileInfo(backupFileName);
            QString fileNameOnly = fileInfo.fileName();
            serverManager->checkFileExists(fileNameOnly);
            QListWidgetItem *item = new QListWidgetItem(fileNameOnly);

            bool fileMissing = false;

            if (!fileInfo.exists()) {
                item->setIcon(missingIcon);
                fileMissing = true;
            }
            item->setData(Qt::UserRole, backupFileName);
            item->setData(Qt::UserRole + 1, fileMissing);
            item->setToolTip(fileMissing ? "文件已缺失" : backupFileName);
            ui->backupList->addItem(item);
        }

    }
}


void FileBackupView::on_backupList_itemClicked(QListWidgetItem *item)
{
    QString file = item->data(Qt::UserRole).toString();
    if (!file.isEmpty())
        emit s_fileopen(file);
}

void FileBackupView::on_pushButton_clicked()
{
    int index = ui->fileListComboBox->currentIndex();
    if (index == -1)
        return;

    QString currentFilePath = ui->fileListComboBox->currentData().toString();
    if (currentFilePath.isEmpty())
        return;

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("操作选择");
    msgBox.setText("您想执行以下哪个操作？");
    QPushButton *changePathButton = msgBox.addButton("更换文件路径", QMessageBox::YesRole);
    QPushButton *deleteButton = msgBox.addButton("删除文件记录", QMessageBox::NoRole);
    QPushButton *cancelButton = msgBox.addButton("取消", QMessageBox::RejectRole);

    msgBox.setDefaultButton(changePathButton);
    msgBox.exec();

    if (msgBox.clickedButton() == changePathButton) {
        QString newFilePath = QFileDialog::getOpenFileName(this, tr("选择新的文件路径"), "", tr("所有文件 (*.*)"));
        if (!newFilePath.isEmpty() && newFilePath != choosed_file) {
            if (dbservice.dbBackup().updateSubmissions(choosed_file, newFilePath)) {
                ui->fileListComboBox->setItemData(index, newFilePath);
                ui->fileListComboBox->setItemText(index, QFileInfo(newFilePath).fileName());
            } else
                QMessageBox::warning(this, "", tr("更新文件路径失败。"));
        }
    }

    else if (msgBox.clickedButton() == deleteButton) {
        QList<QString> backupFileNames = dbservice.dbBackup().getBackupFileList(choosed_file);
        if (dbservice.dbBackup().deleteAll(choosed_file)) {
            // 删除磁盘上的所有备份文件
            for (const QString &backupFile : backupFileNames) {
                deleteBackupFile(backupFile);  // 删除实际文件
            }

            ui->fileListComboBox->removeItem(index);
        } else {
            QMessageBox::warning(this, "", tr("从数据库中删除文件记录失败。"));
        }

        if (ui->fileListComboBox->count() == 0)
            ui->backupList->clear();
    }

    else {
        msgBox.close();
    }
}


void FileBackupView::on_backupList_customContextMenuRequested(const QPoint &pos)
{
    QListWidgetItem *item = ui->backupList->itemAt(pos);
    if (item) {
        QString file = item->data(Qt::UserRole).toString();
        qDebug() << "on_backupList_customContextMenuRequested:" << file;
        // 如果文件路径为空或文件不存在，禁用 "预览" 和 "还原"，并提供 "更换路径" 和 "删除" 功能
        bool isMissingFile = file.isEmpty() || !QFile::exists(file);

        QMenu contextMenu(this);
        QAction *actionEdit = contextMenu.addAction("预览");
        QAction *actionRestore = contextMenu.addAction("详情");
        QAction *actionReplace = contextMenu.addAction("更换路径");
        QAction *actionCommit = contextMenu.addAction("上传云端");
        QAction *actionRecover = contextMenu.addAction("从云端恢复");
        QAction *actionDelete = contextMenu.addAction("删除记录");

        if(exists)
            actionRecover->setEnabled(true);
        else
            actionRecover->setEnabled(false);

        if (isMissingFile) {
            actionEdit->setEnabled(false);
            // actionRestore->setEnabled(false);
            actionCommit->setEnabled(false);
        } else {
            connect(actionEdit, &QAction::triggered, this, [this, item, file]() {
                emit s_fileopen(file);
            });

        }
        connect(actionRestore, &QAction::triggered, this, [this, item, file, isMissingFile]() {
            file_restore_wid = new FileRestoreWid(file, isMissingFile, this);
            file_restore_wid->exec();
        });
        connect(actionReplace, &QAction::triggered, this, [this, item, file]() {
            QString newFilePath = QFileDialog::getOpenFileName(this, tr("选择文件"), "", tr("所有文件 (*.*)"));
            if (!newFilePath.isEmpty()) {
                dbservice.dbBackup().updateFilePath(file, newFilePath);
                item->setData(Qt::UserRole, newFilePath);
                item->setText(QFileInfo(newFilePath).fileName());
            }
        });

        connect(actionCommit, &QAction::triggered, this, [this, item, file]() {
            serverManager->commitFile(file);
        });

        connect(actionRecover, &QAction::triggered, this, [this, item, file]() {
            serverManager->downloadFile(file);

        });

        connect(actionDelete, &QAction::triggered, this, [this, item, file]() {
            if (dbservice.dbBackup().deleteBackupRecord(file)) {
                if (deleteBackupFile(file))
                    delete item;
                else
                    qDebug() << "Failed to delete backup file:" << file;
            }
        });
        contextMenu.exec(ui->backupList->mapToGlobal(pos));
    }
}


bool FileBackupView::deleteBackupFile(const QString &backupFilePath) {
    QFile file(backupFilePath);
    if (file.exists()) {
        if (file.remove()) {
            return true;
        } else {
            qDebug() << "Failed to delete file:" << backupFilePath;
            return false;
        }
    } else {
        qDebug() << "File does not exist:" << backupFilePath;
        return false;
    }
}


void FileBackupView::on_refreshBtn_clicked()
{
    loadFileNames();
}

