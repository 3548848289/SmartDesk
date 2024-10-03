// TabAbstract.h
#ifndef TABABSTRACT_H
#define TABABSTRACT_H

#include <QWidget>
#include <QString>
#include <QByteArray>

#include <QJsonObject>
#include <QJsonDocument>
class TabAbstract : public QWidget
{
    Q_OBJECT

public:
    explicit TabAbstract(QWidget *parent = nullptr) : QWidget(parent) {}
    virtual ~TabAbstract() {}

    virtual void setText(const QString &text) = 0;
    virtual QString getText() const = 0;
    virtual void loadFromFile(const QString &fileName) = 0;
    virtual void saveToFile(const QString &fileName) = 0;
    virtual void loadFromContent(const QByteArray &content) = 0;

    virtual void ReadfromServer(const QJsonObject& jsonObj) = 0;
    virtual void ChickfromServer(const QJsonObject& jsonObj) = 0;
    virtual void clearfromServer(const QJsonObject& jsonObj) = 0;
    virtual void editedfromServer(const QJsonObject& jsonObj) = 0;
};

#endif // TABABSTRACT_H
