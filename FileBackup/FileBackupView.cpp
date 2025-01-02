#include "include/FileBackupView.h"
#include "ui/ui_FileBackupView.h"

FileBackupView::FileBackupView(QWidget *parent)
    : QWidget(parent), ui(new Ui::FileBackupView)
    , serverManager(ServerManager::instance())
    , dbservice(dbService::instance("../SmartDesk.db"))
{
    ui->setupUi(this);
    ui->backupList->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(serverManager, &ServerManager::onFilesListUpdated, this, &FileBackupView::updateFileList);
    loadFileNames();
}

FileBackupView::~FileBackupView()
{
    delete ui;
}


void FileBackupView::loadFileNames()
{
    QList<QString> fileNames = dbservice.dbBackup().getAllFileNames();
    QList<QString> missingFiles;

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

void FileBackupView::on_fileListComboBox_currentIndexChanged(int index)
{
    if (index != -1) {
        if (ui->fileListComboBox->itemData(index) == "missing") {
            QMessageBox::warning(this, "文件缺失", "您选择的文件已经缺失，请选择其他文件。");
        }
        choosed_file = ui->fileListComboBox->currentText();
        QList<QString> backupFileNames = dbservice.dbBackup().getBackupFileNames(choosed_file);
        ui->backupList->clear();

        QIcon missingIcon = QIcon::fromTheme("dialog-warning", QIcon(":/usedimage/tips.png"));

        for (QString &backupFileName : backupFileNames) {
            QFileInfo fileInfo(backupFileName);
            QString fileNameOnly = fileInfo.fileName();
            QListWidgetItem *item = new QListWidgetItem(fileNameOnly);

            bool fileMissing = false;

            if (!fileInfo.exists()) {
                backupFileName = "文件已缺失，请更改路径或者删除记录";
                item->setIcon(missingIcon);
                fileMissing = true;
            }

            item->setData(Qt::UserRole, fileMissing ? QString() : backupFileName);
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
            } else {
                qDebug() << "Failed to update file path in database.";
            }
        }

    }
    else if (msgBox.clickedButton() == deleteButton) {
        if (dbservice.dbBackup().deleteAll(choosed_file)) {
            ui->fileListComboBox->removeItem(index);
        } else {
            qDebug() << "Failed to delete file record from database.";
        }

    } else {
        msgBox.close();
    }
}


void FileBackupView::on_backupList_customContextMenuRequested(const QPoint &pos)
{
    QListWidgetItem *item = ui->backupList->itemAt(pos);
    if (item) {
        QString file = item->data(Qt::UserRole).toString();

        // 如果文件路径为空或文件不存在，禁用 "预览" 和 "还原"，并提供 "更换路径" 和 "删除" 功能
        bool isMissingFile = file.isEmpty() || !QFile::exists(file);

        QMenu contextMenu(this);
        QAction *actionEdit = contextMenu.addAction("预览");
        QAction *actionRestore = contextMenu.addAction("还原");
        QAction *actionReplace = contextMenu.addAction("更换路径");
        QAction *actionDelete = contextMenu.addAction("删除记录");

        if (isMissingFile) {
            actionEdit->setEnabled(false);
            actionRestore->setEnabled(false);
        } else {
            connect(actionEdit, &QAction::triggered, this, [this, item, file]() {
                emit s_fileopen(file);
            });
            connect(actionRestore, &QAction::triggered, this, [this, item, file]() {
                file_restore_wid = new FileRestoreWid(file, this);
                file_restore_wid->exec();
            });
        }

        connect(actionReplace, &QAction::triggered, this, [this, item, file]() {
            QString newFilePath = QFileDialog::getOpenFileName(this, tr("选择文件"), "", tr("所有文件 (*.*)"));
            if (!newFilePath.isEmpty()) {
                dbservice.dbBackup().updateFilePath(file, newFilePath);
                item->setData(Qt::UserRole, newFilePath);
                item->setText(QFileInfo(newFilePath).fileName());
            }
        });

        connect(actionDelete, &QAction::triggered, this, [this, item, file]() {
            if (dbservice.dbBackup().deleteBackupRecord(file)) {
                if (deleteBackupFile(file)) {
                    delete item;
                } else {
                    qDebug() << "Failed to delete backup file:" << file;
                }
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

