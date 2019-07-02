TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += bib
INCLUDEPATH += gui_glut
INCLUDEPATH += pessoal

LIBS += -lGL -lGLU -lglut -l3ds -lSDL_image

SOURCES += main.cpp \
    bib/Camera.cpp \
    bib/CameraDistante.cpp \
    bib/CameraJogo.cpp \
    bib/Desenha.cpp \
    bib/model3ds.cpp \
    bib/Vetor3D.cpp \
    gui_glut/extra.cpp \
    gui_glut/gui.cpp \
    bib/Curva.cpp \
    bib/Objeto.cpp \
    bib/Pista.cpp \
    bib/Ufo.cpp \
    bib/texturemanager.cpp \
    bib/nave.cpp

HEADERS += \
    bib/Camera.h \
    bib/CameraDistante.h \
    bib/CameraJogo.h \
    bib/Desenha.h \
    bib/model3ds.h \
    bib/Vetor3D.h \
    gui_glut/extra.h \
    gui_glut/gui.h \
    bib/Curva.h \
    bib/Objeto.h \
    bib/Pista.h \
    bib/Ufo.h \
    bib/texturemanager.h \
    bib/nave.h
