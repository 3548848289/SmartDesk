#ifndef MYJSON_H
#define MYJSON_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QString>

class myJson {
public:
    myJson();

    static QString constructJson(const QString& localIp, const QString& oper,
                                 int row = -1, int col = -1, const QString& obj = QString());

    static QString parseAndPrintJson(const QJsonObject& jsonObj);
};

#endif
