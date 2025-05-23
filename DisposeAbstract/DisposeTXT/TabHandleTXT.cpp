#include "TabHandleTXT.h"
TextTab::TextTab(const QString &filePath, QWidget *parent)  : TabAbstract(filePath, parent)
{
    textEdit = new QTextEdit(this);
    // 为 QTextEdit 设置 C++ 语法高亮
    // new CppHighlighter(textEdit->document());

    controlWidtxt = new ControlWidTXT(this);


    splitter = new QSplitter(Qt::Vertical, this);
    splitter->addWidget(textEdit);
    splitter->addWidget(controlWidtxt);
    splitter->setSizes({700, 100});

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(splitter);
    setLayout(layout);

    int fontSize = SettingManager::Instance().file_see_font_size();

    QFont font = textEdit->font();
    font.setPointSize(fontSize);
    textEdit->setFont(font);

    connect(textEdit, &QTextEdit::textChanged, this, [this]() {
        setContentModified(true);
    });
}

void TextTab::setContent(const QString &text)
{
    Q_ASSERT(textEdit != nullptr);
    textEdit->setText(text);
}

QString TextTab::getContent() const
{
    return textEdit->toPlainText();
}

void TextTab::loadFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        setContent(in.readAll());
        file.close();
    } else {
        QMessageBox::warning(this, tr("错误"), tr("无法打开文件"));
    }
    setContentModified(false);
}

void TextTab::saveToFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << getContent();
        file.close();
    } else
    {
        QMessageBox::warning(this, tr("错误"), tr("无法保存文件"));
    }
    setContentModified(false);
}


void TextTab::loadFromInternet(const QByteArray &content)
{
    QString text = QString::fromUtf8(content);
    qDebug() << "Converted text:" << text;
    setContent(text);
}

void TextTab::findNext(const QString &str, Qt::CaseSensitivity cs)
{
    QTextDocument::FindFlags findFlags = QTextDocument::FindWholeWords;

    if (cs == Qt::CaseSensitive) {
        findFlags |= QTextDocument::FindCaseSensitively;
    }

    // 第一次查找
    if (!textEdit->find(str, findFlags)) {
        // 没找到：移动光标到文档开头
        QTextCursor cursor = textEdit->textCursor();
        cursor.movePosition(QTextCursor::Start);
        textEdit->setTextCursor(cursor);

        // 尝试再次查找
        textEdit->find(str, findFlags);
    }

    // 如果找到了，设置高亮颜色
    if (textEdit->textCursor().hasSelection()) {
        QPalette palette = textEdit->palette();
        palette.setColor(QPalette::Highlight, palette.color(QPalette::Active, QPalette::Highlight));
        textEdit->setPalette(palette);
    }
}



void TextTab::findAll(const QString &str, Qt::CaseSensitivity cs)
{
    QTextDocument *document = textEdit->document();
    document->undo();
    bool found = false;
    QList<QTextEdit::ExtraSelection> extraSelections;

    QTextCursor cursor(document);
    cursor.beginEditBlock();

    QTextCharFormat plainFormat(cursor.charFormat());
    QTextCharFormat colorFormat = plainFormat;
    colorFormat.setForeground(Qt::red);

    while (!cursor.isNull() && !cursor.atEnd()) {
        cursor = document->find(str, cursor, QTextDocument::FindWholeWords);
        if (!cursor.isNull()) {
            found = true;
            // 创建额外的选择（高亮）
            QTextEdit::ExtraSelection selection;
            selection.format = colorFormat;
            selection.cursor = cursor;
            extraSelections.append(selection);
        }
    }

    cursor.endEditBlock();
    textEdit->setExtraSelections(extraSelections);

    if (!found)
        QMessageBox::information(this, tr("查找"), tr("找不到此单词"));
}

void TextTab::clearHighlight()
{
    textEdit->setExtraSelections(QList<QTextEdit::ExtraSelection>());
}


