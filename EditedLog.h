#ifndef EDITEDLOG_H
#define EDITEDLOG_H


#include <QString>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include "myJson.h"

class EditedLog
{
public:
    EditedLog(const QString &fileName = "log.txt");
    void writeLog(const QJsonObject &message);

private:
    QString m_fileName;
};

#endif // EDITEDLOG_H
