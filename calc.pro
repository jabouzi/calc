TEMPLATE = app
TARGET =
DEPENDPATH += . \
 build \
 debug \
 release \
 src \
 ui
INCLUDEPATH += . src build
HEADERS += src/mainwindowimpl.h src/dsingleapplication.h
FORMS += ui/mainwindow.ui ui/untitled.ui
SOURCES += src/main.cpp src/mainwindowimpl.cpp src/dsingleapplication.cpp
RESOURCES += calc.qrc
QT += network
CONFIG += release
