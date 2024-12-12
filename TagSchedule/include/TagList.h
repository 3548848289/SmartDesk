#ifndef TAGLIST_H
#define TAGLIST_H

#include <QWidget>
#include <QFileInfo>
#include <QString>

namespace Ui {
class TagList;
}

class TagList : public QWidget
{
    Q_OBJECT

public:
    explicit TagList(QWidget *parent = nullptr);
    ~TagList();

    void setFileInfo(const QString &filePath, const QString &expirationInfo);
    void setTag(const QString &mtag);

    QString getFilePath() const;

private:
    Ui::TagList *ui;
    QString filePath;
    QString tag;
};

#endif // TAGLIST_H
