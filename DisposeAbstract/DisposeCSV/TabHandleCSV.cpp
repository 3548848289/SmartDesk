#include "TabHandleCSV.h"

TabHandleCSV::TabHandleCSV(const QString& filePath, QWidget *parent): TabAbstract(filePath, parent)
{

    QSplitter* splitter;
    highlightLabel = new QLabel(this);
    tableWidget = new QTableWidget(this);
    tableWidget->setSortingEnabled(true);
    tableWidget->horizontalHeader()->setSortIndicatorShown(true);

    splitter = new QSplitter(Qt::Vertical, this);

    controlwidget = new ControlWidCSV(this);
    connect(controlwidget, &ControlWidCSV::addRowClicked, this, &TabHandleCSV::addRow);
    connect(controlwidget, &ControlWidCSV::deleteRowClicked, this, &TabHandleCSV::deleteRow);
    connect(controlwidget, &ControlWidCSV::addColumnClicked, this, &TabHandleCSV::addColumn);
    connect(controlwidget, &ControlWidCSV::deleteColumnClicked, this, &TabHandleCSV::deleteColumn);

    splitter->addWidget(tableWidget);
    splitter->addWidget(controlwidget);
    splitter->setSizes({700, 100});
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(splitter);

    setLayout(layout);

    connect(tableWidget, &QAbstractItemView::clicked, this, [=](const QModelIndex &index){
        int row = index.row();
        int col = index.column();

        QTableWidgetItem *item = tableWidget->item(row, col);
        if (item && item->data(Qt::UserRole + 1).toBool()) {
            return;
        }

        foucsRow = row;
        foucsCol = col;

        QString jsonString = myJson::constructJson(localIp, "chick", foucsRow, foucsCol, "");
        if (link)
            emit dataToSend(jsonString);
    });


    connect(tableWidget, &QTableWidget::itemChanged, [=](QTableWidgetItem *item){
        adjustItem(item);
        QString jsonString = myJson::constructJson(localIp, "edited",item->row(), item->column(), item->text());
        if (link)
            emit dataToSend(jsonString);
        setContentModified(true);

    });

    connect(tableWidget, &QTableWidget::itemSelectionChanged, [=](){
        QString jsonString = myJson::constructJson(localIp, "clear",foucsRow, foucsCol, "");
        if (link)
            emit dataToSend(jsonString);
    });
}

void TabHandleCSV::setContent(const QString &text)
{
    tableWidget->clearContents();
    tableWidget->setRowCount(0);

    QStringList rows = text.split('\n', Qt::SkipEmptyParts);
    if (rows.isEmpty())
        return;

    int rowCount = rows.size();
    int colCount = rows.first().split(',').size();

    tableWidget->setColumnCount(colCount);
    tableWidget->setRowCount(rowCount);

    for (int i = 0; i < rowCount; ++i) {
        QStringList cols = rows[i].split(',');
        for (int j = 0; j < colCount; ++j) {
            QString value = (j < cols.size()) ? cols[j] : "";
            tableWidget->setItem(i, j, new QTableWidgetItem(value));
        }
    }

}

void TabHandleCSV::loadFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        setContent(in.readAll());
        file.close();
    } else {
        QMessageBox::warning(this, tr("错误"), tr("无法打开文件"));
    }
    setContentModified(false);

}

QString TabHandleCSV::getContent() const
{
    return toCSV();
}

void TabHandleCSV::setLinkStatus(bool status)
{
    link = status;
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    foreach (const QNetworkInterface &interface, interfaces) {
        QList<QNetworkAddressEntry> entries = interface.addressEntries();
        foreach (const QNetworkAddressEntry &entry, entries) {
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol && !entry.ip().toString().startsWith("127.")) {
                localIp = entry.ip().toString();
                return;
            }
        }
    }
}

bool TabHandleCSV::getLinkStatus()
{
    return link;
}

void TabHandleCSV::saveToFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << getContent();
        file.close();
    } else {
        QMessageBox::warning(this, tr("错误"), tr("无法保存文件"));
    }
}

void TabHandleCSV::loadFromInternet(const QByteArray &content)
{
    setContent(QString::fromUtf8(content));
}

