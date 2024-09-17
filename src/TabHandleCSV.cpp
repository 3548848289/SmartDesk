#include "TabHandleCSV.h"

TabHandleCSV::TabHandleCSV(QWidget *parent): TabAbstract(parent)
{
    highlightLabel = new QLabel(this);
    tableWidget = new QTableWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tableWidget);
    setLayout(layout);

    connect(tableWidget, &QAbstractItemView::clicked, [=](const QModelIndex &index){
        foucsRow = index.row();
        foucsCol = index.column();
        QString jsonString = myJson::constructJson(localIp, "chick",foucsRow, foucsCol, "");

        if (link)
            emit dataToSend(jsonString);
    });

    connect(tableWidget, &QTableWidget::itemChanged, [=](QTableWidgetItem *item){
        adjustItem(item);
        QString jsonString = myJson::constructJson(localIp, "edited",item->row(), item->column(), item->text());
        if (link)
            emit dataToSend(jsonString);
    });

    // 改变选中单元格时发送 clear 操作的 JSON 数据
    connect(tableWidget, &QTableWidget::itemSelectionChanged, [=](){
        QString jsonString = myJson::constructJson(localIp, "clear",foucsRow, foucsCol, "");
        if (link)
            emit dataToSend(jsonString);
    });
}


void TabHandleCSV::setText(const QString &text)
{
    tableWidget->clear();
    QStringList rows = text.split('\n');
    if (rows.isEmpty())
        return;

    QStringList headers = rows.first().split(',');    // 处理第一行作为表头
    tableWidget->setColumnCount(headers.size());
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->setRowCount(rows.size() - 1);        // 减去表头行

    int maxCols = 0;
    for (int i = 1; i < rows.size(); ++i) {
        QStringList cols = rows[i].split(',');
        tableWidget->setColumnCount(qMax(tableWidget->columnCount(), cols.size()));
        for (int j = 0; j < cols.size(); ++j) {
            tableWidget->setItem(i - 1, j, new QTableWidgetItem(cols[j]));
        }
        maxCols = qMax(maxCols, cols.size());
    }

    tableWidget->setColumnCount(maxCols);
}

void TabHandleCSV::loadFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        setText(in.readAll());
        file.close();
    } else {
        QMessageBox::warning(this, tr("Error"), tr("Could not open file"));
    }
}


QString TabHandleCSV::getText() const
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


void TabHandleCSV::saveToFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << getText();
        file.close();
    } else {
        QMessageBox::warning(this, tr("Error"), tr("Could not save file"));
    }
}

void TabHandleCSV::loadFromContent(const QByteArray &content)
{
    setText(QString::fromUtf8(content));
}

QString TabHandleCSV::toCSV() const
{
    QString csvText;
    for (int i = 0; i < tableWidget->rowCount(); ++i) {
        for (int j = 0; j < tableWidget->columnCount(); ++j) {
            if (j > 0)
                csvText += ',';
            if (tableWidget->item(i, j))
                csvText += tableWidget->item(i, j)->text();
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
    tableWidget->insertRow(rowCount);
}

void TabHandleCSV::addColumn()
{
    bool ok;
    QString columnName = QInputDialog::getText(this, tr("New Column"), tr("Enter column name:"), QLineEdit::Normal, "", &ok);

    if (ok && !columnName.isEmpty()) {
        int columnCount = tableWidget->columnCount();
        tableWidget->insertColumn(columnCount);
        tableWidget->setHorizontalHeaderItem(columnCount, new QTableWidgetItem(columnName));
    }
}

void TabHandleCSV::deleteRow()
{
    int currentRow = tableWidget->currentRow();
    if (currentRow != -1) {
        tableWidget->removeRow(currentRow);
    } else {
        QMessageBox::warning(this, tr("Error"), tr("No row selected."));
    }
}

void TabHandleCSV::deleteColumn()
{
    int currentColumn = tableWidget->currentColumn();
    if (currentColumn != -1) {
        tableWidget->removeColumn(currentColumn);
    } else {
        QMessageBox::warning(this, tr("Error"), tr("No column selected."));
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

    qDebug() << "chick data: (" << row << ", " << col << ")";

    if (row >= 0 && row < tableWidget->rowCount() && col >= 0 && col < tableWidget->columnCount()) {
        QTableWidgetItem *item = tableWidget->item(row, col);
        if (item) {
            tableWidget->blockSignals(true);
            item->setBackground(QColor(0, 120, 215));
            item->setData(Qt::UserRole, ip.value_or("unknown"));  // Store client IP
            tableWidget->blockSignals(false);
        }
    } else {
        qDebug() << "Invalid row or column index: (" << row << ", " << col << ")";
    }
}

void TabHandleCSV::clearfromServer(const QJsonObject& jsonObj)
{
    auto [ip, row, col, newValue] = myJson::extract_common_fields(jsonObj);
    qDebug() << "clear data: (" << row << ", " << col << ")";

    if (row >= 0 && row < tableWidget->rowCount() && col >= 0 && col < tableWidget->columnCount()) {
        QTableWidgetItem *item = tableWidget->item(row, col);
        if (item) {
            tableWidget->blockSignals(true);
            item->setBackground(Qt::transparent);
            item->setData(Qt::UserRole, ip.value_or("unknown"));  // Store client IP
            tableWidget->blockSignals(false);
        }
    } else {
        qDebug() << "Invalid row or column index: (" << row << ", " << col << ")";
    }
}

void TabHandleCSV::editedfromServer(const QJsonObject& jsonObj)
{
    auto [ip, row, col, newValue] = myJson::extract_common_fields(jsonObj);
    qDebug() << "Edited cell (" << row << ", " << col << ") with new value: " << newValue.value();

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
