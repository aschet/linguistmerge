QT       += core gui widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32:VERSION = 1.0.0.0
else:VERSION = 1.0.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

QMAKE_TARGET_COMPANY=Thomas Ascher
QMAKE_TARGET_DESCRIPTION=Merge Utility for Qt Localization TS Files
QMAKE_TARGET_COPYRIGHT=Copyright (C) 2021  Thomas Ascher
QMAKE_TARGET_PRODUCT=LinguistMerge
RC_ICONS=linguistmerge.ico

SOURCES += \
    aboutdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    mergemodel.cpp \
    waitcursorscope.cpp

HEADERS += \
    aboutdialog.h \
    mainwindow.h \
    mergemodel.h \
    waitcursorscope.h

FORMS += \
    aboutdialog.ui \
    mainwindow.ui

RESOURCES += \
    linguistmerge.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../core/release/ -lcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../core/debug/ -lcore
else:unix: LIBS += -L$$OUT_PWD/../core/ -lcore

INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../core/release/libcore.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../core/debug/libcore.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../core/release/core.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../core/debug/core.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../core/libcore.a
