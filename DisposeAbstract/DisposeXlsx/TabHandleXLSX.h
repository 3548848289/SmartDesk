#ifndef TABHANDLEXLSX_H
#define TABHANDLEXLSX_H

#include <QTableWidget>
#include <QVBoxLayout>
#include <QString>
#include <QWidget>
#include <QFile>
#include <QHeaderView>
#include "../../main/include/TabAbstract.h"

class TabHandleXLSX : public TabAbstract
{
    Q_OBJECT
public:
    virtual void setContent(const QString &text) override;
    virtual QString getContent() const override;

    void saveToFile(const QString &fileName) override;
    void loadFromInternet(const QByteArray &content) override;

    TabHandleXLSX(const QString& filePath,QWidget *parent = nullptr);
    void loadFromFile(const QString &fileName) override;
    void ControlWidget(QWidget* WControl) override;

private:
    QTableWidget *tableWidget;

};

#endif // TABHANDLEXLSX_H
