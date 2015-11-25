#include "tractionlever_controller.h"

TractionLever_Controller::TractionLever_Controller(SubteStatus * subte, TractionLever * tractionLever, TractionHardware *th)
{
    m_subte = subte;
    m_tractionLever = tractionLever;
    m_tractionHardware = th;

    m_checkJ = new QTimer();
    m_checkJ->setInterval(50);

    m_checkB = new QTimer();
    m_checkB->setInterval(250);

    connect(m_checkJ,SIGNAL(timeout()),m_tractionHardware,SLOT(processValueChanged()));
    connect(m_checkB,SIGNAL(timeout()),m_tractionHardware,SLOT(processRanaChanged()));
    connect(m_checkB,SIGNAL(timeout()),m_tractionHardware,SLOT(processSetaChanged()));
    connect(m_checkB,SIGNAL(timeout()),m_tractionHardware,SLOT(processBottonChanged()));
    connect(m_tractionHardware,SIGNAL(positionChanged(int)),this,SLOT(processValue(int)));
    connect(m_tractionLever,SIGNAL(positionChanged(int)),this,SLOT(processValue(int)));
}

TractionLever_Controller::~TractionLever_Controller()
{

}

void TractionLever_Controller::setValue(int v)
{
    m_tractionLever->setValue(v);
}

void TractionLever_Controller::onTractionLever(){
    bool check = m_tractionHardware->isHardwareEnable();
    if (check){
        m_tractionHardware->reset();
        m_checkJ->start();
        m_checkB->start();
        qDebug()<<"Hardware ON: Palanca, HV, Seta, Rana";
    }else{
        qDebug()<<"No Hardware";
    }
}

void TractionLever_Controller::offTractionLever(){
    if (m_tractionHardware->isHardwareEnable()){
        m_checkJ->stop();
        m_checkB->stop();
        qDebug()<<"Hardware OFF: Palanca, HV, Seta, Rana";
    }else{
        qDebug()<<"No Hardware";
    }
}

void TractionLever_Controller::processValue(int value){

    if (value > 100){
        qDebug()<<" Valor de Traction MAYOR a 100, Controlar limites de parametros de configuracion de Joystick/Traccion! "<< value;
        value = 100;
    }else if (value < -100){
        qDebug()<<" Valor de Traction MENOR a -100, Controlar limites de parametros de configuracion de Joystick/Traccion! "<< value;
        value = -100;
    }

    if(value > 15){
        int tr = static_cast<int>((((double)value-15.0)/85.0)*100.0);
        m_subte->tractionReceived(tr);
        m_tractionLever->setValue(value);
        //qDebug()<<"Valor de Joystick:  ---TRACTION------>"<< value;
    }else if((value <= 15)&&(value >= -15)){
        m_subte->tractionReceived(0);
        m_subte->brakeReceived(0);
        m_tractionLever->setValue(0);
        //qDebug()<<"Valor de Joystick:  ---BRAKE & TRACTION------> 0";
    }else if ((value < -15) && (value >= -95)){
        int br = static_cast<int>((((double)((-1)*value)-15.0)/80.0)*100.0);
        m_subte->brakeReceived(br);
        m_tractionLever->setValue(value);
        //qDebug()<<"Valor de Joystick:  ---BRAKE------>"<< value;
    }else if (value < -95){
        m_subte->brakeReceived(100);
        m_tractionLever->setValue(-100);
        //qDebug()<<"Valor de Joystick:  ---BRAKE EMERGENCY!!!!!!------";
    }
}
