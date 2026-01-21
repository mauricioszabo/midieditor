QT += testlib
QT -= gui

CONFIG += c++17
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

# Include source directory
INCLUDEPATH += ../src/midi

# Source files under test
SOURCES += \
    ../src/midi/ChordDetector.cpp \
    ChordDetectorTest.cpp

HEADERS += \
    ../src/midi/ChordDetector.h
