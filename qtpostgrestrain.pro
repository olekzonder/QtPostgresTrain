QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    editcustomer.cpp \
    editschedule.cpp \
    editstation.cpp \
    edittrain.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    office.cpp \
    officemodel.cpp \
    officeproblemwidget.cpp \
    officewidget.cpp \
    schedule.cpp \
    schedulearchivewidget.cpp \
    scheduledialog.cpp \
    scheduleeditwidget.cpp \
    schedulemodel.cpp \
    schedulewidget.cpp \
    searchschedule.cpp \
    station.cpp \
    stationmodel.cpp \
    stationwidget.cpp \
    statsmodel.cpp \
    statswidget.cpp \
    ticketarchivewidget.cpp \
    train.cpp \
    trainmodel.cpp \
    trainwidget.cpp

HEADERS += \
    editcustomer.h \
    editschedule.h \
    editstation.h \
    edittrain.h \
    logindialog.h \
    mainwindow.h \
    office.h \
    officemodel.h \
    officeproblemwidget.h \
    officewidget.h \
    schedule.h \
    schedulearchivewidget.h \
    scheduledialog.h \
    scheduleeditwidget.h \
    schedulemodel.h \
    schedulewidget.h \
    searchschedule.h \
    station.h \
    stationmodel.h \
    stationwidget.h \
    statsmodel.h \
    statswidget.h \
    ticketarchivewidget.h \
    train.h \
    trainmodel.h \
    trainwidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
