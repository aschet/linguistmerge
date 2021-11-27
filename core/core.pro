QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    context.cpp \
    location.cpp \
    message.cpp \
    ts.cpp \
    tsreader.cpp \
    tswriter.cpp

HEADERS += \
    context.h \
    location.h \
    message.h \
    ts.h \
    tsreader.h \
    tswriter.h \
    tsxmldefs.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
