#include "TabHandleXLSX.h"
#include "xlsxdocument.h"

TabHandleXLSX::TabHandleXLSX(const QString& filePath, QWidget *parent): TabAbstract(filePath, parent)
{
    tableWidget = new QTableWidget(this);
    tableWidget->setSortingEnabled(true);
    tableWidget->horizontalHeader()->setSortIndicatorShown(true);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(tableWidget);
    layout->setContentsMargins(0, 0, 0, 0);  // 可选：去除边距
    this->setLayout(layout);
}

void TabHandleXLSX::loadFromFile(const QString &fileName)
{
    QXlsx::Document xlsx(fileName);

    int maxRow = 0;
    int maxCol = 0;

    // 预扫一遍，找到最大行列
    for (int row = 1; row <= 1000; ++row) {
        for (int col = 1; col <= 100; ++col) {
            if (xlsx.cellAt(row, col)) {
                maxRow = qMax(maxRow, row);
                maxCol = qMax(maxCol, col);
            }
        }
    }

    tableWidget->setRowCount(maxRow);
    tableWidget->setColumnCount(maxCol);

    for (int row = 1; row <= maxRow; ++row) {
        for (int col = 1; col <= maxCol; ++col) {
            QVariant value = xlsx.read(row, col);
            if (!value.isNull()) {
                tableWidget->setItem(row - 1, col - 1, new QTableWidgetItem(value.toString()));
            }
        }
    }
    setContentModified(false);

}

void TabHandleXLSX::ControlWidget(QWidget *WControl)
{

}

void TabHandleXLSX::setContent(const QString &text)
{

}

QString TabHandleXLSX::getContent() const
{

}



void TabHandleXLSX::saveToFile(const QString &fileName)
{

}

void TabHandleXLSX::loadFromInternet(const QByteArray &content)
{

}

