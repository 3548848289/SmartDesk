#ifndef DBCLIPBOARD_H
#define DBCLIPBOARD_H

#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QDateTime>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "dbManager.h"

class dbClipboard : public dbManager
{
public:
    dbClipboard(const QString &dbName);
    bool setHistory(const QString &content);
    bool insertClipboardItem(const QString &id, const QString &content,
        const QString &type, const QDateTime &timestamp, const QString &source,
        bool isFavorite, const QString &tags, const QString &format);
    QList<QString> loadRecentHistory();
};

#endif // DBCLIPBOARD_H
