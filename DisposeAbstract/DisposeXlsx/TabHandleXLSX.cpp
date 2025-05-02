#include "TabHandleXLSX.h"
#include "xlsxdocument.h"

TabHandleXLSX::TabHandleXLSX(const QString& filePath, QWidget *parent)
    : TabAbstract(filePath, parent) {
    tableWidget = new QTableWidget(this);
    tableWidget->setSortingEnabled(true);
    tableWidget->horizontalHeader()->setSortIndicatorShown(true);
    tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    QSplitter *splitter = new QSplitter(Qt::Vertical, this);
    splitter->addWidget(tableWidget);
    splitter->setSizes({700, 100});

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(splitter);
    setLayout(layout);

    connect(tableWidget, &QTableWidget::itemChanged, this, [this]() {
        setContentModified(true);
    });
}

void TabHandleXLSX::setContent(const QString &text) {
    Q_UNUSED(text);
    QMessageBox::information(this, tr("Not supported"), tr("Direct text input is not supported for XLSX files."));
}

QString TabHandleXLSX::getContent() const {
    return tr("[XLSX table view]");
}

void TabHandleXLSX::loadFromFile(const QString &fileName) {
    QXlsx::Document xlsx(fileName);
    if (!QFile::exists(fileName) || !xlsx.load()) {
        QMessageBox::warning(this, tr("Error"), tr("Could not load Excel file."));
        return;
    }
    int maxRow = 0, maxCol = 0;
    for (int row = 1; row <= 1000; ++row)
        for (int col = 1; col <= 100; ++col)
            if (xlsx.cellAt(row, col)) {
                maxRow = qMax(maxRow, row);
                maxCol = qMax(maxCol, col);
            }
    tableWidget->setRowCount(maxRow);
    tableWidget->setColumnCount(maxCol);

    for (int row = 1; row <= maxRow; ++row) {
        for (int col = 1; col <= maxCol; ++col) {
            QVariant value = xlsx.read(row, col);
            if (!value.isNull())
                tableWidget->setItem(row - 1, col - 1, new QTableWidgetItem(value.toString()));
        }
    }
    setContentModified(false);
}

void TabHandleXLSX::saveToFile(const QString &fileName){
    QXlsx::Document xlsx;
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        for (int col = 0; col < tableWidget->columnCount(); ++col) {
            QTableWidgetItem *item = tableWidget->item(row, col);
            if (item && !item->text().isEmpty())
                xlsx.write(row + 1, col + 1, item->text());
        }
    }
    if (!xlsx.saveAs(fileName))
        QMessageBox::warning(this, tr("Save Error"), tr("Failed to save XLSX file."));
    else
        setContentModified(false);
}

void TabHandleXLSX::loadFromInternet(const QByteArray &content) {
    QString tempFilePath = QDir::temp().filePath("temp_internet.xlsx");    QFile tempFile(tempFilePath);
    if (tempFile.open(QIODevice::WriteOnly)) {
        tempFile.write(content);
        tempFile.close();
        loadFromFile(tempFilePath);
        tempFile.remove();
    } else
        QMessageBox::warning(this, tr("Error"), tr("Failed to write temporary file."));
}

void TabHandleXLSX::ControlWidget(QWidget* WControl) {
    Q_UNUSED(WControl);
    qDebug() << "TabHandleXLSX: Control panel slot called";
}
