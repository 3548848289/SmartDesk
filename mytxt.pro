QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DLfromNet.cpp \
    DatabaseManager.cpp \
    EditedLog.cpp \
    RecentFilesManager.cpp \
    Setting.cpp \
    TabHandleCSV.cpp \
    TabHandleTXT.cpp \
    TagItemDelegate.cpp \
    WFileTag.cpp \
    WOnlineDoc.cpp \
    WidgetFunctional.cpp \
    csvLinkServer2.cpp \
    main.cpp \
    mainwindow.cpp \
    myJson.cpp

HEADERS += \
    DLfromNet.h \
    DatabaseManager.h \
    EditedLog.h \
    RecentFilesManager.h \
    Setting.h \
    TabAbstract.h \
    TabHandleCSV.h \
    TabHandleTXT.h \
    TagItemDelegate.h \
    WFileTag.h \
    WOnlineDoc.h \
    WidgetFunctional.h \
    csvLinkServer2.h \
    mainwindow.h \
    myJson.h

FORMS += \
    DLfromNet.ui \
    Setting.ui \
    WFileTag.ui \
    WOnlineDoc.ui \
    WidgetFunctional.ui \
    csvLinkServer2.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=
