#include "topboardconnectors_controller.h"

TopBoardConnectors_Controller::TopBoardConnectors_Controller(SubteStatus *subte)
{
    m_subte = subte;
}

TopBoardConnectors_Controller::~TopBoardConnectors_Controller()
{

}

void TopBoardConnectors_Controller::setBattery(SingleButton *batteryCon, SingleButton *batteryDes)
{
    m_batteryCon = batteryCon;
    m_batteryDes = batteryDes;

    m_batteryCon->setButtonImage(QUrl("qrc:/resources/redON_CON_techo.png"),QUrl("qrc:/resources/red_CON_techo.png"));
    m_batteryDes->setButtonImage(QUrl("qrc:/resources/greenON_DES_techo.png"),QUrl("qrc:/resources/green_DES_techo.png"));

    m_subte->setBatteryConnector(FALSE);

    connect(m_batteryCon,SIGNAL(buttonPressed()),this,SLOT(batteryConPressed()));
    connect(m_batteryDes,SIGNAL(buttonPressed()),this,SLOT(batteryDesPressed()));

    connect(m_batteryCon,SIGNAL(buttonPressed()),this,SIGNAL(batteryCon()));
    connect(m_batteryDes,SIGNAL(buttonPressed()),this,SIGNAL(batteryDes()));
}

void TopBoardConnectors_Controller::setConmutadorPuestaServicio(SingleButton *conmutador,SingleButton *luzLlaveDes,SingleButton *luzLlaveCon, SingleButton *arranqueDes,SingleButton *arranqueCon){
    m_conmutador = conmutador;
    m_conmutador->setButtonImage(QUrl("qrc:/resources/techo_manual_up.png"),QUrl("qrc:/resources/techo_manual_down.png"));

    m_luzLlaveDes = luzLlaveDes;
    m_luzLlaveDes->setButtonImage(QUrl("qrc:/resources/greenON_DES_techo.png"),QUrl("qrc:/resources/green_DES_techo.png"));
    m_luzLlaveDes->setClickeable(false);

    m_luzLlaveCon = luzLlaveCon;
    m_luzLlaveCon->setButtonImage(QUrl("qrc:/resources/redON_CON_techo.png"),QUrl("qrc:/resources/red_CON_techo.png"));
    m_luzLlaveCon->setClickeable(false);

    m_arranqueDes = arranqueDes;
    m_arranqueDes->setButtonImage(QUrl("qrc:/resources/greenON_DES_techo.png"),QUrl("qrc:/resources/green_DES_techo.png"));
    m_arranqueDes->setClickeable(false);

    m_arranqueCon = arranqueCon;
    m_arranqueCon->setButtonImage(QUrl("qrc:/resources/redON_CON_techo.png"),QUrl("qrc:/resources/red_CON_techo.png"));
    m_arranqueCon->setClickeable(false);

    m_conmutadorPuestaServicioStatus = false;
    m_subte->setConmutadorPuestaServicio(m_conmutadorPuestaServicioStatus);

    connect(m_conmutador,SIGNAL(buttonPressed()),this,SLOT(conmutadorPuestaServicioPressed()));
    connect(m_arranqueCon,SIGNAL(buttonPressed()),this,SLOT(conmutadorPuestaServicioAutomaticaConPressed()));
    connect(m_arranqueDes,SIGNAL(buttonPressed()),this,SLOT(conmutadorPuestaServicioAutomaticaDesPressed()));
}

void TopBoardConnectors_Controller::setPantograph(SingleButton *pantographCon, SingleButton *pantographDes)
{
    m_pantographCon = pantographCon;
    m_pantographDes = pantographDes;

    m_pantographCon->setButtonImage(QUrl("qrc:/resources/redON_CON_techo.png"),QUrl("qrc:/resources/red_CON_techo.png"));
    m_pantographDes->setButtonImage(QUrl("qrc:/resources/greenON_DES_techo.png"),QUrl("qrc:/resources/green_DES_techo.png"));

    m_subte->setPantographConnector(false);

    connect(m_pantographCon,SIGNAL(buttonPressed()),this,SLOT(pantographConPressed()));
    connect(m_pantographDes,SIGNAL(buttonPressed()),this,SLOT(pantographDesPressed()));
}

void TopBoardConnectors_Controller::setCompressorAux(SingleButton *compressorAuxCon,SingleButton *compressorAuxDes)
{
    m_compressorAuxCon = compressorAuxCon;
    m_compressorAuxDes = compressorAuxDes;

    m_compressorAuxCon->setButtonImage(QUrl("qrc:/resources/redON_CON_techo.png"),QUrl("qrc:/resources/red_CON_techo.png"));
    m_compressorAuxDes->setButtonImage(QUrl("qrc:/resources/greenON_DES_techo.png"),QUrl("qrc:/resources/green_DES_techo.png"));

    m_subte->setCompressorAuxConnector(false);

    connect(m_compressorAuxCon,SIGNAL(buttonPressed()),this,SLOT(compressorAuxConPressed()));
    connect(m_compressorAuxDes,SIGNAL(buttonPressed()),this,SLOT(compressorAuxDesPressed()));
}

