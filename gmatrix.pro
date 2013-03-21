TEMPLATE = app
CONFIG -= qt
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SOURCES += \
    main.cpp \
    Game.cpp \
    MediaManager.cpp \
    tools.cpp \
    Graph.cpp \
    MyScene.cpp \
    GridScene.cpp

HEADERS += \
    Scene.hpp \
    MediaManager.hpp \
    Game.hpp \
    tools.hpp \
    Graph.hpp \
    Node.hpp \
    MyScene.hpp \
    GridScene.hpp
