#ifndef BASEBOARD_H
#define BASEBOARD_H

#include <QMainWindow>
#include "src/models/subtestatus.h"
#include "src/controllers/eventhandler.h"


class BaseBoard : public QMainWindow
{
    Q_OBJECT

public:

    static const int EN_MARCHA = 1;
    static const int APAGADO = 0;

    explicit BaseBoard(QWidget *parent = 0, SubteStatus *subte = 0, EventHandler *eventHandler = 0);
    ~BaseBoard();

public slots:
    virtual void startBoard()=0;
    virtual void enableScreen()=0;
    virtual void disableScreen()=0;
    virtual void resetControls()=0;
    virtual void loadState(int state)=0;

protected:
    SubteStatus     *m_subte;
    EventHandler    *m_eventHandler;

    int lastState=APAGADO;
};

#endif // BASEBOARD_H
