#include "horn_controller.h"

Horn_Controller::Horn_Controller(SubteStatus *subte,FootHorn *pedal)
{
    m_subte = subte;
    m_pedal = pedal;

    connect(m_pedal,SIGNAL(hornPressed()),m_subte,SLOT(hornOn()));
    connect(m_pedal,SIGNAL(hornReleased()),m_subte,SLOT(hornOff()));
}

Horn_Controller::~Horn_Controller()
{

}

void Horn_Controller::setBocina(bool v)
{
    m_pedal->setBocina(v);
}
