#include "seta_controller.h"

Seta_Controller::Seta_Controller(SubteStatus * modelo, Seta_Button * view, TractionHardware *th)
{
    m_setaButton = view;
    m_modelo = modelo;
    m_tractionHardware = th;

    connect(m_setaButton,SIGNAL(m_pressed()),this, SLOT(pushSeta()));
    connect(m_setaButton, SIGNAL(m_released()),this, SLOT(pullSeta()));
    connect(m_tractionHardware,SIGNAL(seta(int)),this,SLOT(processValue(int)));

}

void Seta_Controller::pushSeta(){
    //qDebug() << "Entro en controller.pushSeta";
    m_modelo->setaActivated();
}

void Seta_Controller::pullSeta(){
    //qDebug() << "Entro en controller.pullSeta";
    m_modelo->setaDeactivated();
}

QVariant Seta_Controller::isPressed(){
    // return seta's state from the model
    return(this->m_modelo->seta());
}

void Seta_Controller::setaPressed()
{
    m_setaButton->setOn();
}

void Seta_Controller::setaReleased()
{
    m_setaButton->setOff();
}

Seta_Controller::~Seta_Controller()
{
    delete m_modelo;
    delete this->m_setaButton;
}

void Seta_Controller::resetToOff()
{
    m_setaButton->setOff();
}

void Seta_Controller::processValue(int v){
    if (v==1){
        m_modelo->setaActivated();
        setaPressed();
    }else if (v==0){
        m_modelo->setaDeactivated();
        setaReleased();
    }
}
