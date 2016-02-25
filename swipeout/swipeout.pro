TEMPLATE = app
TARGET = swipeout

load(ubuntu-click)

QT += qml quick multimedia

QMAKE_CXXFLAGS += -Werror
CONFIG += c++11

SOURCES += main.cpp \
    gameengine.cpp \
    level.cpp \
    levels.cpp \
    block.cpp \
    blocks.cpp \
    board.cpp \
    boardsolver.cpp \
    levelcreator.cpp \
    move.cpp \
    levelpack.cpp \
    levelpacks.cpp \
    settings.cpp

HEADERS += \
    gameengine.h \
    level.h \
    levels.h \
    block.h \
    blocks.h \
    board.h \
    boardsolver.h \
    levelcreator.h \
    move.h \
    levelpack.h \
    levelpacks.h \
    settings.h

RESOURCES += swipeout.qrc \
             images.qrc

QML_FILES += $$files(*.qml,true) \
             $$files(*.js,true)

OTHER_FILES += $${QML_FILES} \

# Default rules for deployment.
target.path = $${UBUNTU_CLICK_BINARY_PATH}
INSTALLS+=target
