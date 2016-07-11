TEMPLATE = app
CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -D__NO_INLINE__

win32 {
    INCLUDEPATH += "C:\Users\Fernando\Downloads\SFML-2.3.2-sources\SFML-2.3.2\include"
    LIBS += -L"C:\Users\Fernando\Downloads\SFML-2.3.2-sources\SFML-2.3.2\binaries\lib"
    LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main
}

!win32 {
    LIBS += -lsfml-graphics -lsfml-window -lsfml-system
}

SOURCES += \
    Animation.cpp \
    Character.cpp \
    Particle.cpp \
    ParticleEmitter.cpp \
    Tile.cpp \
    Utility.cpp \
    World.cpp \
    main.cpp \
    MovementManager.cpp \
    AnimationManager.cpp

HEADERS += \
    Animation.h \
    Character.h \
    Particle.h \
    ParticleEmitter.h \
    Tile.h \
    Utility.h \
    World.h \
    MovementManager.h \
    AnimationManager.h