QString TabHandleCSV::toCSV() const
{
    QString csvText;

    int rowCount = tableWidget->rowCount();
    int colCount = tableWidget->columnCount();

    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < colCount; ++j) {
            if (j > 0)
                csvText += ',';

            QTableWidgetItem *item = tableWidget->item(i, j);
            if (item) {
                QString cellText = item->text();
                // // 若内容包含逗号或引号，需要转义为 CSV 合法格式
                // if (cellText.contains(',') || cellText.contains('"')) {
                //     cellText.replace("\"", "\"\"");  // 转义引号
                //     cellText = "\"" + cellText + "\"";  // 加上外层引号
                // }
                csvText += cellText;
            }
        }
        csvText += '\n';
    }

    return csvText;
}


void TabHandleCSV::adjustItem(QTableWidgetItem *item)
{
    tableWidget->blockSignals(true);
    item->setData(Qt::UserRole, "127.0.0.1");
    tableWidget->blockSignals(false);
    QVariant userData = item->data(Qt::UserRole);

    if (userData.isValid()) {
        QString userString = userData.toString();
//        qDebug() << "成功获取到的用户数据：" << userString;
    } else {
        qDebug() << "数据无效，可能是因为没有设置过或其他原因";
    }
}

void TabHandleCSV::addRow()
{
    int rowCount = tableWidget->rowCount();
    int currentRow = tableWidget->currentRow();
    if (currentRow == -1)
        tableWidget->insertRow(rowCount);
    else
        tableWidget->insertRow(currentRow + 1);
    setContentModified(true);
}


void TabHandleCSV::addColumn()
{
    bool ok;
    QString columnName = QInputDialog::getText(this, tr("New Column"), tr("Enter column name:"), QLineEdit::Normal, "", &ok);

    if (ok && !columnName.isEmpty()) {
        int columnCount = tableWidget->columnCount();
        tableWidget->insertColumn(columnCount);
        tableWidget->setHorizontalHeaderItem(columnCount, new QTableWidgetItem(columnName));
        setContentModified(true);
    }
}

void TabHandleCSV::deleteRow()
{
    int currentRow = tableWidget->currentRow();
    if (currentRow != -1) {
        tableWidget->removeRow(currentRow);
        setContentModified(true);
    } else {
        QMessageBox::warning(this, tr("警告"), tr("没选择行"));
    }
}

void TabHandleCSV::deleteColumn()
{
    int currentColumn = tableWidget->currentColumn();
    if (currentColumn != -1) {
        tableWidget->removeColumn(currentColumn);
        setContentModified(true);
    } else {
        QMessageBox::warning(this, tr("警告"), tr("没选择列"));
    }
}


void TabHandleCSV::ReadfromServer(const QJsonObject& jsonObj)
{
    if (!jsonObj.contains("object") || !jsonObj["object"].isString()) {
        qDebug() << "Invalid JSON format for read operation.";
        return;
    }

    QString csvData = jsonObj["object"].toString();
    tableWidget->clear();

    QStringList lines = csvData.split("\n", Qt::SkipEmptyParts);
    if (lines.isEmpty())
        return;

    tableWidget->blockSignals(true);

    // 设置表头
    QStringList headers = lines.first().trimmed().split(",", Qt::SkipEmptyParts);
    int columnCount = headers.size();
    tableWidget->setColumnCount(columnCount);
    tableWidget->setHorizontalHeaderLabels(headers);

    // 解析CSV数据，忽略表头
    QString csvText = lines.mid(1).join("\n");
    parseCSV(csvText);
    tableWidget->blockSignals(false);

}

void TabHandleCSV::parseCSV(const QString &csvText)
{
    tableWidget->clear();
    QStringList rows = csvText.split('\n');
    tableWidget->setRowCount(rows.size());
    for (int i = 0; i < rows.size(); ++i)
    {
        QStringList cols = rows[i].split(',');
        tableWidget->setColumnCount(qMax(tableWidget->columnCount(), cols.size()));
        for (int j = 0; j < cols.size(); ++j)
            tableWidget->setItem(i, j, new QTableWidgetItem(cols[j]));
    }
}

