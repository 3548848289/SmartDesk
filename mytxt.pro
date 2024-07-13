QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    downLoad.cpp \
    epoll.cpp \
    main.cpp \
    mainwindow.cpp \
    tab.cpp \
    tabletab.cpp \
    texttab.cpp

HEADERS += \
    abstracttab.h \
    downLoad.h \
    epoll.h \
    mainwindow.h \
    tab.h \
    tabletab.h \
    texttab.h

FORMS += \
    downLoad.ui \
    epoll.ui \
    mainwindow.ui \
    tab.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