void TopBoardConnectors_Controller::setConverter(SingleButton *converterCon,SingleButton *converterDes)
{
    m_converterCon = converterCon;
    m_converterDes = converterDes;

    m_converterCon->setButtonImage(QUrl("qrc:/resources/redON_CON_techo.png"),QUrl("qrc:/resources/red_CON_techo.png"));
    m_converterDes->setButtonImage(QUrl("qrc:/resources/greenON_DES_techo.png"),QUrl("qrc:/resources/green_DES_techo.png"));

    m_subte->setConverterConnector(false);

    connect(m_converterCon,SIGNAL(buttonPressed()),this,SLOT(converterConPressed()));
    connect(m_converterDes,SIGNAL(buttonPressed()),this,SLOT(converterDesPressed()));
}

void TopBoardConnectors_Controller::setMainCompressor(SingleButton *mainCompressorCon,SingleButton *mainCompressorDes)
{
    m_mainCompressorCon = mainCompressorCon;
    m_mainCompressorDes = mainCompressorDes;

    m_mainCompressorCon->setButtonImage(QUrl("qrc:/resources/redON_CON_techo.png"),QUrl("qrc:/resources/red_CON_techo.png"));
    m_mainCompressorDes->setButtonImage(QUrl("qrc:/resources/greenON_DES_techo.png"),QUrl("qrc:/resources/green_DES_techo.png"));

    m_subte->setMainCompressorConnector(false);

    connect(m_mainCompressorCon,SIGNAL(buttonPressed()),this,SLOT(mainCompressorConPressed()));
    connect(m_mainCompressorDes,SIGNAL(buttonPressed()),this,SLOT(mainCompressorDesPressed()));
}

void TopBoardConnectors_Controller::setLighting(SingleButton *lightingCon,SingleButton *lightingDes)
{
    m_lightingCon = lightingCon;
    m_lightingDes = lightingDes;

    m_lightingCon->setButtonImage(QUrl("qrc:/resources/redON_CON_techo.png"),QUrl("qrc:/resources/red_CON_techo.png"));
    m_lightingDes->setButtonImage(QUrl("qrc:/resources/greenON_DES_techo.png"),QUrl("qrc:/resources/green_DES_techo.png"));

    m_subte->setLightingConnector(false);

    connect(m_lightingCon,SIGNAL(buttonPressed()),this,SLOT(lightingConPressed()));
    connect(m_lightingDes,SIGNAL(buttonPressed()),this,SLOT(lightingDesPressed()));
}

void TopBoardConnectors_Controller::setAir(SingleButton *airCon,SingleButton *airDes)
{
    m_airCon = airCon;
    m_airDes = airDes;

    m_airCon->setButtonImage(QUrl("qrc:/resources/redON_CON_techo.png"),QUrl("qrc:/resources/red_CON_techo.png"));
    m_airDes->setButtonImage(QUrl("qrc:/resources/greenON_DES_techo.png"),QUrl("qrc:/resources/green_DES_techo.png"));

    m_subte->setAirConnector(false);

    connect(m_airCon,SIGNAL(buttonPressed()),this,SLOT(airConPressed()));
    connect(m_airDes,SIGNAL(buttonPressed()),this,SLOT(airDesPressed()));
}

void TopBoardConnectors_Controller::setMegaphone(SingleButton *megaphoneCon,SingleButton *megaphoneDes)
{
    m_megaphoneCon = megaphoneCon;
    m_megaphoneDes = megaphoneDes;

    m_megaphoneCon->setButtonImage(QUrl("qrc:/resources/redON_CON_techo.png"),QUrl("qrc:/resources/red_CON_techo.png"));
    m_megaphoneDes->setButtonImage(QUrl("qrc:/resources/greenON_DES_techo.png"),QUrl("qrc:/resources/green_DES_techo.png"));

    m_subte->setMegaphoneConnector(false);

    connect(m_megaphoneCon,SIGNAL(buttonPressed()),this,SLOT(megaphoneConPressed()));
    connect(m_megaphoneDes,SIGNAL(buttonPressed()),this,SLOT(megaphoneDesPressed()));
}

