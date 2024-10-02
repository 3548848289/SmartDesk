#include "ControlFrame.h"

ControlFrame::ControlFrame(QWidget *parent) : QFrame(parent)
{
    createControlFrame();
}

void ControlFrame::createControlFrame()
{
    // 旋转控制
    QSlider *rotateSlider = new QSlider(Qt::Horizontal);
    rotateSlider->setRange(0, 360);
    connect(rotateSlider, &QSlider::valueChanged, this, &ControlFrame::rotateChanged);

    QHBoxLayout *rotateLayout = new QHBoxLayout;
    rotateLayout->addWidget(rotateSlider);
    QGroupBox *rotateGroup = new QGroupBox(tr("Rotate"));
    rotateGroup->setLayout(rotateLayout);

    // 缩放控制
    QSlider *scaleSlider = new QSlider(Qt::Horizontal);
    scaleSlider->setRange(0, 20);
    connect(scaleSlider, &QSlider::valueChanged, this, &ControlFrame::scaleChanged);

    QHBoxLayout *scaleLayout = new QHBoxLayout;
    scaleLayout->addWidget(scaleSlider);
    QGroupBox *scaleGroup = new QGroupBox(tr("Scale"));
    scaleGroup->setLayout(scaleLayout);

    // 切变控制
    QSlider *shearSlider = new QSlider(Qt::Horizontal);
    shearSlider->setRange(0, 20);
    connect(shearSlider, &QSlider::valueChanged, this, &ControlFrame::shearChanged);

    QHBoxLayout *shearLayout = new QHBoxLayout;
    shearLayout->addWidget(shearSlider);
    QGroupBox *shearGroup = new QGroupBox(tr("Shear"));
    shearGroup->setLayout(shearLayout);

    // 位移控制
    QSlider *translateSlider = new QSlider(Qt::Horizontal);
    translateSlider->setRange(0, 100);
    connect(translateSlider, &QSlider::valueChanged, this, &ControlFrame::translateChanged);

    QHBoxLayout *translateLayout = new QHBoxLayout;
    translateLayout->addWidget(translateSlider);
    QGroupBox *translateGroup = new QGroupBox(tr("Translate"));
    translateGroup->setLayout(translateLayout);

    // 控制面板布局
    QVBoxLayout *frameLayout = new QVBoxLayout;
    frameLayout->setContentsMargins(10, 10, 10, 10);
    frameLayout->setSpacing(20);
    frameLayout->addWidget(rotateGroup);
    frameLayout->addWidget(scaleGroup);
    frameLayout->addWidget(shearGroup);
    frameLayout->addWidget(translateGroup);
    setLayout(frameLayout);
}
