#-------------------------------------------------
#
# Project created by QtCreator 2019-08-27T21:42:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Trabalho1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        buttonwindow.cpp \
        imagewindow.cpp \
        main.cpp

HEADERS += \
        buttonwindow.h \
        imagewindow.h \
        jpeg-9c/jpeglib.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/jpeg-9c/.libs/release/ -ljpeg
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/jpeg-9c/.libs/debug/ -ljpeg
else:unix: LIBS += -L$$PWD/jpeg-9c/.libs/ -ljpeg

INCLUDEPATH += $$PWD/jpeg-9c/.libs
DEPENDPATH += $$PWD/jpeg-9c/.libs

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/jpeg-9c/.libs/release/libjpeg.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/jpeg-9c/.libs/debug/libjpeg.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/jpeg-9c/.libs/release/jpeg.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/jpeg-9c/.libs/debug/jpeg.lib
else:unix: PRE_TARGETDEPS += $$PWD/jpeg-9c/.libs/libjpeg.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/jpeg-9c/.libs/release/ -ljpeg
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/jpeg-9c/.libs/debug/ -ljpeg
else:unix: LIBS += -L$$PWD/jpeg-9c/.libs/ -ljpeg

INCLUDEPATH += $$PWD/jpeg-9c/.libs
DEPENDPATH += $$PWD/jpeg-9c/.libs
