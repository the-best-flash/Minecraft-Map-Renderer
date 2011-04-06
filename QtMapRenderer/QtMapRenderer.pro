#-------------------------------------------------
#
# Project created by QtCreator 2011-01-14T14:57:24
#
#-------------------------------------------------

QT       += core gui

TARGET = QtMapRenderer
TEMPLATE = app


SOURCES += main.cpp\
        renderoptions.cpp \
    point.cpp \
    nbt.c \
    Map.cpp \
    FileEnumeration.cpp \
    endianness.c \
    Color.cpp \
    Chunk.cpp

HEADERS  += renderoptions.h \
    renderoptions.h \
    point.h \
    nbt.h \
    Map.h \
    FileEnumeration.h \
    endianness.h \
    Color.h \
    Chunk.h

QMAKE_CXXFLAGS += -fopenmp

LIBS += -lgomp

INCLUDEPATH += zlib125-dll/include IL

unix:LIBS += -lzlib -lil

win32:LIBS += -L"C:\\Users\\Colton\\Desktop\\NBT_Library\\MapRenderer\\QtMapRenderer\\zlib125-dll\\lib" -lzdll -L"C:\\Users\\Colton\\Desktop\\NBT_Library\\MapRenderer\\DevIL" -lDevIL

FORMS    += renderoptions.ui
