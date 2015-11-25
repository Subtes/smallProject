#include "emergencyoverride_controller.h"

EmergencyOverride_Controller::EmergencyOverride_Controller(SubteStatus *subte, SingleButton *button)
{
    m_subte = subte;
    m_button = button;

    m_button->setNestled(true);
    m_button->setLighted(true);

    connect(m_button,SIGNAL(buttonClicked()),this,SLOT(emergencyOverrideClicked()));
}

EmergencyOverride_Controller::~EmergencyOverride_Controller()
{

}

void EmergencyOverride_Controller::emergencyOverrideClicked()
{
    if(m_button->buttonState())
    {
        m_button->stopBlink();
    }else{
        m_button->startBlink();
    }
    m_subte->emergencyOverridePressed();
}
