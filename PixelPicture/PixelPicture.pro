#-------------------------------------------------
#
# Project created by QtCreator 2015-03-31T23:00:44
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PixelPicture
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    pixel.cpp \
    window.cpp \
    tool.cpp \
    ellipsetool.cpp \
    pentool.cpp \
    pixelscene.cpp \
    erasertool.cpp \
    canvas.cpp \
    layer.cpp \
    layerpixel.cpp \
    frame.cpp \
    importsettings.cpp \
    animationtool.cpp \
    imageconvertertool.cpp \
    videoconvertertool.cpp \
    videosurface.cpp \
    renamelayer.cpp \
    linetool.cpp \
    rectangletool.cpp \
    filltool.cpp

HEADERS  += mainwindow.h \
    pixel.h \
    window.h \
    tool.h \
    ellipsetool.h \
    pentool.h \
    pixelscene.h \
    erasertool.h \
    canvas.h \
    layer.h \
    layerpixel.h \
    frame.h \
    importsettings.h \
    animationtool.h \
    imageconvertertool.h \
    videoconvertertool.h \
    videosurface.h \
    renamelayer.h \
    linetool.h \
    rectangletool.h \
    filltool.h

FORMS    += mainwindow.ui \
    importsettings.ui \
    renamelayer.ui
