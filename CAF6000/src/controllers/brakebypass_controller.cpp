#include "brakebypass_controller.h"

BrakeBypass_Controller::BrakeBypass_Controller(SubteStatus *subte, SingleButton *button, TractionHardware *th)
    : Base_Controller(subte)
{
    m_subte = subte;
    m_button = button;
    m_tractionHardware = th;

    m_button->setNestled(false);
    m_button->setLighted(true);
    m_button->setOnPressAsDriver();
    m_button->setLightManagement(false);

    m_button->setButtonImage(QUrl("qrc:/resources/redON.png"),QUrl("qrc:/resources/red.png"));

    updateHiloLazoStatus(m_subte->getHiloLazo());

    connect(m_button,SIGNAL(buttonPressed()),this,SLOT(bypassBrakePressed()));
    connect(m_button,SIGNAL(buttonReleased()),this,SLOT(bypassBrakeReleased()));
    connect(m_subte,SIGNAL(hiloLazoChanged(bool)),this,SLOT(updateHiloLazoStatus(bool)));
    connect(m_tractionHardware,SIGNAL(brakeBypassPressed()),this,SLOT(bypassBrakePressed()));
    connect(m_tractionHardware,SIGNAL(brakeBypassReleased()),this,SLOT(bypassBrakeReleased()));    

}

BrakeBypass_Controller::~BrakeBypass_Controller()
{
}

void BrakeBypass_Controller::bypassBrakePressed()
{
    m_subte->bypassBrake(true);
    qDebug()<<"BYPASS ACTIVATES";
    if(m_button->isLighted())
        m_button->turnOn();
}

void BrakeBypass_Controller::bypassBrakeReleased()
{
    m_subte->bypassBrake(false);
    qDebug()<<"BYPASS DEACTIVATED";
    this->updateHiloLazoStatus(m_subte->getHiloLazo());
}

void BrakeBypass_Controller::updateHiloLazoStatus(bool status)
{
    if(m_button->isLighted()){
        if(status){
            m_button->turnOn();
        }else{
            m_button->turnOff();
        }
    }
}

