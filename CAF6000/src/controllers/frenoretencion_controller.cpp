#include "frenoretencion_controller.h"

FrenoRetencion_Controller::FrenoRetencion_Controller(SubteStatus *subte, SingleButton *button)
    : Base_Controller(subte)
{
    m_button = button;

    m_button->setNestled(true);
    m_button->setLighted(true);

    connect(m_button,SIGNAL(buttonClicked()),this,SLOT(updateBrakeState()));
}

FrenoRetencion_Controller::~FrenoRetencion_Controller()
{
}

void FrenoRetencion_Controller::updateBrakeState()
{
    //m_button->buttonState() ? qDebug()<<"ON" : qDebug()<<"OFF" ;
    //TODO:
    m_subte->setRetentionBrakeBypass(!m_button->buttonState());
}

void FrenoRetencion_Controller::turnOn()
{
    m_button->turnOn();
    m_subte->setRetentionBrakeBypass(m_button->buttonState());
}

void FrenoRetencion_Controller::turnOff()
{
    m_button->release();
    m_button->turnOff();
    m_subte->setRetentionBrakeBypass(m_button->buttonState());
}
