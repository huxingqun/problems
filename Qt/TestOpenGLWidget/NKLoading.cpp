#include "NKLoading.h"
#include <QPainter>
#include <QTimer>
#include <QPropertyAnimation>
#include <QSvgRenderer>
#include <QPainterPath>
NKLoading::NKLoading(QWidget* parent)
    : QWidget( parent)
    , m_pixmap(":/loginLoading.png")
    , m_rotation(0)
    , m_loadingImgSize(78, 78)
    , m_timeout(-1)
    , m_bShowBackgroundColor(false)
    , m_iBorderRadius(0)
{
//    m_timer = new QTimer(this);
//    connect(m_timer, &QTimer::timeout, this, &NKLoading::handleTimeout);
//    m_timer->start(25);

    m_aniRotation = new QPropertyAnimation(this, "rotation", this);
    m_aniRotation->setLoopCount(-1);
    m_aniRotation->setDuration(2200);
    m_aniRotation->setStartValue(0);
    m_aniRotation->setEndValue(40);
    //m_aniRotation->start();
    m_backgroundColor = QColor("#999999");//"#55999999"
    m_backgroundColor.setAlpha(85);
    m_beginTime = QTime::currentTime();
}

NKLoading::~NKLoading()
{
    if(m_aniRotation)
    {
        m_aniRotation->stop();
    }
}

void NKLoading::setRotation(int r)
{
    if(r == m_rotation)
        return;

    m_rotation = r;
    emit rotationChanged();

    if(m_timeout >= 0){
        int duration = m_beginTime.msecsTo(QTime::currentTime());
        if(duration > m_timeout){
            setVisible(false);
            emit loadingFinished();
        }
    }

    update();
}

void NKLoading::setTimeout(int t)
{
    if(m_timeout == t)
        return;

    m_timeout = t;
}

bool NKLoading::isRunning()
{
    return m_aniRotation->state() == QPropertyAnimation::Running;
}

void NKLoading::setLoadingImage(const QString& strImg)
{
    m_strLoadingImg = strImg;
    QString strExtName = imgExtName();
    if (0 != strExtName.compare("svg", Qt::CaseInsensitive))
    {
        m_pixmap.load(m_strLoadingImg);
    }
    update();
}

void NKLoading::setLoadingImageSize(int w, int h)
{
    m_loadingImgSize = QSize(w, h);
}

void NKLoading::setBackgroundColor(const QColor& clr)
{
    m_backgroundColor = clr;
    update();
}

void NKLoading::showBackgroundColor(bool show)
{
    m_bShowBackgroundColor = show;
    update();
}

void NKLoading::setBorderRadius(int radius)
{
    m_iBorderRadius = radius;
    update();
}

void NKLoading::paintEvent(QPaintEvent *event)
{
    (void)event;

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

    if (m_bShowBackgroundColor)
    {
        QPainterPath pathBK;
        pathBK.addRoundedRect(rect(), m_iBorderRadius, m_iBorderRadius);
        painter.fillPath(pathBK, QBrush(m_backgroundColor));
    }

    painter.translate(this->size().width() / 2, this->size().height() / 2);
    painter.rotate(m_rotation * 9);
    QString strExtName = imgExtName();
    if (0 == strExtName.compare("svg", Qt::CaseInsensitive))
    {
        QSvgRenderer svgRender(m_strLoadingImg);
        svgRender.setAspectRatioMode(Qt::KeepAspectRatio);
        svgRender.render(&painter, QRect(-width()*0.5, -height()*0.5, width(), height()));
    }
    else
    {
        QPixmap pixmap = m_pixmap.scaled(m_loadingImgSize, Qt::AspectRatioMode::KeepAspectRatio);
        //int w = (width() - pixmap.width()) / 2;
        //int h = (height() - pixmap.height()) / 2;
        int w = -pixmap.width() / 2;
        int h = -pixmap.height() / 2;
        painter.drawPixmap(w, h, pixmap);
    }

}

void NKLoading::showEvent(QShowEvent *event)
{
    m_beginTime = QTime::currentTime();

    if(m_aniRotation->state() != QPropertyAnimation::Running)
    {
        m_aniRotation->start();
    }

    QWidget::showEvent(event);
}

void NKLoading::hideEvent(QHideEvent *event)
{
    if(m_aniRotation->state() == QPropertyAnimation::Running)
    {
        m_aniRotation->stop();
    }

    QWidget::hideEvent(event);
}

void NKLoading::closeEvent(QCloseEvent *event)
{
    if(m_aniRotation->state() == QPropertyAnimation::Running)
    {
        m_aniRotation->stop();
    }

    QWidget::closeEvent(event);
}

QString NKLoading::imgExtName() const
{
    int iPos = m_strLoadingImg.lastIndexOf(".");
    QString strExtName = m_strLoadingImg.mid(iPos + 1, -1);
    return strExtName;
}

//void NKLoading::handleTimeout()
//{
//    m_rotation += 5;
//    m_rotation %= 360;
//    update();
//}

