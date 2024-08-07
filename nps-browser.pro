TEMPLATE = app
TARGET = nps-browser
INCLUDEPATH += .

# Input
SOURCES += src/main.cpp src/fs/config.cpp src/ui/tsv.cpp
greaterThan(QT_MAJOR_VERSION, 4): QT += core gui widgets network