// TabHandleCSV.h
#ifndef TABHANDLECSV_H
#define TABHANDLECSV_H

#include "TabAbstract.h"
#include "../manager/myJson.h"

#include <QTableWidget>
#include <QString>
#include <QLabel>
#include <map>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QTimer>
#include <regex>
#include <string>
#include <QInputDialog>
#include <QDebug>
#include <QNetworkInterface>

class TabHandleCSV : public TabAbstract
{
    Q_OBJECT

public:

    explicit TabHandleCSV(QWidget *parent = nullptr);
    void setText(const QString &text) override;
    QString getText() const override;
    void setLinkStatus(bool status);

    void loadFromFile(const QString &fileName) override;
    void saveToFile(const QString &fileName) override;
    void loadFromContent(const QByteArray &content) override;

    void addRow();
    void addColumn();   
    void deleteRow();
    void deleteColumn();

    void ReadfromServer(const QJsonObject& jsonObj);
    void ChickfromServer(const QJsonObject& jsonObj);
    void clearfromServer(const QJsonObject& jsonObj);
    void editedfromServer(const QJsonObject& jsonObj);

signals:
    void dataToSend(const QString &data);


protected:

private:
    int row = 0, col = 0;
    int foucsRow = 0;
    int foucsCol = 0;
    bool link = false;
    QString localIp;

    QTableWidget *tableWidget;
    QLabel *highlightLabel;
    std::map<std::pair<int, int>, QColor> originalColors;

    void parseCSV(const QString &csvText);
    QString toCSV() const;
    QString constructJson(QString oper, int row, int col, QString obj);
    void adjustItem(QTableWidgetItem *item);
};

#endif // TABHANDLECSV_H
