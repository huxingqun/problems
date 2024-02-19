#ifndef NVOPENGLWIDGET_H
#define NVOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class QOpenGLShaderProgram;


class NVOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit NVOpenGLWidget(QWidget *parent = nullptr);

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

signals:

private:
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;

    QOpenGLShaderProgram *m_program = nullptr;
    int m_frame = 0;
};

#endif // NVOPENGLWIDGET_H
