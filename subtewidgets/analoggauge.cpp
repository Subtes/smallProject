#include "analoggauge.h"
#include "ui_analoggauge.h"

AnalogGauge::AnalogGauge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalogGauge)
{
    ui->setupUi(this);
    ui->quickWidget->setClearColor(Qt::transparent);
    ui->quickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
    m_qmlView = ui->quickWidget->rootObject();
}

AnalogGauge::~AnalogGauge()
{
    delete ui;
}

void AnalogGauge::setBackgroudImage(QUrl bg)
{
    QObject * hook = m_qmlView->findChild<QObject*>("background");
    hook->setProperty("source", bg);
}

void AnalogGauge::setNeedleImage(QUrl n)
{
    QObject * hook = m_qmlView->findChild<QObject*>("needle");
    hook->setProperty("source", n);
}

void AnalogGauge::setNeedleImage(QUrl n, int anchorX, int anchorY)
{
    setNeedleImage(n);
    m_qmlView->setProperty("originX",anchorX);
    m_qmlView->setProperty("originY",anchorY);
}

void AnalogGauge::setMaxAngle(int angle)
{
    m_qmlView->setProperty("maxAngle",angle);
}

void AnalogGauge::setOffsetAngle(int angle)
{
    m_qmlView->setProperty("offsetAngle",angle);
}

void AnalogGauge::setMinMaxValue(int minV,int maxV)
{
    m_qmlView->setProperty("maxValue",maxV);
    m_qmlView->setProperty("minValue",minV);

}

void AnalogGauge::updateNeedle(double speed){
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "updateNeedle",
            Q_RETURN_ARG(QVariant, returnedValue),
            Q_ARG(QVariant, speed));
}
