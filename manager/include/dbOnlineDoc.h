#ifndef DBONLINEDOC_H
#define DBONLINEDOC_H


#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QDateTime>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "dbManager.h"

class dbOnlineDoc : public dbManager
{
public:
    dbOnlineDoc(const QString &dbName);
    QStringList getSharedFilesByShareToken(const QString &shareToken);
};

#endif // DBONLINEDOC_H
