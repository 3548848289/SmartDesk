// abstracttab.h
#ifndef ABSTRACTTAB_H
#define ABSTRACTTAB_H

#include <QWidget>
#include <QString>
#include <QByteArray>

class AbstractTab : public QWidget
{
    Q_OBJECT

public:
    explicit AbstractTab(QWidget *parent = nullptr) : QWidget(parent) {}
    virtual ~AbstractTab() {}

    virtual void setText(const QString &text) = 0;
    virtual QString getText() const = 0;
    virtual void loadFromFile(const QString &fileName) = 0;
    virtual void saveToFile(const QString &fileName) = 0;
    virtual void loadFromContent(const QByteArray &content) = 0;
};

#endif // ABSTRACTTAB_H
