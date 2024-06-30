// texttab.h
#ifndef TEXTTAB_H
#define TEXTTAB_H

#include "abstracttab.h"
#include <QTextEdit>

class TextTab : public AbstractTab
{
    Q_OBJECT

public:
    explicit TextTab(QWidget *parent = nullptr);
    void setText(const QString &text) override;
    QString getText() const override;
    void loadFromFile(const QString &fileName) override;
    void saveToFile(const QString &fileName) override;
    void loadFromContent(const QByteArray &content) override;

private:
    QTextEdit *textEdit;
};

#endif // TEXTTAB_H
