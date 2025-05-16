#include "dbClipboard.h"

dbClipboard::dbClipboard(const QString &dbName) : dbManager(dbName) { }

bool dbClipboard::setHistory(const QString &content)
{
    QSqlQuery query(dbsqlite);
    query.prepare(R"(
        INSERT INTO clipboard_history (content) VALUES (:content) )");
    query.bindValue(":content", content);
    if (!query.exec()) {
        qDebug() << "插入失败:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<QString> dbClipboard::loadRecentHistory(int hours)
{
    QList<QString> historyList;
    QSqlQuery query(dbsqlite);
    query.prepare(R"(
        SELECT content FROM clipboard_history
        WHERE DATE(timestamp) >= DATE('now', ?)
        ORDER BY timestamp DESC
    )");

    // 构造动态的时间过滤条件，传入的是类似 '-X hour' 的格式
    QString timeFilter = QString("-%1 hour").arg(hours);
    query.bindValue(0, timeFilter); // 绑定时间参数

    if (!query.exec()) {
        qDebug() << "加载剪贴板历史失败: " << query.lastError().text();
        return historyList;
    }

    while (query.next()) {
        QString content = query.value(0).toString();
        historyList.append(content);
    }

    return historyList;
}


bool dbClipboard::insertClipboardItem(const QString &id, const QString &content,
    const QString &type, const QDateTime &timestamp, const QString &source,
    bool isFavorite,const QString &tags,const QString &format) {
    QSqlQuery query(dbsqlite);
    query.prepare(R"(
        INSERT INTO clipboard_history (
            id, content, type, timestamp, source, is_favorite, tags, format
        ) VALUES (
            :id, :content, :type, :timestamp, :source, :is_favorite, :tags, :format
        )
    )");

    query.bindValue(":id", id);
    query.bindValue(":content", content);
    query.bindValue(":type", type);
    query.bindValue(":timestamp", timestamp.toString(Qt::ISODate));
    query.bindValue(":source", source);
    query.bindValue(":is_favorite", isFavorite);
    query.bindValue(":tags", tags);
    query.bindValue(":format", format);

    if (!query.exec()) {
        qDebug() << "插入失败:" << query.lastError().text();
        return false;
    }
    return true;
}