void TopBoardConnectors_Controller::setParkingBrake(SingleButton *parkingBrakeCon,SingleButton *parkingBrakeDes)
{
    m_parkingBrakeCon = parkingBrakeCon;
    m_parkingBrakeDes = parkingBrakeDes;

    m_parkingBrakeCon->setButtonImage(QUrl("qrc:/resources/redON_CON_techo.png"),QUrl("qrc:/resources/red_CON_techo.png"));
    m_parkingBrakeDes->setButtonImage(QUrl("qrc:/resources/greenON_DES_techo.png"),QUrl("qrc:/resources/green_DES_techo.png"));

    m_subte->setParkingBrakeConnector(true);
    connect(m_parkingBrakeCon,SIGNAL(buttonPressed()),this,SLOT(parkingBrakeConPressed()));
    connect(m_parkingBrakeDes,SIGNAL(buttonPressed()),this,SLOT(parkingBrakeDesPressed()));
}

void TopBoardConnectors_Controller::batteryConPressed(){
    m_batteryCon->setClickeable(false);
    m_batteryDes->setClickeable(true);
    m_batteryDes->turnOff();
    m_batteryCon->turnOn();
    m_subte->setBatteryConnector(true);
}

void TopBoardConnectors_Controller::batteryDesPressed(){
    m_batteryCon->setClickeable(true);
    m_batteryDes->setClickeable(false);
    m_batteryDes->turnOn();
    m_batteryCon->turnOff();
    m_subte->setBatteryConnector(false);
}

void TopBoardConnectors_Controller::conmutadorPuestaServicioPressed(){
    m_conmutadorPuestaServicioStatus = !m_conmutadorPuestaServicioStatus;

    if(m_conmutadorPuestaServicioStatus){
        m_subte->setConmutadorPuestaServicio(true);
        m_luzLlaveDes->turnOn();
        m_luzLlaveCon->turnOff();
        if(!m_enMarcha){
            m_arranqueCon->setClickeable(true);
            m_arranqueDes->setClickeable(false);
            m_arranqueDes->turnOn();
            m_arranqueCon->turnOff();
        }else{
            m_arranqueCon->setClickeable(false);
            m_arranqueDes->setClickeable(true);
            m_arranqueDes->turnOff();
            m_arranqueCon->turnOn();
        }
    }else{
        m_subte->setConmutadorPuestaServicio(false);
        m_luzLlaveDes->turnOff();
        m_luzLlaveCon->turnOn();
        m_subte->setConmutadorPuestaServicioAutomatica(false);
        m_arranqueCon->setClickeable(false);
        m_arranqueDes->setClickeable(false);
        m_arranqueCon->turnOff();
        m_arranqueDes->turnOff();
    }
}

void TopBoardConnectors_Controller::conmutadorPuestaServicioAutomaticaConPressed(){
    m_enMarcha = true;
    m_arranqueCon->setClickeable(false);
    m_arranqueDes->setClickeable(true);
    m_arranqueDes->turnOff();
    m_arranqueCon->turnOn();
    m_subte->setConmutadorPuestaServicioAutomatica(true);

    this->pantographConPressed();
    this->compressorAuxConPressed();
    this->converterConPressed();
    this->mainCompressorConPressed();
    this->lightingConPressed();
    this->airConPressed();
    this->megaphoneConPressed();
}

void TopBoardConnectors_Controller::conmutadorPuestaServicioAutomaticaDesPressed(){
    m_enMarcha = false;
    m_arranqueCon->setClickeable(true);
    m_arranqueDes->setClickeable(false);
    m_arranqueCon->turnOff();
    m_arranqueDes->turnOn();
    m_subte->setConmutadorPuestaServicioAutomatica(false);

    this->pantographDesPressed();
    this->compressorAuxDesPressed();
    this->converterDesPressed();
    this->mainCompressorDesPressed();
    this->lightingDesPressed();
    this->airDesPressed();
    this->megaphoneDesPressed();
}

void TopBoardConnectors_Controller::pantographConPressed(){
    m_pantographCon->setClickeable(false);
    m_pantographDes->setClickeable(true);
    m_pantographDes->turnOff();
    m_pantographCon->turnOn();
    m_subte->setPantographConnector(true);
}

void TopBoardConnectors_Controller::pantographDesPressed(){
    m_pantographCon->setClickeable(true);
    m_pantographDes->setClickeable(false);
    m_pantographDes->turnOn();
    m_pantographCon->turnOff();
    m_subte->setPantographConnector(false);
}

void TopBoardConnectors_Controller::compressorAuxConPressed(){
    m_compressorAuxCon->setClickeable(false);
    m_compressorAuxDes->setClickeable(true);
    m_compressorAuxDes->turnOff();
    m_compressorAuxCon->turnOn();
    m_subte->setCompressorAuxConnector(true);
}

void TopBoardConnectors_Controller::compressorAuxDesPressed(){
    m_compressorAuxCon->setClickeable(true);
    m_compressorAuxDes->setClickeable(false);
    m_compressorAuxDes->turnOn();
    m_compressorAuxCon->turnOff();
    m_subte->setCompressorAuxConnector(false);
}

