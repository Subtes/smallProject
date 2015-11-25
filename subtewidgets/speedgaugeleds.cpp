#include "speedgaugeleds.h"
#include "ui_speedgaugeleds.h"

SpeedGaugeLeds::SpeedGaugeLeds(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpeedGaugeLeds)
{
    ui->setupUi(this);

    ui->quickWidget->setClearColor(Qt::transparent);
    ui->quickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);

    m_qmlView = ui->quickWidget->rootObject();
}

SpeedGaugeLeds::~SpeedGaugeLeds()
{
    delete ui;
}

void SpeedGaugeLeds::updateSpeed(double speed){

    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "updateSpeed",
            Q_RETURN_ARG(QVariant, returnedValue),
                              Q_ARG(QVariant, speed));
}

void SpeedGaugeLeds::turnOff()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "turnOff",
            Q_RETURN_ARG(QVariant, returnedValue));
}

void SpeedGaugeLeds::turnOn()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "turnOn",
            Q_RETURN_ARG(QVariant, returnedValue));
}

void SpeedGaugeLeds::updateTargetSpeed(double speed){
    //qDebug() << "updateTargetSpeed con " << speed;
    QVariant returnedValue;

    QMetaObject::invokeMethod(m_qmlView, "updateMaxSpeed",
            Q_RETURN_ARG(QVariant, returnedValue),
            Q_ARG(QVariant, speed));
}

void SpeedGaugeLeds::updateAllowedSpeed(double speed){
    //qDebug() << "updateAllowedSpeed con " << speed;
    QVariant returnedValue;

    QMetaObject::invokeMethod(m_qmlView, "updateMaxSpeed",
            Q_RETURN_ARG(QVariant, returnedValue),
            Q_ARG(QVariant, speed));
}

void SpeedGaugeLeds::setMode(int m){

    qDebug() << "SpeedGaugeLeds::setMode.........." << m;

    QVariant returnedValue;

    QMetaObject::invokeMethod(m_qmlView, "setOperationMode",
            Q_RETURN_ARG(QVariant, returnedValue),
            Q_ARG(QVariant, m));
}
