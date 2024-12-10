#ifndef TABHANDLETXT_H
#define TABHANDLETXT_H

#include "TabAbstract.h"
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QSettings>
#include <QSplitter>
#include "ControlWidTXT.h"

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
    ControlWidTXT * controlWsidtxt;
    QSplitter * splitter;
    QTextEdit *textEdit;
};

#endif // TABHANDLETXT_H
