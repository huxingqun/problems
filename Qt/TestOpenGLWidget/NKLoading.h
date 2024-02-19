#ifndef NKLOADING_H
#define NKLOADING_H

#include <QWidget>
#include <QTime>
#include <QColor>
class QPropertyAnimation;

class NKLoading : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int rotation READ rotation WRITE setRotation NOTIFY rotationChanged)
public:
    NKLoading(QWidget* parent = nullptr);
    ~NKLoading();

    void setRotation(int r);
    int rotation() const {return m_rotation;}

    void setTimeout(int t);
    int timeout()const {return m_timeout;}

    bool isRunning();

    void setLoadingImage(const QString& strImg);

    void setLoadingImageSize(int w, int h);
    //设置背景色
    void setBackgroundColor(const QColor& clr);
    void showBackgroundColor(bool show);
    //设置圆角
    void setBorderRadius(int radius);
signals:
    void rotationChanged();
    void loadingFinished();

protected:
    virtual void paintEvent(QPaintEvent *event) override;

    void showEvent(QShowEvent *event) override;

    void hideEvent(QHideEvent *event) override;

    void closeEvent(QCloseEvent *event) override;
    QString imgExtName()const;
//private slots:
//    void handleTimeout();

private:
    QPixmap m_pixmap;
    int m_rotation;

    QTime m_beginTime;

    QSize m_loadingImgSize;
    QString m_strLoadingImg;
    
//    QTimer *m_timer;
    int m_timeout;
    QPropertyAnimation* m_aniRotation;
    bool m_bShowBackgroundColor;
    QColor m_backgroundColor;
    int m_iBorderRadius;
};

#endif // NKLOADING_H
