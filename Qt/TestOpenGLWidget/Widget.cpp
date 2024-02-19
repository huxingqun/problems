#include "Widget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QEvent>

#include "NKLoading.h"
#include "NVOpenGLWidget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_startBtn(nullptr)
    , m_stopBtn(nullptr)
    , m_openglWidget(nullptr)
    , m_loading(nullptr)
{
    drawUI();

    initConnect();
}

Widget::~Widget() {

}

bool Widget::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::UpdateRequest:
        if(m_openglWidget)
            m_openglWidget->update();
        break;
    default:
        break;
    }

    return QWidget::event(event);
}

void Widget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if(m_openglWidget)
    {
        m_openglWidget->resize(m_container->size());
    }

    if(m_loading)
    {
        m_loading->resize(m_container->size());
    }
}

void Widget::drawUI()
{
    setWindowFlag(Qt::FramelessWindowHint, true);
    QVBoxLayout* baseVL = new QVBoxLayout(this);

    QWidget* toolBar = new QWidget(this);
    toolBar->setFixedHeight(60);
    QHBoxLayout* toolBarLayout = new QHBoxLayout(toolBar);
    toolBarLayout->setContentsMargins(0,0,0,0);
    m_startBtn = new QPushButton(tr("开始"), this);
    m_stopBtn = new QPushButton(tr("停止"), this);
    toolBarLayout->addWidget(m_startBtn);
    toolBarLayout->addWidget(m_stopBtn);
    toolBarLayout->addStretch();

    baseVL->addWidget(toolBar);

    m_container = new QWidget(this);
    baseVL->addWidget(m_container);

    onStart();
}

void Widget::initConnect()
{
    connect(m_startBtn, &QPushButton::clicked, this, [this]{
        onStart();

    });

    connect(m_stopBtn, &QPushButton::clicked, this, [this]{
        if(!m_openglWidget)
            return;

        delete m_openglWidget;
        m_openglWidget = nullptr;

        m_loading->setVisible(false);
        delete m_loading;
        m_loading = nullptr;
    });
}

void Widget::onStart()
{
    if(m_openglWidget)
        return;

    m_openglWidget = new NVOpenGLWidget(m_container);
    m_openglWidget->setVisible(true);
    m_openglWidget->resize(m_container->size());

    m_loading = new NKLoading(m_container);
    m_loading->resize(m_container->size());
    m_loading->setVisible(true);
}
