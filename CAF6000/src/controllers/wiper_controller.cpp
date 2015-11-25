#include "wiper_controller.h"

Wiper_Controller::Wiper_Controller(SubteStatus * subte, Wiper * wiper)
{
    m_subte = subte;
    m_wiper = wiper;

    connect(m_wiper,SIGNAL(wiperOn()),m_subte,SLOT(wiperOn()));
    connect(m_wiper,SIGNAL(wiperOff()),m_subte,SLOT(wiperOff()));
    connect(m_wiper,SIGNAL(washer()),m_subte,SLOT(washer()));

}

Wiper_Controller::~Wiper_Controller()
{

}

