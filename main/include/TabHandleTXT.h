#ifndef TABHANDLETXT_H
#define TABHANDLETXT_H

#include "TabAbstract.h"
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QSettings>
#include <QApplication>
#include <QTextEdit>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QTextDocument>

class CppHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    CppHighlighter(QTextDocument *parent = nullptr) : QSyntaxHighlighter(parent) {}

protected:
    void highlightBlock(const QString &text) override
    {
        // 设置默认格式
        QTextCharFormat defaultFormat;
        defaultFormat.setForeground(Qt::white);
        setFormat(0, text.length(), defaultFormat);

        // 关键字高亮
        QTextCharFormat keywordFormat;
        keywordFormat.setForeground(Qt::blue);  // 设置蓝色
        QRegularExpression keywordRegex("\\b(class|struct|public|private|protected|if|else|for|while|return|int|float|double|char|void)\\b");
        QRegularExpressionMatchIterator keywordIterator = keywordRegex.globalMatch(text);
        while (keywordIterator.hasNext()) {
            QRegularExpressionMatch match = keywordIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), keywordFormat);
        }

        // 字符串高亮
        QTextCharFormat stringFormat;
        stringFormat.setForeground(Qt::green);  // 设置绿色
        QRegularExpression stringRegex("\"([^\"]*)\"");
        QRegularExpressionMatchIterator stringIterator = stringRegex.globalMatch(text);
        while (stringIterator.hasNext()) {
            QRegularExpressionMatch match = stringIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), stringFormat);
        }

        // 注释高亮
        QTextCharFormat commentFormat;
        commentFormat.setForeground(Qt::darkGreen);  // 设置深绿色
        QRegularExpression commentRegex("//[^\n]*");
        QRegularExpressionMatchIterator commentIterator = commentRegex.globalMatch(text);
        while (commentIterator.hasNext()) {
            QRegularExpressionMatch match = commentIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), commentFormat);
        }
    }
};


class TextTab : public TabAbstract
{
    Q_OBJECT

public:
    explicit TextTab(const QString& filePath, QWidget *parent = nullptr);



    void setText(const QString &text) override;
    QString getText() const override;
    void loadFromFile(const QString &fileName) override;
    void saveToFile(const QString &fileName) override;
    void loadFromContent(const QByteArray &content) override;
    void ReadfromServer(const QJsonObject& jsonObj) { }
    void ChickfromServer(const QJsonObject& jsonObj) { }
    void clearfromServer(const QJsonObject& jsonObj) { }
    void editedfromServer(const QJsonObject& jsonObj) { }

    void ControlWidget(QWidget* WControl){
        qDebug() << "TabHandleTXT: Showing control frame!";
    }

private:
    void setFontSize(int fontSize);
    void loadSettings();
    void updateFontSize(int size);


private:
    QTextEdit *textEdit;
};

#endif // TABHANDLETXT_H
