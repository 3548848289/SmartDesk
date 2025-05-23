// TabAbstract.h
#ifndef TABABSTRACT_H
#define TABABSTRACT_H

#include <QWidget>
#include <QString>
#include <QByteArray>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>

class TabAbstract : public QWidget
{
    Q_OBJECT

public:
    explicit TabAbstract(QWidget *parent = nullptr) : QWidget(parent) {}
    explicit TabAbstract(const QString& filePath, QWidget *parent = nullptr)
        : QWidget(parent), currentFilePath(filePath) {}

    virtual ~TabAbstract() {    }

    virtual void setContent(const QString &text) = 0;
    virtual QString getContent() const = 0;
    virtual void loadFromFile(const QString &fileName) = 0;
    virtual void loadFromInternet(const QByteArray &content) = 0;
    virtual void saveToFile(const QString &fileName) = 0;
    virtual void ControlWidget(bool judge) = 0;

    virtual QString getCurrentFilePath() const {
        return currentFilePath;
    }
    virtual void setCurrentFilePath(const QString& path) {
        currentFilePath = path;
    }

    void fileSave() {
        if (currentFilePath.isEmpty()) {
            QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"));
            if (!fileName.isEmpty()) {
                setCurrentFilePath(fileName);
            } else {
                return;
            }
        }
        saveToFile(currentFilePath);
        setContentModified(false);
        emit contentSaved(currentFilePath);
    }

    bool confirmClose() {
        if (isModified) {
            QMessageBox::StandardButton reply = QMessageBox::question(
                this, tr("未保存的更改"),
                tr("文档已被修改，是否保存更改？"),
                QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
            );

            if (reply == QMessageBox::Yes) {
                fileSave();
                return true;
            } else if (reply == QMessageBox::No) {
                return true;
            } else {
                return false;
            }
        }
        return true;
    }

signals:
    void contentModified();
    void contentSaved(const QString &fileName);

protected:
    QString currentFilePath;
    bool isModified;
    bool isShowControl;

    void setContentModified(bool modified) {
        if (isModified != modified) {
            isModified = modified;
            if (isModified)
                emit contentModified();
        }
    }

    void showControl() {
        isShowControl = true;
    }
};

#endif // TABABSTRACT_H
