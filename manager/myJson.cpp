#include "myJson.h"

myJson::myJson()
{

}

QString myJson::constructJson(const QString& localIp, const QString& oper,
                              int row, int col, const QString& obj) {
    QJsonObject jsonObj;
    jsonObj["ip"] = localIp;
    jsonObj["operation"] = oper;
    jsonObj["row"] = row;
    jsonObj["column"] = col;
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


std::tuple<std::optional<QString>, int, int, std::optional<QString>>
myJson::extract_common_fields(const QJsonObject& root) {
    std::optional<QString> ip = std::nullopt;
    int row = -1;
    int column = -1;
    std::optional<QString> object = std::nullopt;

    if (root.contains("ip") && root["ip"].isString()) {
        ip = root["ip"].toString();
    }
    if (root.contains("row") && root["row"].isDouble()) {
        row = root["row"].toInt();
    }
    if (root.contains("column") && root["column"].isDouble()) {
        column = root["column"].toInt();
    }
    if (root.contains("object") && root["object"].isString()) {
        object = root["object"].toString();
    }

    if (!ip || row < 0 || column < 0 || !object) {
        return {std::nullopt, -1, -1, std::nullopt};
    }
    return {ip, row, column, object};
}
