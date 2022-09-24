QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aliasdisplay.cpp \
    bargraph.cpp \
    #bmdata.cpp \
    #bmtree.cpp \
    dial.cpp \
    filterctrl.cpp \
    filterdisplay.cpp \
    freqdisplay.cpp \
    keypad.cpp \
    main.cpp \
    mainwindow.cpp \
    meter.cpp \
    modectrl.cpp \
    modedisplay.cpp \
    #monitor.cpp \
    pcrio.cpp \
    pcrproxy.cpp \
    qtpcr.cpp \
    scan.cpp \
    #scandialog.cpp \
    squctrl.cpp \
    volctrl.cpp

HEADERS += \
    aliasdisplay.h \
    bargraph.h \
    #bmdata.h \
    #bmtree.h \
    dial.h \
    filterctrl.h \
    filterdisplay.h \
    freqdisplay.h \
    keypad.h \
    mainwindow.h \
    meter.h \
    modectrl.h \
    modedisplay.h \
    #monitor.h \
    pcrio.h \
    pcrproto.h \
    pcrproxy.h \
    qtpcr.h \
    scan.h \
    #scandialog.h \
    squctrl.h \
    tips.h \
    volctrl.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
