QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app1
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    glwrenderer.cpp \
    sceneobject.cpp \
    camera.cpp \
    scene.cpp \
    meshbuffer.cpp \
    meshobject.cpp \
    scenemanager.cpp \
    renderer.cpp \
    shader.cpp \
    demoscene1.cpp \
    renderablevao.cpp

HEADERS  += mainwindow.h \
    glwrenderer.h \
    vdata.h \
    config.h \
    sceneobject.h \
    camera.h \
    scene.h \
    meshbuffer.h \
    meshobject.h \
    scenemanager.h \
    renderer.h \
    shader.h \
    properties.h \
    childrencontainer.h \
    log.h \
    demoscene1.h \
    renderablevao.h

RESOURCES = shaders.qrc

OTHER_FILES += \
    fshader.glsl \
    vshader.glsl
