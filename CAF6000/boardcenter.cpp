#include <tractionhardware.h>

#include "boardcenter.h"
#include "ui_boardcenter.h"

BoardCenter::BoardCenter(QWidget *parent, SubteStatus * subte, EventHandler *eventHandler) :
    BaseBoard(parent,subte,eventHandler),
    ui(new Ui::BoardCenter)
{
    ui->setupUi(this);

    m_wiper = NULL;
    m_emergencyOverride = NULL;
    m_tractionBypass = NULL;
    m_brakesBypass = NULL;
    m_speedGauge = NULL;
    m_doors = NULL;
    m_tractionHardware = NULL;


    connect(m_eventHandler,SIGNAL(controlReady()),this,SLOT(startBoard()));
    connect(m_eventHandler,SIGNAL(controlDisable()),this,SLOT(disableScreen()));
    connect(m_eventHandler,SIGNAL(controlEnable()),this,SLOT(enableScreen()));
    connect(m_eventHandler,SIGNAL(controlReset()),this,SLOT(resetControls()));
    connect(m_eventHandler,SIGNAL(cargarEstado(int)),this,SLOT(loadState(int)));

    connect(m_eventHandler,SIGNAL(masPressed()),this,SLOT(bypassTraccionON()));
    connect(m_eventHandler,SIGNAL(masReleased()),this,SLOT(bypassTraccionOFF()));
    connect(m_eventHandler,SIGNAL(menosPressed()),this,SLOT(bypassFrenoON()));
    connect(m_eventHandler,SIGNAL(menosReleased()),this,SLOT(bypassFrenoOFF()));

//    connect(m_checkBypass,SIGNAL(timeout()),m_tractionHardware,SLOT(processBottonChanged()));


    connect(m_subte,SIGNAL(bateriaCon()),this,SLOT(turnOnWidgets()));
    connect(m_subte,SIGNAL(bateriaDes()),this,SLOT(turnOffWidgets()));
}

BoardCenter::~BoardCenter()
{
    delete ui;
}

void BoardCenter::startBoard()
{
    qDebug() << "board center startBoard";

    m_wiper = new Wiper_Controller(m_subte,ui->wiper);;
    m_emergencyOverride = new EmergencyOverride_Controller(m_subte,ui->anulacionEmergencia);
    m_tractionBypass = new TractionBypass_Controller(m_subte,ui->bypassTraccion, m_tractionHardware);
    m_brakesBypass = new BrakeBypass_Controller(m_subte,ui->bypassFreno, m_tractionHardware);
    m_speedGauge = new SpeedGaugeLeds_Controller(m_subte,ui->velocimetro);
    m_doors = new Doors_Controller(m_subte, ui->abrirIzquierda, ui->cerrarIzquierda, ui->selectorIzquierda, ui->abrirDerecha, ui->cerrarDerecha, ui->selectorDerecha, ui->silbato);

    ui->megafonia->setButtonImage(QUrl("qrc:/resources/blueON.png"),QUrl("qrc:/resources/blueplane.png"));
    ui->antivaho->setButtonImage(QUrl("qrc:/resources/blueON.png"),QUrl("qrc:/resources/blueplane.png"));
    ui->iluminacionReducPulsad->setButtonImage(QUrl("qrc:/resources/blueON.png"),QUrl("qrc:/resources/blueplane.png"));
    ui->iluminacionPulsadores->setButtonImage(QUrl("qrc:/resources/blueON.png"),QUrl("qrc:/resources/blueplane.png"));
    ui->faros->setButtonImage(QUrl("qrc:/resources/blueON.png"),QUrl("qrc:/resources/blueplane.png"));
    ui->luzCabina->setButtonImage(QUrl("qrc:/resources/luzcabinaON.png"),QUrl("qrc:/resources/luzcabina.png"));
    ui->publicoCabina->setButtonImage(QUrl("qrc:/resources/publico-cabinaR.png"),QUrl("qrc:/resources/publico-cabinaL.png"));
    ui->modoConduccion->setClearColor(Qt::transparent);
    ui->modoConduccion->setAttribute(Qt::WA_AlwaysStackOnTop);

    this->setEnabled(false);

    connect(ui->bypassFrenoTraccion,SIGNAL(pressed()),m_brakesBypass,SLOT(bypassBrakePressed()));
    connect(ui->bypassFrenoTraccion,SIGNAL(pressed()),m_tractionBypass,SLOT(pressBypass()));
    connect(ui->bypassFrenoTraccion,SIGNAL(released()),m_brakesBypass,SLOT(bypassBrakeReleased()));
    connect(ui->bypassFrenoTraccion,SIGNAL(released()),m_tractionBypass,SLOT(releaseBypass()));

    //m_checkBypass->stop();

}

void BoardCenter::enableScreen()
{
    this->setEnabled(true);
    m_tractionBypass->onBypassHD();
}

void BoardCenter::disableScreen()
{
    this->setEnabled(false);
    m_tractionBypass->offBypassHD();
}

void BoardCenter::resetControls(){
    m_doors->reset();
    loadState(lastState);
}

void BoardCenter::loadState(int state){
    ui->megafonia->turnOff();
    ui->antivaho->turnOff();
    ui->iluminacionReducPulsad->turnOff();
    ui->iluminacionPulsadores->turnOff();
    ui->faros->turnOff();
    ui->luzCabina->turnOff();
    ui->publicoCabina->turnOff();
    ui->anulacionEmergencia->turnOff();
    ui->velocimetro->updateSpeed(0);
    ui->velocimetro->updateTargetSpeed(0);

    m_brakesBypass->bypassBrakeReleased();
    m_tractionBypass->releaseBypass();



    if(state == APAGADO){
        lastState = APAGADO;
        m_doors->turnOff();
        ui->velocimetro->turnOff();
    }
    else if(state == EN_MARCHA){
        lastState = EN_MARCHA;
        m_doors->turnOn();
        ui->velocimetro->turnOn();
        ui->bypassFreno->turnOn();
        ui->bypassTraccion->turnOn();

    }

    m_eventHandler->enableDiffusion();
}

void BoardCenter::bypassFrenoON(){
    m_brakesBypass->bypassBrakePressed();
}

void BoardCenter::bypassFrenoOFF(){
    m_brakesBypass->bypassBrakeReleased();
}

void BoardCenter::bypassTraccionON(){
    m_tractionBypass->pressBypass();
}

void BoardCenter::bypassTraccionOFF(){
    m_tractionBypass->releaseBypass();
}


void BoardCenter::turnOnWidgets()
{
    m_doors->turnOn();
    ui->velocimetro->turnOn();
    ui->bypassFreno->setLighted(true);
    ui->bypassTraccion->setLighted(true);

    m_brakesBypass->bypassBrakeReleased();
    m_tractionBypass->releaseBypass();
}

void BoardCenter::turnOffWidgets()
{
    m_doors->turnOff();
    ui->velocimetro->turnOff();
    ui->bypassFreno->turnOff();
    ui->bypassTraccion->turnOff();

    ui->bypassFreno->setLighted(false);
    ui->bypassTraccion->setLighted(false);
}
void BoardCenter::setHardware(TractionHardware *th){
    m_tractionHardware = th;
}
