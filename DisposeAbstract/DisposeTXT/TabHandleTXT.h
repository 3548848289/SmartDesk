#ifndef TABHANDLETXT_H
#define TABHANDLETXT_H

#include "../../main/include/TabAbstract.h"
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QSettings>
#include <QSplitter>
#include "ControlWidTXT.h"
#include "../../Setting/include/SettingManager.h"

class TextTab : public TabAbstract
{
    Q_OBJECT

public:
    explicit TextTab(const QString& filePath, QWidget *parent = nullptr);

    void setContent(const QString &text) override;
    QString getContent() const override;
    void loadFromFile(const QString &fileName) override;
    void loadFromInternet(const QByteArray &content) override;
    void saveToFile(const QString &fileName) override;
    void ControlWidget(QWidget* WControl){
        qDebug() << "TabHandleTXT: Showing control frame!";
    }

public slots:
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findAll(const QString &str, Qt::CaseSensitivity cs);
    void clearHighlight();
private:
    ControlWidTXT * controlWsidtxt;
    QSplitter * splitter;
    QTextEdit *textEdit;
};

#endif // TABHANDLETXT_H
