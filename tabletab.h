// tabletab.h
#ifndef TABLETAB_H
#define TABLETAB_H

#include "abstracttab.h"
#include <QTableWidget>

class TableTab : public AbstractTab
{
    Q_OBJECT

public:
    explicit TableTab(QWidget *parent = nullptr);
    void setText(const QString &text) override;
    QString getText() const override;
    void loadFromFile(const QString &fileName) override;
    void saveToFile(const QString &fileName) override;
    void loadFromContent(const QByteArray &content) override;

    void addRow();
    void addColumn();


signals:
    void dataToSend(const QString &data); // Signal to send data

private:
    QTableWidget *tableWidget;
    void parseCSV(const QString &csvText);
    QString toCSV() const;

};

#endif // TABLETAB_H
