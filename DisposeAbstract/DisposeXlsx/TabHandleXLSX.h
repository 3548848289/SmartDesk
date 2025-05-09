#ifndef TABHANDLEXLSX_H
#define TABHANDLEXLSX_H
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QSplitter>
#include <QDir>
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
    void loadFromFile(const QString &fileName) override;
    void loadFromInternet(const QByteArray &content) override;
    void saveToFile(const QString &fileName) override;
    void ControlWidget(bool judge) override;


    TabHandleXLSX(const QString& filePath,QWidget *parent = nullptr);

private:
    QTableWidget *tableWidget;

};

#endif // TABHANDLEXLSX_H
