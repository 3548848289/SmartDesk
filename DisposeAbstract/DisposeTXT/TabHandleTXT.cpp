#include "TabHandleTXT.h"
TextTab::TextTab(const QString &filePath, QWidget *parent)  : TabAbstract(filePath, parent)
{
    textEdit = new QTextEdit(this);
    // 为 QTextEdit 设置 C++ 语法高亮
    // new CppHighlighter(textEdit->document());

    controlWsidtxt = new ControlWidTXT(this);

    splitter = new QSplitter(Qt::Vertical, this);
    splitter->addWidget(textEdit);
    splitter->addWidget(controlWsidtxt);
    splitter->setSizes({700, 100});

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(splitter);
    setLayout(layout);

    loadSettings();

    connect(textEdit, &QTextEdit::textChanged, this, [this]() {
        setContentModified(true);
    });
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
    setContentModified(false);
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
    setContentModified(false);
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


void TextTab::findNext(const QString &str, Qt::CaseSensitivity cs)
{
    if(textEdit->find(str,QTextDocument::FindWholeWords)){
        QPalette palette = textEdit->palette();
        palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
        textEdit->setPalette(palette);
    }
}

void TextTab::findAll(const QString &str, Qt::CaseSensitivity cs)
{
    QTextDocument *document = textEdit->document();
    bool found = false;
    QTextCursor highlightCursor(document);

    highlightCursor.beginEditBlock();  // 开始文本块编辑

    QTextCharFormat plainFormat = highlightCursor.charFormat();
    QTextCharFormat colorFormat = plainFormat;
    colorFormat.setForeground(Qt::red);  // 设置红色高亮

    QTextDocument::FindFlags options = QTextDocument::FindWholeWords;
    if (cs == Qt::CaseInsensitive) {
        options |= QTextDocument::FindCaseSensitively;  // 如果是区分大小写，添加 FindCaseSensitively
    }

    // 查找所有匹配项
    while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
        highlightCursor = document->find(str, highlightCursor, options);

        if (!highlightCursor.isNull()) {
            found = true;

            // 选中匹配的单词
            highlightCursor.movePosition(QTextCursor::StartOfWord, QTextCursor::KeepAnchor);
            highlightCursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);

            // 合并字符格式（避免覆盖原有语法高亮）
            highlightCursor.mergeCharFormat(colorFormat);  // 使用 mergeCharFormat

            // Debug输出确认
            qDebug() << "Highlighting: " << highlightCursor.selectedText();
        }
    }

    highlightCursor.endEditBlock();  // 结束文本块编辑

    if (!found) {
        QMessageBox::information(this, tr("Word Not Found"),
                                 tr("Sorry, the word cannot be found."));
    }
}
