#ifndef FILEITEMWIDGET_H
#define FILEITEMWIDGET_H

#include <QWidget>
#include <QFileInfo>
#include <QString>

namespace Ui {
class FileItemWidget;
}

class FileItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileItemWidget(QWidget *parent = nullptr);
    ~FileItemWidget();

    void setFileInfo(const QString &filePath, const QString &expirationInfo);
    void setTag(const QString &mtag);

    QString getFilePath() const;

private:
    Ui::FileItemWidget *ui;
    QString filePath;
    QString tag;
};

#endif // FILEITEMWIDGET_H
