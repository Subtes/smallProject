//#include <tractionhardware.h>

#include "boardhardware.h"
#include "ui_boardhardware.h"


BoardHardware::BoardHardware(QWidget *parent, SubteStatus * subte, EventHandler *eventHandler) :
    BaseBoard(parent,subte,eventHandler),
    ui(new Ui::BoardHardware)
{
    ui->setupUi(this);

    connect(m_eventHandler,SIGNAL(controlReady()),this,SLOT(startBoard()));
    connect(m_eventHandler,SIGNAL(controlDisable()),this,SLOT(disableScreen()));
    connect(m_eventHandler,SIGNAL(controlEnable()),this,SLOT(enableScreen()));
    connect(m_eventHandler,SIGNAL(controlReset()),this,SLOT(resetControls()));
    connect(m_eventHandler,SIGNAL(cargarEstado(int)),this,SLOT(loadState(int)));
    connect(m_eventHandler,SIGNAL(bPressed()),this,SLOT(bocinaON()));
    connect(m_eventHandler,SIGNAL(bReleased()),this,SLOT(bocinaOFF()));
//    connect(m_eventHandler,SIGNAL(aPressed()),this,SLOT(ranaAD()));
//    connect(m_eventHandler,SIGNAL(ceroPressed()),this,SLOT(ranaCERO()));
//    connect(m_eventHandler,SIGNAL(rPressed()),this,SLOT(ranaAT()));
    connect(m_eventHandler,SIGNAL(fPressed()),this,SLOT(setaON()));
    connect(m_eventHandler,SIGNAL(tPressed()),this,SLOT(setaOFF()));

    m_horn = NULL;
//    m_tractionLever = NULL;
//    m_rana = NULL;
//    m_hombreMuerto = NULL;
    m_setaButton = NULL;

    m_tractionHardware = NULL;

}

BoardHardware::~BoardHardware()
{
    delete ui;
}

void BoardHardware::startBoard()
{
    qDebug() << "board hardware startBoard";

    m_horn = new Horn_Controller(m_subte,ui->horn);
//    m_tractionLever = new TractionLever_Controller(m_subte,ui->traction, m_tractionHardware);
//    m_rana = new Rana_Controller(m_subte,ui->ranaDevice,m_tractionHardware);
//    m_hombreMuerto = new HombreMuerto_Controller(m_subte,ui->traction, m_tractionHardware);
    m_setaButton = new Seta_Controller(m_subte, ui->setaButton, m_tractionHardware);

    this->setEnabled(false);
}

void BoardHardware::enableScreen()
{
    this->setEnabled(true);
   // m_tractionLever->onTractionLever();
}

void BoardHardware::disableScreen()
{
    this->setEnabled(false);
   // m_tractionLever->offTractionLever();
}

void BoardHardware::resetControls()
{
    loadState(lastState);
}

void BoardHardware::bocinaON()
{
    m_horn->setBocina(true);
}

void BoardHardware::bocinaOFF()
{
    m_horn->setBocina(false);
}

void BoardHardware::ranaAD()
{
    //m_rana->setValue(1);
}

void BoardHardware::ranaCERO()
{
   // m_rana->setValue(0);
}

void BoardHardware::ranaAT()
{
   // m_rana->setValue(-1);
}

void BoardHardware::setaON()
{
    m_setaButton->setaPressed();
}

void BoardHardware::setaOFF()
{
    m_setaButton->setaReleased();
}

void BoardHardware::loadState(int state){

//   // m_tractionLever->setValue(0);
//    m_setaButton->resetToOff();

//    if(state == APAGADO){
//        lastState = APAGADO;
//       // m_rana->setValue(0);
//    }
//    else if(state == EN_MARCHA){
//        lastState = EN_MARCHA;
//       // m_rana->setValue(1);
//    }

//    m_eventHandler->enableDiffusion();
}

void BoardHardware::setHardware(TractionHardware *th){
    m_tractionHardware = th;
}
