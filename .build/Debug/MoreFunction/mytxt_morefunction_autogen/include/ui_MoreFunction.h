/********************************************************************************
** Form generated from reading UI file 'MoreFunction.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOREFUNCTION_H
#define UI_MOREFUNCTION_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MoreFunction
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QTextEdit *textEdit;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QWidget *MoreFunction)
    {
        if (MoreFunction->objectName().isEmpty())
            MoreFunction->setObjectName("MoreFunction");
        MoreFunction->resize(478, 329);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::HelpAbout));
        MoreFunction->setWindowIcon(icon);
        label = new QLabel(MoreFunction);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 70, 61, 31));
        lineEdit = new QLineEdit(MoreFunction);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(120, 70, 271, 20));
        QFont font;
        font.setPointSize(10);
        lineEdit->setFont(font);
        label_2 = new QLabel(MoreFunction);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 120, 71, 151));
        textEdit = new QTextEdit(MoreFunction);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(120, 100, 271, 191));
        label_4 = new QLabel(MoreFunction);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 20, 61, 16));
        QFont font1;
        font1.setPointSize(12);
        label_4->setFont(font1);
        label_5 = new QLabel(MoreFunction);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(120, 20, 271, 16));
        label_5->setFont(font1);

        retranslateUi(MoreFunction);

        QMetaObject::connectSlotsByName(MoreFunction);
    } // setupUi

    void retranslateUi(QWidget *MoreFunction)
    {
        MoreFunction->setWindowTitle(QCoreApplication::translate("MoreFunction", "\346\233\264\345\244\232\345\212\237\350\203\275", nullptr));
        label->setText(QCoreApplication::translate("MoreFunction", "github\345\234\260\345\235\200", nullptr));
        lineEdit->setText(QCoreApplication::translate("MoreFunction", "https://github.com/3548848289/SmartDesk", nullptr));
        label_2->setText(QCoreApplication::translate("MoreFunction", "\346\234\252\345\274\200\346\224\276\345\212\237\350\203\275", nullptr));
        textEdit->setHtml(QCoreApplication::translate("MoreFunction", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">1.csv\346\226\207\344\273\266\345\205\261\344\272\253\347\263\273\347\273\237\357\274\214\350\257\245\345\212\237\350\203\275\350\203\275\344\270\216\345\220\214\346\236\204\351\200\240\345\215\263\344\275\277\345\261\200\345\237\237\347\275\221\357\274\214\350\277\233\350\241\214csv\346\226\207\344\273\266\347\232\204\345\234\250\347\272\277\345\205\261\344\272"
                        "\253\347\274\226\350\276\221</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">2.\347\224\250\346\210\267\344\277\241\346\201\257\350\256\260\345\275\225\347\263\273\347\273\237\357\274\214\347\242\215\344\272\216\346\262\241\346\234\211\347\251\272\344\275\231\347\224\265\350\204\221\344\275\234\346\234\215\345\212\241\345\231\250\357\274\214\350\257\245\345\212\237\350\203\275\346\232\202\346\227\266\351\232\220\350\227\217\357\274\214\345\246\202\346\234\211\351\234\200\350\246\201\345\212\241\345\277\205\345\234\250github\344\270\212\345\212\240star\357\274\214star\345\244\232\345\220\216\346\210\221\344\274\232\345\274\200\346\224\276\357\274\214\350\257\245\345\212\237\350\203\275\350\203\275\350\256\251\347\224\250\346\210\267\345\260\206 \346\240\207\347\255\276\344\277\241\346\201\257 \345\244\207\344\273\275\344\277\241\346\201\257 \344\270\252\346\200\247\345\214\226\350\256\276\347"
                        "\275\256\344\277\241\346\201\257 \344\270\212\344\274\240\350\207\263\344\272\221\346\234\215\345\212\241\345\231\250</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("MoreFunction", "SmartDesk", nullptr));
        label_5->setText(QCoreApplication::translate("MoreFunction", "\346\202\250\345\234\250github\344\270\212\347\232\204stars\346\230\257\345\257\271\346\210\221\346\234\200\345\244\247\347\232\204\346\224\257\346\214\201\357\274\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MoreFunction: public Ui_MoreFunction {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOREFUNCTION_H
