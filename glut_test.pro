
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    work_test/arc.cpp \
    shader/shader.cpp

HEADERS += \
    work_test/arc.h \
    shader/shader.h \
    engine/particle.h \
    engine/object.h \
    engine/component.h \
    engine/manager_draw.h \
    engine/manager_physics.h \
    engine/manager.h

LIBS += -lGL -lGLEW -lglut -lIL

OTHER_FILES += \
    shader/default.frag \
    shader/default.vert

INCLUDEPATH += ../glm
