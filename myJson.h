#ifndef MYJSON_H
#define MYJSON_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QString>
#include <tuple>
#include <optional>

class myJson {
public:
    myJson();

    static QString constructJson(const QString& localIp, const QString& oper,
                                 int row = -1, int col = -1, const QString& obj = QString());

    static QString parseAndPrintJson(const QJsonObject& jsonObj);

    static std::tuple<std::optional<QString>, int, int, std::optional<QString>>
    extract_common_fields(const QJsonObject& root);
};

#endif
