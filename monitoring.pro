QT       += core gui network charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += /usr/local/include  #LIBS te yazılacak dosyaları bu dosya yolunda arar..
LIBS += -L/usr/local/lib
LIBS += -lgrpc++
LIBS += /usr/local/lib/libprotobuf.a

SOURCES += \
    diskmonitor.cpp \
    drawchart.cpp \
    main.cpp \
    mainwindow.cpp \
	monitoring.grpc.pb.cc \
	monitoring.pb.cc

HEADERS += \
    diskmonitor.h \
    drawchart.h \
    mainwindow.h \
	monitoring.grpc.pb.h \
	monitoring.pb.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    diskio.proto

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/lib/release/ -labsl_synchronization
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/lib/debug/ -labsl_synchronization
else:unix: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -labsl_synchronization

INCLUDEPATH += $$PWD/../../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../../usr/local/include
