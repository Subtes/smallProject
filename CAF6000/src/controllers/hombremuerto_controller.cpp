#include "hombremuerto_controller.h"

HombreMuerto_Controller::HombreMuerto_Controller(SubteStatus *subte, TractionLever *slider, TractionHardware *th)
{
    m_subte = subte;
    m_slider = slider;
    m_tractionHardware = th;

    connect(m_slider,SIGNAL(hvPressed()),m_subte,SLOT(hombreMuertoPressed()));
    connect(m_slider,SIGNAL(hvReleased()),m_subte,SLOT(hombreMuertoReleased()));
    connect(m_tractionHardware,SIGNAL(manDiedPressed()),m_subte,SLOT(hombreMuertoPressed()));
    connect(m_tractionHardware,SIGNAL(manDiedReleased()),m_subte,SLOT(hombreMuertoReleased()));
}

HombreMuerto_Controller::~HombreMuerto_Controller()
{

}

