#include "manometer.h"
#include "ui_manometer.h"

Manometer::Manometer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Manometer)
{
    ui->setupUi(this);
    ui->quickWidget->setClearColor(Qt::transparent);
    ui->quickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
    m_qmlView = ui->quickWidget->rootObject();
}

Manometer::~Manometer()
{
    delete ui;
}

void Manometer::setBackgroudImage(QUrl bg)
{
    QObject * hook = m_qmlView->findChild<QObject*>("background");
    hook->setProperty("source", bg);
}

void Manometer::setGlassImage(QUrl gl)
{
    QObject * hook = m_qmlView->findChild<QObject*>("glass");
    hook->setProperty("source", gl);
}

void Manometer::setNeedleWhiteImage(QUrl nw)
{
    QObject * hook = m_qmlView->findChild<QObject*>("needleWhite");
    hook->setProperty("source", nw);
}
void Manometer::setNeedleRedImage(QUrl nr)
{
    QObject * hook = m_qmlView->findChild<QObject*>("needleRed");
    hook->setProperty("source", nr);
}

void Manometer::setNeedleWhiteImage(QUrl nw, int anchorX, int anchorY)
{
    setNeedleWhiteImage(nw);
    m_qmlView->setProperty("originX",anchorX);
    m_qmlView->setProperty("originY",anchorY);
}

void Manometer::setNeedleRedImage(QUrl nr, int anchorX, int anchorY)
{
    setNeedleRedImage(nr);
    m_qmlView->setProperty("originX",anchorX);
    m_qmlView->setProperty("originY",anchorY);
}

void Manometer::setMaxAngle(int angle)
{
    m_qmlView->setProperty("maxAngle",angle);
}

void Manometer::setOffsetAngle(int angle)
{
    m_qmlView->setProperty("offsetAngle",angle);
}

void Manometer::setMinMaxValue(int minV,int maxV)
{
    m_qmlView->setProperty("maxValue",maxV);
    m_qmlView->setProperty("minValue",minV);

}


void Manometer::updateNeedleRed(double speed){
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "updateNeedleRed",
            Q_RETURN_ARG(QVariant, returnedValue),
            Q_ARG(QVariant, speed));
}

void Manometer::updateNeedleWhite(double speed){
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "updateNeedleWhite",
            Q_RETURN_ARG(QVariant, returnedValue),
            Q_ARG(QVariant, speed));
}
