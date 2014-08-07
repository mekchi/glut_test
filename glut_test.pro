
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    work_test/arc.cpp \
    shader/shader.cpp \
    engine/environment.cpp \
    scripttest.cpp \
    material/material.cpp \
    engine/system_physics.cpp \
#    engine/memory.cpp

HEADERS += \
    work_test/arc.h \
    shader/shader.h \
    engine/particle.h \
    engine/object.h \
    engine/component.h \
    engine/manager.h \
    engine/system_draw.h \
    engine/system_physics.h \
#    engine/memory.h \
#    engine/system_global.h
    engine/environment.h \
    scripttest.h \
    material/material.h

LIBS += -lGL -lGLEW -lglut -lIL

OTHER_FILES += \
    shader/default.frag \
    shader/default.vert \
    lua_test.lua

INCLUDEPATH += ../glm
