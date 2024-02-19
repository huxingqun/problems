QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

win32: {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
    QMAKE_CXXFLAGS -= -Zc:__cplusplus

}

LIBS += -lOpenGL32

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    NKLoading.cpp \
    NVOpenGLWidget.cpp \
    main.cpp \
    Widget.cpp

HEADERS += \
    NKLoading.h \
    NVOpenGLWidget.h \
    Widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
