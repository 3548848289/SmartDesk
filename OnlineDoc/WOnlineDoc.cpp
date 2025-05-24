#include "./include/WOnlineDoc.h"
#include "ui/ui_WOnlineDoc.h"

WOnlineDoc::WOnlineDoc(QWidget *parent) : QWidget(parent), ui(new Ui::WOnlineDoc)
{
    ui->setupUi(this);

    download_view = new DownloadView();
    shared_view = new SharedView();

    ui->tabWidget->addTab(shared_view, "CSV文件共享");
    ui->tabWidget->addTab(download_view, "网络资源下载");
}


WOnlineDoc::~WOnlineDoc()
{

    delete ui;
}