void TabHandleCSV::ChickfromServer(const QJsonObject& jsonObj)
{
    auto [ip, row, col, newValue] = myJson::extract_common_fields(jsonObj);
    if (row >= 0 && row < tableWidget->rowCount() && col >= 0 && col < tableWidget->columnCount()) {
        QTableWidgetItem *item = tableWidget->item(row, col);
        if (item) {
            tableWidget->blockSignals(true);
            item->setBackground(QColor(0, 120, 215)); // 远程编辑颜色
            item->setData(Qt::UserRole, ip.value_or("unknown"));  // Store IP
            item->setData(Qt::UserRole + 1, true);  // 设置正在被远程编辑的标志
            item->setToolTip(QString("正在被 %1 编辑中").arg(ip.value_or("unknown")));
            // tableWidget->clearSelection();
            tableWidget->blockSignals(false);
        }
    } else {
        qDebug() << "Invalid row or column index: (" << row << ", " << col << ")";
    }
}

void TabHandleCSV::clearfromServer(const QJsonObject& jsonObj)
{
    auto [ip, row, col, newValue] = myJson::extract_common_fields(jsonObj);
    if (row >= 0 && row < tableWidget->rowCount() && col >= 0 && col < tableWidget->columnCount()) {
        QTableWidgetItem *item = tableWidget->item(row, col);
        if (item) {
            tableWidget->blockSignals(true);
            item->setBackground(Qt::transparent); // 或使用白色 QColor(Qt::white)
            item->setData(Qt::UserRole + 1, false);  // 取消远程编辑标志
            item->setToolTip("");
            tableWidget->blockSignals(false);
        }
    } else {
        qDebug() << "Invalid row or column index: (" << row << ", " << col << ")";
    }
}


void TabHandleCSV::editedfromServer(const QJsonObject& jsonObj)
{
    auto [ip, row, col, newValue] = myJson::extract_common_fields(jsonObj);
    if (row >= 0 && row < tableWidget->rowCount() && col >= 0 && col < tableWidget->columnCount()) {
        QTableWidgetItem *item = tableWidget->item(row, col);
        if (!item) {
            item = new QTableWidgetItem();
            tableWidget->setItem(row, col, item);
        }
        item->setText(newValue.value());
        adjustItem(item);
    } else {
        qDebug() << "Invalid row or column index: (" << row << ", " << col << ")";
    }
}


void TabHandleCSV::findNext(const QString &str, Qt::CaseSensitivity cs)
{
    bool found = false;
    int rowCount = tableWidget->rowCount();
    int colCount = tableWidget->columnCount();

    QTableWidgetItem *currentItem = tableWidget->currentItem();
    if (!currentItem) return;

    int currentRow = currentItem->row();
    int currentCol = currentItem->column();

    for (int row = currentRow; row < rowCount; ++row) {
        for (int col = (row == currentRow ? currentCol + 1 : 0); col < colCount; ++col) {
            QTableWidgetItem *item = tableWidget->item(row, col);
            if (item && item->text().contains(str, cs)) {
                tableWidget->setCurrentItem(item);
                found = true;
                break;
            }
        }
        if (found) break;
    }

    if (!found) {
        for (int row = 0; row <= currentRow; ++row) {
            for (int col = 0; col < (row == currentRow ? currentCol : colCount); ++col) {
                QTableWidgetItem *item = tableWidget->item(row, col);
                if (item && item->text().contains(str, cs)) {
                    tableWidget->setCurrentItem(item);
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
    }

    if (!found) {
        QMessageBox::information(this, tr("查找"), tr("找不到此单词"));
    }
}

void TabHandleCSV::findAll(const QString &str, Qt::CaseSensitivity cs)
{
    bool found = false;
    int rowCount = tableWidget->rowCount();
    int colCount = tableWidget->columnCount();

    // 遍历所有单元格，查找匹配项
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            QTableWidgetItem *item = tableWidget->item(row, col);
            if (item && item->text().contains(str, cs == Qt::CaseInsensitive ? Qt::CaseInsensitive : Qt::CaseSensitive)) {
                // 找到匹配项，设置高亮
                item->setForeground(QBrush(Qt::red));
                found = true;
            }
        }
    }

    if (!found)
        QMessageBox::information(this, tr("查找"), tr("找不到此单词"));

}

void TabHandleCSV::clearHighlight()
{

    int rowCount = tableWidget->rowCount();
    int colCount = tableWidget->columnCount();

    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            QTableWidgetItem *item = tableWidget->item(row, col);
            if (item) {
                item->setForeground(QBrush());  // 使用默认字体色
            }
        }
    }
}


