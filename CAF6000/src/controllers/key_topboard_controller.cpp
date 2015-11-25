#include "key_topboard_controller.h"

Key_TopBoard_Controller::Key_TopBoard_Controller(SubteStatus *modelo, LlaveTecho *view, TractionHardware * th)
{
    m_keyButton = view;
    m_modelo = modelo;
    m_tractionHardware = th;

    m_checkJ = new QTimer();
    m_checkJ->setInterval(750);

    connect(m_keyButton,SIGNAL(kHardPressed()),this, SLOT(keyON()));
    connect(m_keyButton, SIGNAL(lHardPressed()),this, SLOT(keyOFF()));
    // Basicamente m_checkJ le dice a m_tractionHardware (el traction me quedo arrastrado, seria hardware) cada cuanto quiere chequear.
    connect(m_tractionHardware,SIGNAL(processKeyTop(int)),this,SLOT(processKeyTop(int)));
    connect(m_checkJ,SIGNAL(timeout()),m_tractionHardware,SLOT(processKeyTop()));
}

void Key_TopBoard_Controller::keyON(){
    qDebug() << "Entro en controller.keyON";
    m_modelo->keyActivated();
    m_modelo->setModeOperation(5);
}

void Key_TopBoard_Controller::keyOFF(){
    qDebug() << "Entro en controller.keyOFF";
    m_modelo->keyDeactivated();
    m_modelo->setModeOperation(1);
}

void Key_TopBoard_Controller::keyTurnON()
{
    m_keyButton->setOn();
}

void Key_TopBoard_Controller::keyTurnOFF()
{
    m_keyButton->setOff();
}

Key_TopBoard_Controller::~Key_TopBoard_Controller()
{
    delete m_modelo;
    delete m_keyButton;
}

void Key_TopBoard_Controller::resetToOff()
{
    m_keyButton->setOff();
}

QVariant Key_TopBoard_Controller::isON(){
    // return keyATP's state from the model
    return(m_modelo->keyTopBoard());
}

void Key_TopBoard_Controller::processKeyTop(int k){
    if (k==1){
        m_keyButton->setOn();
        qDebug()<< "LLave (Joystick) Techo: ON";
    }else{
        m_keyButton->setOff();
    }
}

void Key_TopBoard_Controller::onKeyHD(){
    if (m_tractionHardware->isHardwareEnable()){
        m_tractionHardware->reset();
        m_checkJ->start();
        qDebug()<<"Hardware ON: LLave Hardware ON";
    }else{
        qDebug()<<"No Hardware Key";
    }
}

void Key_TopBoard_Controller::offKeyHD(){
    if (m_tractionHardware->isHardwareEnable()){
        m_checkJ->stop();
        qDebug()<<"Hardware OFF: LLave Hardware OFF";
    }else{
        qDebug()<<"No Hardware Key";
    }
}

