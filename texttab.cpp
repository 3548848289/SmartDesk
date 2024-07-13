#include "texttab.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QVBoxLayout>

TextTab::TextTab(QWidget *parent): AbstractTab(parent)
{
    textEdit = new QTextEdit(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(textEdit);
    setLayout(layout);
}

void TextTab::setText(const QString &text)
{
    Q_ASSERT(textEdit != nullptr);
    qDebug() << "setText called with text:" << text;

    textEdit->setText(text);
}



QString TextTab::getText() const
{
    return textEdit->toPlainText();
}

void TextTab::loadFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        setText(in.readAll());
        file.close();
    } else {
        QMessageBox::warning(this, tr("Error"), tr("Could not open file"));
    }
}

void TextTab::saveToFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << getText();
        file.close();
    } else
    {
        QMessageBox::warning(this, tr("Error"), tr("Could not save file"));
    }
}


void TextTab::loadFromContent(const QByteArray &content)
{
    QString text = QString::fromUtf8(content);
    qDebug() << "Converted text:" << text;
    setText(text);
}

