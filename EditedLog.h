#ifndef EDITEDLOG_H
#define EDITEDLOG_H


#include <QString>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

class EditedLog
{
public:
    EditedLog(const QString &fileName = "log.txt");
    void writeLog(const QString &message);

private:
    QString m_fileName;
};

#endif // EDITEDLOG_H
