#include <tractionhardware.h>

#include "boardright.h"
#include "ui_boardright.h"

BoardRight::BoardRight(QWidget *parent, SubteStatus * subte, EventHandler *eventHandler) :
    BaseBoard(parent,subte,eventHandler),
    ui(new Ui::BoardRight)
{
    ui->setupUi(this);

    connect(m_eventHandler,SIGNAL(controlReady()),this,SLOT(startBoard()));
    connect(m_eventHandler,SIGNAL(controlDisable()),this,SLOT(disableScreen()));
    connect(m_eventHandler,SIGNAL(controlEnable()),this,SLOT(enableScreen()));
    connect(m_eventHandler,SIGNAL(controlReset()),this,SLOT(resetControls()));
    connect(m_eventHandler,SIGNAL(cargarEstado(int)),this,SLOT(loadState(int)));

    m_manometer = NULL;
    m_CON_Disyuntor = NULL;
    m_DES_Disyuntor = NULL;
    m_sicasmac = NULL;
    m_modoConduccion = NULL;
    m_frenoRetencion = NULL;
}

BoardRight::~BoardRight()
{
    delete ui;
}

void BoardRight::startBoard()
{
    qDebug() << "board right startBoard";

    ui->calientapies->setButtonImage(QUrl("qrc:/resources/blueON.png"),QUrl("qrc:/resources/blue.png"));
    ui->desacople->setButtonImage(QUrl("qrc:/resources/greenON.png"),QUrl("qrc:/resources/green.png"));

    m_CON_Disyuntor = new CircuitBreakerCON_Controller(m_subte,ui->CONDisy_widget );
    m_DES_Disyuntor = new CircuitBreakerDES_Controller(m_subte,ui->DESDisy_widget );
    m_manometer = new Manometer_Controller(m_subte,ui->manometer);
    m_sicasmac = new SicasMac_Controller(m_subte,ui->sicasmac, m_hardwareSupport);
    m_modoConduccion = new LlaveModoConduccion_Controller(m_subte,ui->modoConduccion);

    //CARGA SICAS CUANDO CAMBIA DE MODO ACOPLE O MANIOBRA A MODO NORMAL
    connect(m_modoConduccion,SIGNAL(menssajeModeAcople()),m_sicasmac,SLOT(cargarMensajeAcople()));
    connect(m_modoConduccion,SIGNAL(mensajeModeManiobra()),m_sicasmac,SLOT(cargarMensajeAcople()));
    connect(m_modoConduccion,SIGNAL(mensajeModeNormal()),m_sicasmac,SLOT(sacoMensajeAcople()));

    m_frenoRetencion = new FrenoRetencion_Controller(m_subte,ui->frenoRetencion);

    //CARGA DE SICAS ENVIADA POR INSTRUCCIONES
    connect(m_eventHandler,SIGNAL(cargarDestinoSicas(QString)),m_sicasmac,SLOT(cargarDestinoSicas(QString)));
    connect(m_eventHandler,SIGNAL(cargarMensaje(QString)),m_sicasmac,SLOT(separoMensajes(QString)));
    connect(m_eventHandler,SIGNAL(cargarMensajeCocheSicas(QString)),m_sicasmac,SLOT(cargoCoches(QString)));
    this->setEnabled(false);

    // SONIDO SICAS
    connect(m_sicasmac,SIGNAL(playSound(int)),m_hardwareSupport,SLOT(onSound(int)));

}

void BoardRight::enableScreen()
{
    this->setEnabled(true);
}

void BoardRight::disableScreen()
{
    this->setEnabled(false);
}

void BoardRight::resetControls(){
    loadState(lastState);
    m_sicasmac->resetSicas();
}

void BoardRight::loadState(int state){
    ui->calientapies->turnOff();
    ui->desacople->turnOff();
    ui->DESDisy_widget->turnOff();
    ui->CONDisy_widget->turnOff();
    m_frenoRetencion->turnOff();

    if(state == APAGADO){
        m_manometer->updatePressureRed(0);
        m_manometer->updatePressureWhite(0);
        m_modoConduccion->setManiobraMode();
        ui->sicasmac->turnOffSicas();
    }
    else if(state == EN_MARCHA){
        m_manometer->updatePressureRed(m_subte->getPressureRed());
        m_manometer->updatePressureWhite(m_subte->getPressureWhite());
        ui->sicasmac->turnOnSicas();
    }

    m_eventHandler->enableDiffusion();
}

void BoardRight::setHardware(TractionHardware *th){
    m_hardwareSupport = th;
}
