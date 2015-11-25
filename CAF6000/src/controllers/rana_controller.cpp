#include "rana_controller.h"

Rana_Controller::Rana_Controller(SubteStatus *modelo, Rana *vista, TractionHardware *th){

    this->m_subte = modelo;
    this->m_ranaTraction = vista;
    this->m_tractionHardware = th;

    connect(m_ranaTraction,SIGNAL(ranaAD()),m_subte,SLOT(ranaAD()));
    connect(m_ranaTraction,SIGNAL(ranaCERO()),m_subte,SLOT(ranaCERO()));
    connect(m_ranaTraction,SIGNAL(ranaAT()),m_subte,SLOT(ranaAT()));
    connect(m_tractionHardware,SIGNAL(ranaY(int)),this,SLOT(setValue(int)));
}

Rana_Controller::~Rana_Controller(){

}

void Rana_Controller::setValue(int v)
{
    m_ranaTraction->setValue(v);

}

void Rana_Controller::processValue(int v){

    if (v == 1){
        setValue(1);
        //m_subte->ranaAD();
        qDebug()<< "RANA AD Controller";
    }else if (v == 0){
        setValue(0);
        //m_subte->ranaCERO();
        qDebug()<< "RANA Cero Controller";
    }else if (v == -1){
        setValue(-1);
        //m_subte->ranaAT();
        qDebug()<< "RANA AT Controller";
    }else{
        qDebug()<< "ERROR Rana posicion no valida";
    }

}
