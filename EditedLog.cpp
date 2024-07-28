#include "EditedLog.h"

EditedLog::EditedLog(const QString &fileName)
    : m_fileName(fileName)
{
    // Initialize EditedLog file
    QFile file(m_fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        // Handle error opening file
        qDebug() << "Error: Cannot open EditedLog file " << m_fileName;
    }
    file.close();
}

void EditedLog::writeLog(const QString &message)
{
    QFile file(m_fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QDateTime timestamp = QDateTime::currentDateTime();
        out << timestamp.toString(Qt::ISODate) << " - " << message << "\n";
        file.close();
    } else {
        qDebug() << "Error: Cannot open EditedLog file " << m_fileName << " for writing";
    }
}
