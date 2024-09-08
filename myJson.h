#ifndef MYJSON_H
#define MYJSON_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QString>

class myJson {
public:
    myJson();

    static QString constructJson(const QString& localIp, const QString& oper, int row = -1, int col = -1, const QString& obj = QString()) {
        QJsonObject jsonObj;
        jsonObj["ip"] = localIp;
        jsonObj["operation"] = oper;
        if (row != -1) {
            jsonObj["row"] = row;
        }
        if (col != -1) {
            jsonObj["column"] = col;
        }
        if (!obj.isEmpty()) {
            jsonObj["object"] = obj;
        }

        QJsonDocument jsonDoc(jsonObj);
        QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);

        return jsonString;
    }

    void parseAndPrintJson(const QString& jsonString) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
        QJsonObject jsonObj = jsonDoc.object();

        QString ip = jsonObj.value("ip").toString();
        QString oper = jsonObj.value("operation").toString();
        int row = jsonObj.value("row").toInt(-1);  // 默认值为 -1
        int col = jsonObj.value("column").toInt(-1);  // 默认值为 -1
        QString obj = jsonObj.value("object").toString(QString());  // 默认值为空字符串

        qDebug() << "IP:" << ip << ", Operation:" << oper << ", Row:" << row << ", Column:" << col << ", Object:" << obj;
    }
};

#endif
