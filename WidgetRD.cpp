#include "WidgetRD.h"
#include "ui_WidgetRD.h"
WidgetRD::WidgetRD(QWidget *parent) :QWidget(parent),ui(new Ui::WidgetRD)
{
    ui->setupUi(this);
    downloadWidget = new downLoad();
    m_csvLinkServer = new csvLinkServer();

    ui->tabWidget->addTab(downloadWidget, "网络资源下载");
    ui->tabWidget->addTab(m_csvLinkServer, "连接服务器");
}

WidgetRD::~WidgetRD()
{
    delete ui;
}
