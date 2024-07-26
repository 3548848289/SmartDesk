// TabAbstract.h
#ifndef TABABSTRACT_H
#define TABABSTRACT_H

#include <QWidget>
#include <QString>
#include <QByteArray>

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

    virtual void ReadfromServer(QString data) = 0;
    virtual void ChickfromServer(QString data) = 0;
    virtual void clearfromServer(QString data) = 0;
    virtual void editedfromServer(QString data) = 0;
};

#endif // TABABSTRACT_H
