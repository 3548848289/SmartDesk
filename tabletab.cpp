#include "tabletab.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QVBoxLayout>

TableTab::TableTab(QWidget *parent): AbstractTab(parent)
{

    tableWidget = new QTableWidget(this);
    // 创建垂直布局并将表格添加到布局中
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tableWidget);

    // 设置布局
    setLayout(layout);
    connect(tableWidget, &QAbstractItemView::clicked, [=](const QModelIndex &index){
        QString newText = QString("('%1','%2')").arg(index.row()).arg(index.column());
        emit dataToSend("chick " + newText);
    });

    connect(tableWidget, &QTableWidget::itemChanged, [=](QTableWidgetItem *item){
        QString newText = QString("内容改变：行%1，列%2，新内容：%3")
                          .arg(item->row()).arg(item->column()).arg(item->text());
        emit dataToSend("edited" + newText);

    });
}

void TableTab::setText(const QString &text)
{
    parseCSV(text);
}

QString TableTab::getText() const
{
    return toCSV();
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


QString TableTab::toCSV() const
{
    QString csvText;
    for (int i = 0; i < tableWidget->rowCount(); ++i) {
        for (int j = 0; j < tableWidget->columnCount(); ++j) {
            if (j > 0) csvText += ',';
            if (tableWidget->item(i, j)) {
                csvText += tableWidget->item(i, j)->text();
            }
        }
        csvText += '\n';
    }
    return csvText;
}

void TableTab::addRow()
{
    int rowCount = tableWidget->rowCount();
    tableWidget->insertRow(rowCount);
}

void TableTab::addColumn()
{
    int columnCount = tableWidget->columnCount();
    tableWidget->insertColumn(columnCount);
}

void TableTab::getEpolldata(QString data)
{
    // Clear existing data
    tableWidget->clearContents();
    tableWidget->setRowCount(0);    
    tableWidget->setColumnCount(5);  // 设置列数
    QStringList headers = {"Name", "ID", "Gender", "Age", "Address"};
    tableWidget->setHorizontalHeaderLabels(headers);

    // Each entry is separated by a newline
    QStringList entries = data.split("\n", Qt::SkipEmptyParts);

    tableWidget->setRowCount(entries.size());
    for (int row = 0; row < entries.size(); ++row) {
        QString entry = entries[row].trimmed();
        entry = entry.remove("('").remove("')");
        QStringList fields = entry.split("', '");
        if (fields.size() == 5) {
            tableWidget->setItem(row, 0, new QTableWidgetItem(fields[0]));
            tableWidget->setItem(row, 1, new QTableWidgetItem(fields[1]));
            tableWidget->setItem(row, 2, new QTableWidgetItem(fields[2]));
            tableWidget->setItem(row, 3, new QTableWidgetItem(fields[3]));
            tableWidget->setItem(row, 4, new QTableWidgetItem(fields[4]));
        }
    }
}

void TableTab::getEpolllight(QString data)
{
    int row = 0, column = 0;
    sscanf(data.toStdString().c_str(), "chick ('%d','%d')", &row, &column);

    if (row >= 0 && row < tableWidget->rowCount() && column >= 0 && column < tableWidget->columnCount())
    {
        QTableWidgetItem *item = tableWidget->item(row, column);
        if (item)
            item->setBackground(Qt::yellow);
    }
    else
        qDebug() << "Invalid data: (" << row << ", " << column << ")";
}
