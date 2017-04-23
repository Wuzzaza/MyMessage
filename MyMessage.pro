#-------------------------------------------------
#
# Project created by QtCreator 2017-04-23T09:32:34
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyMessage
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    loginform.cpp \
    filemanager.cpp \
    privatemessage.cpp \
    networkmanager.cpp

HEADERS  += mainwindow.h \
    loginform.h \
    filemanager.h \
    privatemessage.h \
    networkmanager.h

FORMS    += mainwindow.ui \
    loginform.ui \
    privatemessage.ui
