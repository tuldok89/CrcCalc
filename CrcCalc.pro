#-------------------------------------------------
#
# Project created by QtCreator 2013-09-08T15:15:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CrcCalc
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    crc32.cpp \
    mysetting.cpp \
    filecrc32.cpp \
    lz_crc32.cpp

HEADERS  += mainwindow.h \
    crc32.h \
    mysetting.h \
    filecrc32.h \
    crc_macros.h \
    lz_crc32_table.h \
    lz_crc32.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

RC_FILE += \
    icon.rc

OTHER_FILES += \
    "./icons/MAX.ico" \
    "./icons/XCM.ico" \
    "icon.rc"

*-g++:QMAKE_CXXFLAGS = "-std=c++0x -flto"
