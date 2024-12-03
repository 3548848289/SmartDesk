#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QUuid>
class dbManager {
public:
    dbManager(const QString &dbName);
    virtual ~dbManager();

    bool open();
    void close();
    QString lastError() const;
    bool createTables();
protected:
    bool initializeTables();
    QSqlDatabase dbsqlite;
};

#endif // DBMANAGER_H
