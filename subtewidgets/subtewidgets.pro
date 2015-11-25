QT += core gui quick quickwidgets widgets
#declarative

TEMPLATE = lib

CONFIG += release

HEADERS += \
#    tractionlever.h \
#    speedgauge.h \
    foothorn.h \
#    wiper.h \
#    rana.h \
    seta_button.h \
#    singlebutton.h \
#    speedgaugeleds.h \
#    atp.h \
#    analoggauge.h \
#    manometer.h \
#    sicasmac.h \
#    llavemodoconduccion.h \
#    llavetecho.h \
    tractionhardware.h \
#    alstomtractionlever.h \
#    alstomselectormodoconduccion.h

SOURCES += \
#    tractionlever.cpp \
#    speedgauge.cpp \
    foothorn.cpp \
#    wiper.cpp \
#    rana.cpp \
    seta_button.cpp \
#    singlebutton.cpp \
#    speedgaugeleds.cpp \
#    atp.cpp \
#    analoggauge.cpp \
#    manometer.cpp \
#    sicasmac.cpp \
#    llavemodoconduccion.cpp \
#    llavetecho.cpp \
    tractionhardware.cpp \
#    alstomtractionlever.cpp \
#    alstomselectormodoconduccion.cpp

FORMS += \
#    tractionlever.ui \
#    speedgauge.ui \
    foothorn.ui \
#    wiper.ui \
#    rana.ui \
    seta_button.ui \
#    singlebutton.ui \
#    speedgaugeleds.ui \
#    atp.ui \
#    analoggauge.ui \
#    manometer.ui \
#    sicasmac.ui \
#    llavemodoconduccion.ui \
#    llavetecho.ui \
#    alstomtractionlever.ui \
#    alstomselectormodoconduccion.ui

RESOURCES += \
            qmlrsc.qrc \
            widgetsrsc.qrc

INCLUDEPATH +=  $$PWD/../Source/include

DEPENDPATH += $$PWD/../Source

LIBS += -L$$PWD/../Source/lib/ -lSDL \
        -L$$PWD/../Source/lib/ -lSDL_mixer

DISTFILES +=
