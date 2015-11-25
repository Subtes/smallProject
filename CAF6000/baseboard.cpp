#include "baseboard.h"

BaseBoard::BaseBoard(QWidget *parent, SubteStatus *subte, EventHandler *eventHandler) :
    QMainWindow(parent)
{
    //SUBTE Model
    m_subte = subte;
    m_eventHandler = eventHandler;
}

BaseBoard::~BaseBoard()
{

}
