#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QPushButton;
class NKLoading;
class NVOpenGLWidget;
class QResizeEvent;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:

    bool event(QEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

private:
    void drawUI();

    void initConnect();

    void onStart();

private:
    QPushButton* m_startBtn;
    QPushButton* m_stopBtn;

    QWidget* m_container;
    NVOpenGLWidget* m_openglWidget;
    NKLoading* m_loading;

};
#endif // WIDGET_H
