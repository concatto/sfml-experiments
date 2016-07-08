TEMPLATE = app
CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-graphics -lsfml-window -lsfml-system

SOURCES += \
    Animation.cpp \
    Character.cpp \
    Particle.cpp \
    ParticleEmitter.cpp \
    Tile.cpp \
    Utility.cpp \
    World.cpp \
    main.cpp

HEADERS += \
    Animation.h \
    Character.h \
    Particle.h \
    ParticleEmitter.h \
    Tile.h \
    Utility.h \
    World.h

