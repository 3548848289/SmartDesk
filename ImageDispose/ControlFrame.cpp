#include "ControlFrame.h"
#include "ui_ControlFrame.h"

ControlFrame::ControlFrame(QWidget *parent)
    : QWidget(parent), ui(new Ui::ControlFrame)
{
    ui->setupUi(this);

    setupConnections();
}

ControlFrame::~ControlFrame()
{
    delete ui;
}

void ControlFrame::setupConnections()
{
    connect(ui->rotateSlider, &QSlider::valueChanged, this, &ControlFrame::rotateChanged);
    connect(ui->scaleSlider, &QSlider::valueChanged, this, &ControlFrame::scaleChanged);
    connect(ui->shearSlider, &QSlider::valueChanged, this, &ControlFrame::shearChanged);
    connect(ui->translateSlider, &QSlider::valueChanged, this, &ControlFrame::translateChanged);
}


void ControlFrame::on_addTextButton_clicked()
{
    QString text = ui->textInput->text();
    // 获取用户输入的 x 和 y 坐标
    bool xOk, yOk;
    int x = ui->xPosInput->text().toInt(&xOk);
    int y = ui->yPosInput->text().toInt(&yOk);

    if (!text.isEmpty() && xOk && yOk) {
        // 发出信号，通知外部添加文字和位置
        emit textAdded(text, QPointF(x, y));
    }
}


void ControlFrame::on_exportButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("Images (*.png *.jpg *.bmp)"));
    if (!filePath.isEmpty()) {
        emit exportRequested(filePath);
    }
}

