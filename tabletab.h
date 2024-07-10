// tabletab.h
#ifndef TABLETAB_H
#define TABLETAB_H

#include "abstracttab.h"
#include <QTableWidget>
#include <QString>
#include <QLabel>
#include <map>

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

    void getEpolldata(QString data);
    void getEpolllight(QString data);
    void clearHighlight(QString data);

signals:
    void dataToSend(const QString &data);


protected:

private:
    int foucsRow = 0;
    int foucsCol = 0;
    bool link = false;

    QTableWidget *tableWidget;
    QLabel *highlightLabel;
    std::map<std::pair<int, int>, QColor> originalColors;

    void parseCSV(const QString &csvText);
    QString toCSV() const;
};

#endif // TABLETAB_H
