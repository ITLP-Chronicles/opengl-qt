QT       += core gui
QT       += openglwidgets
LIBS     += -lopengl32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    linea.cpp \
    main.cpp \
    mainwindow.cpp \
    matriz3d.cpp \
    objeto3d.cpp \
    openglwidget.cpp \
    superficie.cpp \
    utils.cpp \
    vertice.cpp

HEADERS += \
    linea.h \
    mainwindow.h \
    matriz3d.h \
    objeto3d.h \
    openglwidget.h \
    superficie.h \
    utils.h \
    vertice.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
