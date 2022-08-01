QT       += core gui opengl openglwidgets printsupport
include(QTGifimage-master/src/gifimage/qtgifimage.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    affine_transformations.c \
    edgesthickness.cpp \
    glview.cpp \
    main.cpp \
    mainwindow.cpp \
    parser.c \
    verticesize.cpp

HEADERS += \
    edgesthickness.h \
    glview.hpp \
    mainwindow.h \
    3d_viewer.h \
    verticesize.h

FORMS += \
    edgesthickness.ui \
    mainwindow.ui \
    verticesize.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
