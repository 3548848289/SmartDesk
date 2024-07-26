#ifndef TABHANDLETXT_H
#define TABHANDLETXT_H

#include "TabAbstract.h"
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QVBoxLayout>

class TextTab : public TabAbstract
{
    Q_OBJECT

public:
    explicit TextTab(QWidget *parent = nullptr);
    void setText(const QString &text) override;
    QString getText() const override;
    void loadFromFile(const QString &fileName) override;
    void saveToFile(const QString &fileName) override;
    void loadFromContent(const QByteArray &content) override;
    void ReadfromServer(QString data) { }
    void ChickfromServer(QString data) { }
    void clearfromServer(QString data) { }
    void editedfromServer(QString data) { }

private:
    QTextEdit *textEdit;
};

#endif // TABHANDLETXT_H
