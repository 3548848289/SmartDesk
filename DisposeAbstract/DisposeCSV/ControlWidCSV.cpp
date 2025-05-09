#include "ControlWidCSV.h"
#include "ui_ControlWidCSV.h"

ControlWidCSV::ControlWidCSV(QWidget *parent)
    : QWidget(parent), ui(new Ui::ControlWidCSV) {
    ui->setupUi(this);  // 设置 UI
    // 连接按钮点击信号到相应的信号

    connect(ui->addRowButton, &QPushButton::clicked, this, &ControlWidCSV::addRowClicked);
    connect(ui->deleteRowButton, &QPushButton::clicked, this, &ControlWidCSV::deleteRowClicked);
    connect(ui->addColumnButton, &QPushButton::clicked, this, &ControlWidCSV::addColumnClicked);
    connect(ui->deleteColumnButton, &QPushButton::clicked, this, &ControlWidCSV::deleteColumnClicked);

    bool isShow = SettingManager::Instance().file_see_csv();
    this->setVisible(isShow);
}

ControlWidCSV::~ControlWidCSV() {
    delete ui;
}