void TopBoardConnectors_Controller::converterConPressed(){
    m_converterCon->setClickeable(false);
    m_converterDes->setClickeable(true);
    m_converterDes->turnOff();
    m_converterCon->turnOn();
    m_subte->setConverterConnector(true);
}

void TopBoardConnectors_Controller::converterDesPressed(){
    m_converterCon->setClickeable(true);
    m_converterDes->setClickeable(false);
    m_converterDes->turnOn();
    m_converterCon->turnOff();
    m_subte->setConverterConnector(false);
}

void TopBoardConnectors_Controller::mainCompressorConPressed(){
    m_mainCompressorCon->setClickeable(false);
    m_mainCompressorDes->setClickeable(true);
    m_mainCompressorDes->turnOff();
    m_mainCompressorCon->turnOn();
    m_subte->setConverterConnector(true);
}

void TopBoardConnectors_Controller::mainCompressorDesPressed(){
    m_mainCompressorCon->setClickeable(true);
    m_mainCompressorDes->setClickeable(false);
    m_mainCompressorDes->turnOn();
    m_mainCompressorCon->turnOff();
    m_subte->setConverterConnector(false);
}

void TopBoardConnectors_Controller::lightingConPressed(){
    m_lightingCon->setClickeable(false);
    m_lightingDes->setClickeable(true);
    m_lightingDes->turnOff();
    m_lightingCon->turnOn();
    m_subte->setConverterConnector(true);
}

void TopBoardConnectors_Controller::lightingDesPressed(){
    m_lightingCon->setClickeable(true);
    m_lightingDes->setClickeable(false);
    m_lightingDes->turnOn();
    m_lightingCon->turnOff();
    m_subte->setConverterConnector(false);
}

void TopBoardConnectors_Controller::airConPressed(){
    m_airCon->setClickeable(false);
    m_airDes->setClickeable(true);
    m_airDes->turnOff();
    m_airCon->turnOn();
    m_subte->setConverterConnector(true);
}

void TopBoardConnectors_Controller::airDesPressed(){
    m_airCon->setClickeable(true);
    m_airDes->setClickeable(false);
    m_airDes->turnOn();
    m_airCon->turnOff();
    m_subte->setConverterConnector(false);
}

void TopBoardConnectors_Controller::megaphoneConPressed(){
    m_megaphoneCon->setClickeable(false);
    m_megaphoneDes->setClickeable(true);
    m_megaphoneDes->turnOff();
    m_megaphoneCon->turnOn();
    m_subte->setMegaphoneConnector(true);
}

void TopBoardConnectors_Controller::megaphoneDesPressed(){
    m_megaphoneCon->setClickeable(true);
    m_megaphoneDes->setClickeable(false);
    m_megaphoneDes->turnOn();
    m_megaphoneCon->turnOff();
    m_subte->setMegaphoneConnector(false);
}

void TopBoardConnectors_Controller::parkingBrakeConPressed(){
    m_parkingBrakeCon->setClickeable(false);
    m_parkingBrakeDes->setClickeable(true);
    m_parkingBrakeDes->turnOff();
    m_parkingBrakeCon->turnOn();
    m_subte->setParkingBrakeConnector(true);
}

void TopBoardConnectors_Controller::parkingBrakeDesPressed(){
    m_parkingBrakeCon->setClickeable(true);
    m_parkingBrakeDes->setClickeable(false);
    m_parkingBrakeDes->turnOn();
    m_parkingBrakeCon->turnOff();
    m_subte->setParkingBrakeConnector(false);
}

void TopBoardConnectors_Controller::setEstado(int state)
{
    m_lastState = state;
}

void TopBoardConnectors_Controller::reset(){
    if(m_lastState == APAGADO){
        resetToApagado();
    }else{
        resetToMarcha();
    }
}

void TopBoardConnectors_Controller::resetToApagado(){
    batteryDesPressed();
    m_conmutadorPuestaServicioStatus = true;
    m_enMarcha = false;
    m_conmutador->turnOff();
    conmutadorPuestaServicioPressed();
    pantographDesPressed();
    compressorAuxDesPressed();
    converterDesPressed();
    mainCompressorDesPressed();
    lightingDesPressed();
    airDesPressed();
    megaphoneDesPressed();
    parkingBrakeConPressed();
    m_lastState = APAGADO;
}

void TopBoardConnectors_Controller::resetToMarcha(){
    batteryConPressed();
    m_conmutadorPuestaServicioStatus = false;
    m_enMarcha = true;
    m_conmutador->turnOn();
    conmutadorPuestaServicioPressed();
    pantographConPressed();
    compressorAuxConPressed();
    converterConPressed();
    mainCompressorConPressed();
    lightingConPressed();
    airConPressed();
    megaphoneConPressed();
    parkingBrakeDesPressed();
    m_lastState = EN_MARCHA;
}
