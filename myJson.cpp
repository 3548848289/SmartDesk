#include "myJson.h"

myJson::myJson()
{

}

QString myJson::constructJson(const QString& localIp, const QString& oper,
                              int row, int col, const QString& obj) {
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

QString myJson::parseAndPrintJson(const QJsonObject& jsonObj) {

    QString ip = jsonObj.value("ip").toString();
    QString oper = jsonObj.value("operation").toString();
    int row = jsonObj.value("row").toInt(-1);  // 默认值为 -1
    int col = jsonObj.value("column").toInt(-1);  // 默认值为 -1
    QString obj = jsonObj.value("object").toString(QString());  // 默认值为空字符串

    qDebug() << "IP:" << ip << ", Operation:" << oper << ", Row:" << row << ", Column:" << col << ", Object:" << obj;

    QString output;
    output += "IP: " + ip + ", ";
    output += "Operation: " + oper + ", ";
    output += "Row: " + QString::number(row) + ", ";
    output += "Column: " + QString::number(col) + ", ";
    output += "Object: " + obj;

    return output;
}
