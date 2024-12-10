/********************************************************************************
** Form generated from reading UI file 'ControlFrame.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLFRAME_H
#define UI_CONTROLFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlFrame
{
public:
    QGridLayout *gridLayout_2;
    QLabel *label_1;
    QSlider *rotateSlider;
    QLabel *label_4;
    QSlider *scaleSlider;
    QLabel *label_3;
    QSlider *shearSlider;
    QLabel *label_2;
    QSlider *translateSlider;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *yPosInput;
    QLineEdit *xPosInput;
    QLineEdit *textInput;
    QLabel *label_6;
    QLabel *label_5;
    QPushButton *addTextButton;
    QPushButton *exportButton;

    void setupUi(QWidget *ControlFrame)
    {
        if (ControlFrame->objectName().isEmpty())
            ControlFrame->setObjectName("ControlFrame");
        ControlFrame->resize(300, 149);
        gridLayout_2 = new QGridLayout(ControlFrame);
        gridLayout_2->setObjectName("gridLayout_2");
        label_1 = new QLabel(ControlFrame);
        label_1->setObjectName("label_1");

        gridLayout_2->addWidget(label_1, 0, 0, 1, 1);

        rotateSlider = new QSlider(ControlFrame);
        rotateSlider->setObjectName("rotateSlider");
        rotateSlider->setMaximum(360);
        rotateSlider->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_2->addWidget(rotateSlider, 0, 1, 1, 1);

        label_4 = new QLabel(ControlFrame);
        label_4->setObjectName("label_4");

        gridLayout_2->addWidget(label_4, 0, 2, 1, 1);

        scaleSlider = new QSlider(ControlFrame);
        scaleSlider->setObjectName("scaleSlider");
        scaleSlider->setMaximum(20);
        scaleSlider->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_2->addWidget(scaleSlider, 0, 3, 1, 1);

        label_3 = new QLabel(ControlFrame);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        shearSlider = new QSlider(ControlFrame);
        shearSlider->setObjectName("shearSlider");
        shearSlider->setMaximum(20);
        shearSlider->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_2->addWidget(shearSlider, 1, 1, 1, 1);

        label_2 = new QLabel(ControlFrame);
        label_2->setObjectName("label_2");

        gridLayout_2->addWidget(label_2, 1, 2, 1, 1);

        translateSlider = new QSlider(ControlFrame);
        translateSlider->setObjectName("translateSlider");
        translateSlider->setMaximum(100);
        translateSlider->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_2->addWidget(translateSlider, 1, 3, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        yPosInput = new QLineEdit(ControlFrame);
        yPosInput->setObjectName("yPosInput");

        horizontalLayout->addWidget(yPosInput);

        xPosInput = new QLineEdit(ControlFrame);
        xPosInput->setObjectName("xPosInput");

        horizontalLayout->addWidget(xPosInput);


        gridLayout->addLayout(horizontalLayout, 2, 1, 1, 1);

        textInput = new QLineEdit(ControlFrame);
        textInput->setObjectName("textInput");

        gridLayout->addWidget(textInput, 1, 1, 1, 1);

        label_6 = new QLabel(ControlFrame);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 2, 0, 1, 1);

        label_5 = new QLabel(ControlFrame);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        addTextButton = new QPushButton(ControlFrame);
        addTextButton->setObjectName("addTextButton");

        gridLayout->addWidget(addTextButton, 2, 2, 1, 1);

        exportButton = new QPushButton(ControlFrame);
        exportButton->setObjectName("exportButton");

        gridLayout->addWidget(exportButton, 1, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 2, 0, 1, 4);


        retranslateUi(ControlFrame);

        QMetaObject::connectSlotsByName(ControlFrame);
    } // setupUi

    void retranslateUi(QWidget *ControlFrame)
    {
        ControlFrame->setWindowTitle(QCoreApplication::translate("ControlFrame", "Form", nullptr));
        label_1->setText(QCoreApplication::translate("ControlFrame", "\346\227\213\350\275\254", nullptr));
        label_4->setText(QCoreApplication::translate("ControlFrame", "\347\274\251\346\224\276", nullptr));
        label_3->setText(QCoreApplication::translate("ControlFrame", "\345\210\207\345\217\230", nullptr));
        label_2->setText(QCoreApplication::translate("ControlFrame", "\344\275\215\347\247\273", nullptr));
        label_6->setText(QCoreApplication::translate("ControlFrame", "\346\260\264\345\215\260\345\235\220\346\240\207", nullptr));
        label_5->setText(QCoreApplication::translate("ControlFrame", "\346\267\273\345\212\240\346\260\264\345\215\260", nullptr));
        addTextButton->setText(QCoreApplication::translate("ControlFrame", "\347\241\256\345\256\232", nullptr));
        exportButton->setText(QCoreApplication::translate("ControlFrame", "\345\257\274\345\207\272\345\233\276\347\211\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ControlFrame: public Ui_ControlFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLFRAME_H
