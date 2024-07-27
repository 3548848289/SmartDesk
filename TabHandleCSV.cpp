#include "TabHandleCSV.h"

TableTab::TableTab(QWidget *parent): TabAbstract(parent)
{

    highlightLabel = new QLabel(this);
    tableWidget = new QTableWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tableWidget);

    setLayout(layout);
    connect(tableWidget, &QAbstractItemView::clicked, [=](const QModelIndex &index){
        foucsRow = index.row();
        foucsCol = index.column();
        QString newText = QString("(%1,%2)").arg(foucsRow).arg(foucsCol);
        if (link)
            emit dataToSend("chick" + newText);
    });

    connect(tableWidget, &QTableWidget::itemChanged, [=](QTableWidgetItem *item){

        QString newText = QString("%1,%2,%3,%4")
                              .arg(item->row()).arg(item->column()).arg(item->text().length()).arg(item->text());

        qDebug() << "编辑函数启动了" << newText;
        adjustItem(item);
        if (link)
            emit dataToSend("edited," + newText);
    });

    connect(tableWidget, &QTableWidget::itemSelectionChanged, [=](){
        QString newText = QString("(%1,%2)").arg(foucsRow).arg(foucsCol);
        if (link)
            emit dataToSend("clear" + newText);
    });


}

void TableTab::setText(const QString &text)
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

void TableTab::loadFromFile(const QString &fileName)
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


QString TableTab::getText() const
{
    return toCSV();
}

void TableTab::setLinkStatus(bool status)
{
    this->link = status;
}


void TableTab::saveToFile(const QString &fileName)
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

void TableTab::loadFromContent(const QByteArray &content)
{
    setText(QString::fromUtf8(content));
}

QString TableTab::toCSV() const
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

void TableTab::adjustItem(QTableWidgetItem *item)
{
    tableWidget->blockSignals(true);
    item->setData(Qt::UserRole, "127.0.0.1");
    tableWidget->blockSignals(false);
    QVariant userData = item->data(Qt::UserRole);

    if (userData.isValid()) {
        QString userString = userData.toString();
        qDebug() << "成功获取到的用户数据：" << userString;
    } else {
        qDebug() << "数据无效，可能是因为没有设置过或其他原因";
    }
}

void TableTab::addRow()
{
    int rowCount = tableWidget->rowCount();
    tableWidget->insertRow(rowCount);
}

void TableTab::addColumn()
{
    bool ok;
    QString columnName = QInputDialog::getText(this, tr("New Column"), tr("Enter column name:"), QLineEdit::Normal, "", &ok);

    if (ok && !columnName.isEmpty()) {
        int columnCount = tableWidget->columnCount();
        tableWidget->insertColumn(columnCount);
        tableWidget->setHorizontalHeaderItem(columnCount, new QTableWidgetItem(columnName));
    }
}


void TableTab::deleteRow()
{
    int currentRow = tableWidget->currentRow();
    if (currentRow != -1) {
        tableWidget->removeRow(currentRow);
    } else {
        QMessageBox::warning(this, tr("Error"), tr("No row selected."));
    }
}

void TableTab::deleteColumn()
{
    int currentColumn = tableWidget->currentColumn();
    if (currentColumn != -1) {
        tableWidget->removeColumn(currentColumn);
    } else {
        QMessageBox::warning(this, tr("Error"), tr("No column selected."));
    }
}

void TableTab::ReadfromServer(QString data)
{
    tableWidget->clear();
    QStringList lines = data.split("\n", Qt::SkipEmptyParts);

    if (lines.isEmpty())
        return;

    QStringList headers = lines.first().trimmed().split(",", Qt::SkipEmptyParts);
    int columnCount = headers.size();
    tableWidget->setColumnCount(columnCount);
    tableWidget->setHorizontalHeaderLabels(headers);

    // Exclude header line from data
    QString csvText = lines.mid(1).join("\n");

    // Reuse parseCSV function to populate table
    parseCSV(csvText);
}

void TableTab::parseCSV(const QString &csvText)
{
    tableWidget->clear();
    QStringList rows = csvText.split('\n');
    tableWidget->setRowCount(rows.size());
    for (int i = 0; i < rows.size(); ++i) {
        QStringList cols = rows[i].split(',');
        tableWidget->setColumnCount(qMax(tableWidget->columnCount(), cols.size()));
        for (int j = 0; j < cols.size(); ++j) {
            tableWidget->setItem(i, j, new QTableWidgetItem(cols[j]));
        }
    }
}


void TableTab::ChickfromServer(QString data)
{
    int row = 0, column = 0;
    sscanf(data.toStdString().c_str(), "chick (%d,%d)", &row, &column);
    qDebug() << "chick data: (" << row << ", " << column << ")";

    if (row >= 0 && row < tableWidget->rowCount() && column >= 0 && column < tableWidget->columnCount())
    {
        QTableWidgetItem *item = tableWidget->item(row, column);

        if (item)
        {
            tableWidget->blockSignals(true);
            item->setBackground(QColor(0, 120, 215));
            item->setData(Qt::UserRole, "127.0.0.1");
            tableWidget->blockSignals(false);
        }
    }
    else
        qDebug() << "Invalid data: (" << row << ", " << column << ")";
}

void TableTab::clearfromServer(QString data)
{
    int row = 0, column = 0;
    sscanf(data.toStdString().c_str(), "clear (%d,%d)", &row, &column);
    qDebug() << "clear data: (" << row << ", " << column << ")";

    if (row >= 0 && row < tableWidget->rowCount() && column >= 0 && column < tableWidget->columnCount())
    {
        QTableWidgetItem *item = tableWidget->item(row, column);
        if (item) {
            tableWidget->blockSignals(true);
            item->setBackground(Qt::transparent);
            item->setData(Qt::UserRole, "127.0.0.1");
            tableWidget->blockSignals(false);
       }
    }
}

void TableTab::editedfromServer(QString data)
{

    int row, col;
    char newValue[256];
    sscanf(data.toStdString().c_str(), "edited(%d,%d,%10s", &row, &col, newValue);

    // 更新QTableWidget中的相应单元格内容
    if (row >= 0 && row < tableWidget->rowCount() && col >= 0 && col < tableWidget->columnCount()) {
        QTableWidgetItem *item = tableWidget->item(row, col);
        if (!item) {
            item = new QTableWidgetItem();
            qDebug() << "这里原因";
            tableWidget->setItem(row, col, item);
        }
        item->setText(newValue);
        adjustItem(item);
    } else {
        qDebug() << "Invalid row or column index";
    }
}
