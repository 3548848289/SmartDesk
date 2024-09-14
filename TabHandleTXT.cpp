#include "TabHandleTXT.h"

TextTab::TextTab(QWidget *parent): TabAbstract(parent)
{
    textEdit = new QTextEdit(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(textEdit);
    setLayout(layout);
    loadSettings();

}

void TextTab::setText(const QString &text)
{
    Q_ASSERT(textEdit != nullptr);
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


void TextTab::loadSettings() {
    QSettings settings("MyApp", "MySettings");
    int fontSize = settings.value("FontSize", 12).toInt(); // 默认字体大小为 12
    updateFontSize(fontSize);
}

void TextTab::updateFontSize(int size) {
    if (size < 8) size = 8; // 设置最小字体大小
    if (size > 72) size = 72; // 设置最大字体大小

    QFont font = textEdit->font(); // 获取当前字体
    font.setPointSize(size); // 设置新字体大小
    textEdit->setFont(font); // 应用字体大小

    QSettings settings("MyApp", "MySettings");
    settings.setValue("FontSize", textEdit->font().pointSize());
}


void TextTab::setFontSize(int fontSize)
{
    QFont font = textEdit->font();
    font.setPointSize(fontSize);
    textEdit->setFont(font);
}
