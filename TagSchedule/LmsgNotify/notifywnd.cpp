#include "notifywnd.h"
#include "notifymanager.h"
#include <QBoxLayout>
#include <QGraphicsDropShadowEffect>

NotifyWnd::NotifyWnd (NotifyManager *manager, QWidget *parent)
    : ArrangedWnd(manager, parent)
{
    background = new QFrame(this);
    background->setGeometry(3, 3, width()-6, height()-6);
    background->setObjectName("notify-background");

    QHBoxLayout *mainLayout = new QHBoxLayout(background);
    QVBoxLayout *contentLayout = new QVBoxLayout();

    iconLabel = new QLabel(background);
    iconLabel->setFixedSize(40, 40);
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setWordWrap(true);

    titleLabel = new QLabel(background);
    titleLabel->setObjectName("notify-title");

    bodyLabel = new QLabel(background);
    bodyLabel->setObjectName("notify-body");
    bodyLabel->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    bodyLabel->setWordWrap(true);

    contentLayout->addWidget(titleLabel);
    contentLayout->addWidget(bodyLabel);
    contentLayout->setStretch(1,1);

    mainLayout->addWidget(iconLabel);
    mainLayout->addLayout(contentLayout);
    mainLayout->setAlignment(iconLabel, Qt::AlignTop);

    closeBtn = new QPushButton("×", background);
    closeBtn->setObjectName("notify-close-btn");
    closeBtn->setFixedSize(24, 24);
    closeBtn->move(background->width() - closeBtn->width(), 0);
    connect(closeBtn, &QPushButton::clicked, this, &QObject::deleteLater);

    setStyleSheet(m_manager->styleSheet());

    // 边框阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setBlurRadius(5);
    background->setGraphicsEffect(shadow);

    connect(this, &ArrangedWnd::visibleChanged, [this](bool visible){
        if (visible)
        {
            int displayTime = m_data.value("displayTime", m_manager->displayTime()).toInt();
            QTimer::singleShot(displayTime, this, [this](){
                showArranged(0);
            });
        }
        else deleteLater();
    });
}

QVariantMap NotifyWnd::data() const
{
    return m_data;
}

// 需显示后调用
void NotifyWnd::setData(const QVariantMap &data)
{
    m_data = data;

    // 设置图标
    QPixmap icon;
    QVariant iconv = data.value("icon");
    if (iconv.type() == QVariant::Pixmap)
        icon = iconv.value<QPixmap>();
    if (iconv.type() == QVariant::String)
        icon = QPixmap(iconv.toString());
    else
        icon = QPixmap(m_manager->defaultIcon());
    icon = icon.scaled(QSize(32, 32), Qt::KeepAspectRatio);
    iconLabel->setPixmap(icon);

    // 设置标题
    QString title = data.value("title").toString();
    titleLabel->setText(title);

    // 获取正文内容
    QString body = m_data.value("body").toString();

    // 获取正文的最大可显示区域
    QSize s1 = bodyLabel->size();
    QSize s2 = bodyLabel->fontMetrics().size(Qt::TextSingleLine, body);

    int linecount = s1.height() / s2.height();
    int charcount = qFloor(1.0 * body.size() * s1.width() / s2.width()) * linecount;
    QString bodyElid = charcount > body.size() ? body : (body.left(charcount - 1) + "…");

    // 处理tag和annotation
    QString fullBody = bodyElid;  // 默认情况下，正文显示部分

    if (data.contains("tag")) {
        QStringList tagList = data.value("tag").toStringList();
        if (!tagList.isEmpty()) {
            fullBody += "<br/><i>Tags: " + tagList.join(", ") + "</i>";
        }
    }

    if (data.contains("annotation")) {
        QString annotation = data.value("annotation").toString();
        if (!annotation.isEmpty()) {
            fullBody += "<br/><i>Annotation: " + annotation + "</i>";
        }
    }

    // 在 bodyLabel 上显示所有内容
    bodyLabel->setText(bodyElid);
    // qDebug() << bodyLabel->text();

    // // 处理样式
    // if (data.contains("styleSheet"))
    //     setStyleSheet(data.value("styleSheet").toString());
    // else if (data.contains("theme"))
    //     setStyleSheet(m_manager->styleSheet(data.value("theme").toString()));
}


NotifyCountWnd::NotifyCountWnd(NotifyManager *manager, QWidget *parent)
    : ArrangedWnd(manager, parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents, true);

    iconLabel = new QLabel(this);
    iconLabel->setFixedSize(40, 40);
    iconLabel->setAlignment(Qt::AlignCenter);

    countLabel = new QLabel(this);
    countLabel->setObjectName("notify-count");
    countLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(iconLabel);
    mainLayout->addWidget(countLabel);

    // 文字阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(2, 2);
    shadow->setBlurRadius(5);
    setGraphicsEffect(shadow);

    setStyleSheet("#notify-count {"
                  "font: 20px Verdana;"
                  "color: #dd424d;"
                  "}");

    QPixmap icon = QPixmap(m_manager->defaultIcon());
    icon = icon.scaled(QSize(32, 32), Qt::KeepAspectRatio);
    iconLabel->setPixmap(icon);

    flickerAnim = new QPropertyAnimation(this, "windowOpacity", this);
    flickerAnim->setStartValue(1);
    flickerAnim->setKeyValueAt(0.25, 0.1);
    flickerAnim->setKeyValueAt(0.5, 1);
    flickerAnim->setEndValue(1);
    flickerAnim->setDuration(2000);
    flickerAnim->setLoopCount(-1);

    connect(this, &ArrangedWnd::visibleChanged, [this](bool visible){
        if (visible) flickerAnim->start();
        else flickerAnim->stop();
    });
}

void NotifyCountWnd::setCount(int count)
{
    countLabel->setNum(count);
}
