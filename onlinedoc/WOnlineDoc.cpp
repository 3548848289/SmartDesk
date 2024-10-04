#include "./include/WOnlineDoc.h"
#include "ui/ui_WOnlineDoc.h"

// 修改 WOnlineDoc 构造函数，确保内部控件的布局
WOnlineDoc::WOnlineDoc(QWidget *parent) : QWidget(parent), ui(new Ui::WOnlineDoc)
{
    ui->setupUi(this);

    downloadWidget = new downLoad();
    m_csvLinkServer = new csvLinkServer();

    ui->tabWidget->addTab(m_csvLinkServer, "连接服务器");
    ui->tabWidget->addTab(downloadWidget, "网络资源下载");

}


WOnlineDoc::~WOnlineDoc()
{
    delete ui;
}
