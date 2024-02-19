#include "Widget.h"

#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    auto defFmt = QSurfaceFormat::defaultFormat();
    defFmt.setDepthBufferSize(24);
    defFmt.setSamples(16);

#ifdef Q_OS_MAC
    defFmt.setProfile(QSurfaceFormat::CompatibilityProfile);
#if defined(ENABLE_DEBUG)
    defFmt.setOption(QSurfaceFormat::DebugContext);
#endif // ENABLE_DEBUG
    QSurfaceFormat::setDefaultFormat(defFmt);
#else
#if defined(ENABLE_DEBUG)
    defFmt.setOption(QSurfaceFormat::DebugContext);
    QSurfaceFormat::setDefaultFormat(defFmt);
#endif // ENABLE_DEBUG
    QSurfaceFormat::setDefaultFormat(defFmt);
#endif

    if (true) {
#ifdef QT_OPENGL_DYNAMIC
        qputenv("QT_OPENGL", "angle");
#endif
#ifdef Q_OS_WIN
        QString gl = "es_d3d11";
        if (gl.endsWith(QLatin1String("d3d11")))
            qputenv("QT_ANGLE_PLATFORM", "d3d11");
        else if (gl.endsWith(QLatin1String("d3d9")))
            qputenv("QT_ANGLE_PLATFORM", "d3d9");
        else if (gl.endsWith(QLatin1String("warp")))
            qputenv("QT_ANGLE_PLATFORM", "warp");
#endif
    }

    QApplication a(argc, argv);
    Widget w;
    w.showMaximized();
    return a.exec();
}
