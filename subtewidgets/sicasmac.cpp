#include "sicasmac.h"
#include "ui_sicasmac.h"

SicasMac::SicasMac(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SicasMac)
{
    ui->setupUi(this);
    ui->quickWidget->setClearColor(Qt::transparent);
    ui->quickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
    m_qmlView = ui->quickWidget->rootObject();
    connect(m_qmlView,SIGNAL(onPressSig()),this,SIGNAL(onPressSigRow()));
    connect(m_qmlView,SIGNAL(onPressAnt()),this,SIGNAL(onPressAntRow()));
    connect(m_qmlView,SIGNAL(sicasOk()),this,SIGNAL(sicasOk()));
}

SicasMac::~SicasMac()
{
    delete ui;
}

void SicasMac::setBackgroudImage(QUrl bg)
{
    QObject * hook = m_qmlView->findChild<QObject*>("background");
    hook->setProperty("source", bg);
}


void SicasMac::setGlassImage(QUrl gl)
{
    QObject * hook = m_qmlView->findChild<QObject*>("glassmac");
    hook->setProperty("source", gl);
}

void SicasMac::setFailure1(QUrl fl)
{
    QObject * hook = m_qmlView->findChild<QObject*>("failure1");
    hook->setProperty("source", fl);
}

void SicasMac::setFailure2(QUrl f2)
{
    QObject * hook = m_qmlView->findChild<QObject*>("failure2");
    hook->setProperty("source", f2);
}

void SicasMac::setFailure3(QUrl f3)
{
    QObject * hook = m_qmlView->findChild<QObject*>("failure3");
    hook->setProperty("source", f3);
}

void SicasMac::setFailure4(QUrl f4)
{
    QObject * hook = m_qmlView->findChild<QObject*>("failure4");
    hook->setProperty("source", f4);
}

void SicasMac::setFailure5(QUrl f5)
{
    QObject * hook = m_qmlView->findChild<QObject*>("failure5");
    hook->setProperty("source", f5);
}

void SicasMac::setFailure6(QUrl f6)
{
    QObject * hook = m_qmlView->findChild<QObject*>("failure6");
    hook->setProperty("source", f6);
}

void SicasMac::setStartTrain(QUrl at1)
{
    QObject * hook = m_qmlView->findChild<QObject*>("actualtrainstart");
    hook->setProperty("source", at1);
}

void SicasMac::setEndTrain(QUrl at6)
{
    QObject * hook = m_qmlView->findChild<QObject*>("actualtrainend");
    hook->setProperty("source", at6);
}



void SicasMac::startBlinkFailure(int failure)
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "startBlinkFailure",
                              Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, failure));
}

void SicasMac::stopBlink(int failure)
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "stopBlinkFailure",
                              Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, failure));
}

void SicasMac::textEditSicas(QString error,QString trenes,QString letra, int index)
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "changeText",
                              Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, error),
                                    Q_ARG(QVariant, trenes),Q_ARG(QVariant, letra),Q_ARG(QVariant, index));
}
void SicasMac::borrarArregloBlinkSicas(QString trenes, int index)
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "borrarTrenesBlink",
                              Q_RETURN_ARG(QVariant, returnedValue),Q_ARG(QVariant, trenes)
                              ,Q_ARG(QVariant, index));
}
void SicasMac::generarTrenesBlink(QString trenes, int index,bool parpadeo)
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "blinkRenglonTrenes",
                              Q_RETURN_ARG(QVariant, returnedValue),Q_ARG(QVariant, trenes),
                              Q_ARG(QVariant, index),Q_ARG(QVariant, parpadeo));
}


void SicasMac::insertTrainSicas(QString coche, QString estFreno)
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "changeStateTrain",
                              Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, coche),
                                    Q_ARG(QVariant, estFreno));
}

void SicasMac::turnOffFailure(int coche)
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "turnOffFailure",
            Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, coche));
}

void SicasMac::turnOnFailure(int coche)
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "turnOnFailure",
            Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, coche));
}

void SicasMac::turnBlinkFailure(int coche)
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "turnBlinkFailure",
            Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, coche));
}
void SicasMac::turnInhabFailure(int coche)
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "turnInhabFailure",
            Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, coche));
}
void SicasMac::turnOffDoors(int coche)
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "turnOffDoors",
            Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, coche));
}

void SicasMac::turnOnDoors(int coche)
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "turnOnDoors",
            Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, coche));
}

void SicasMac::actualizarTamArreRenglon(int finRenglon)
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "actualizarTamArreRenglon",
            Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, finRenglon));
}


//NUEVO SICAS
void SicasMac::sigPosicionSicas()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "nextPositionSicas",
            Q_RETURN_ARG(QVariant, returnedValue));
}

void SicasMac::endRenglonSicas()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "endRenglonSicas",
            Q_RETURN_ARG(QVariant, returnedValue));
}

void SicasMac::initRenglonSicas()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "initRenglonSicas",
            Q_RETURN_ARG(QVariant, returnedValue));
}


void SicasMac::turnOnSiguiente()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "turnOnSiguiente",
            Q_RETURN_ARG(QVariant, returnedValue));
}

void SicasMac::turnOffSiguiente()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "turnOffSiguiente",
            Q_RETURN_ARG(QVariant, returnedValue));
}

void SicasMac::turnOnAnterior()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "turnOnAnterior",
            Q_RETURN_ARG(QVariant, returnedValue));
}

void SicasMac::turnOffAnterior()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "turnOffAnterior",
            Q_RETURN_ARG(QVariant, returnedValue));
}

void SicasMac::antPositionSicas()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "backPositionSicas",
            Q_RETURN_ARG(QVariant, returnedValue));
}
int SicasMac::getPosActualRenglon()
{
    return m_qmlView->property("valorRenglonActual").toInt();
}

void SicasMac::turnOnSicas()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "turnOnSicas",
            Q_RETURN_ARG(QVariant, returnedValue));
}
void SicasMac::turnOffSicas()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "turnOffSicas",
            Q_RETURN_ARG(QVariant, returnedValue));
}
void SicasMac::cargoDestinoSicas(QString destino)
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "cargoDestinoSicas",
            Q_RETURN_ARG(QVariant, returnedValue),Q_ARG(QVariant, destino));
}
void SicasMac::ponerOnSicasSinIncidencia()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "ponerOnSicasSinIncidencia",
            Q_RETURN_ARG(QVariant, returnedValue));
}
void SicasMac::ponerValoresInicio(int cantPantallas)
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "ponerValoresInicio",
            Q_RETURN_ARG(QVariant, returnedValue),Q_ARG(QVariant, cantPantallas));
}
