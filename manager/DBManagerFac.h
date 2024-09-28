#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QDebug>

class DatabaseManager {
public:
    static DatabaseManager& instance() {
        static DatabaseManager instance; // 懒汉式单例
        return instance;
    }

    bool openDatabase(const QString& dbName) {
        if (!db.isOpen()) {
            db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName(dbName);
            if (!db.open()) {
                qDebug() << "数据库连接失败：" << db.lastError().text();
                                                          return false;
            }
        }
        return true;
    }

    QSqlDatabase getDatabase() {
        return db;
    }

    void closeDatabase() {
        if (db.isOpen()) {
            db.close();
            QSqlDatabase::removeDatabase(db.connectionName());
        }
    }

private:
    DatabaseManager() {} // 私有构造函数
    ~DatabaseManager() {
        closeDatabase();
    }

    QSqlDatabase db;
};
