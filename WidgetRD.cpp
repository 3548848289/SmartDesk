#include "WidgetRD.h"
#include "ui_WidgetRD.h"

// 修改 WidgetRD 构造函数，确保内部控件的布局
WidgetRD::WidgetRD(QWidget *parent) : QWidget(parent), ui(new Ui::WidgetRD)
{
    ui->setupUi(this);

    downloadWidget = new downLoad();
    m_csvLinkServer = new csvLinkServer();

    ui->tabWidget->addTab(m_csvLinkServer, "连接服务器");
    ui->tabWidget->addTab(downloadWidget, "网络资源下载");

}


WidgetRD::~WidgetRD()
{
    delete ui;
}
