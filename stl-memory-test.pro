TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -ldl

SOURCES += \
    memory/memoryfunc.cc \
    memory/memoryhook.cc \ \
    stltest.cc

HEADERS += \
    memory/memory.h \
    memory/memoryfunc.h \
    memory/memoryhook.h \
