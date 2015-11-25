#include "topgauges_controller.h"

TopGauges_Controller::TopGauges_Controller(SubteStatus * subte, AnalogGauge * voltmeter, AnalogGauge * ammeter, AnalogGauge * effortmeter)
{
    m_subte = subte;

    m_voltmeter = voltmeter;
    m_voltmeter->setBackgroudImage(QUrl("qrc:/resources/Relojtecho01.png"));
    m_voltmeter->setNeedleImage(QUrl("qrc:/resources/RelojtechoAGUJA01.png"),162,158);
    m_voltmeter->setMinMaxValue(0,150);
    m_voltmeter->setMaxAngle(90);
    m_voltmeter->setOffsetAngle(0);

    m_ammeter = ammeter;
    m_ammeter->setBackgroudImage(QUrl("qrc:/resources/Relojtecho02.png"));
    m_ammeter->setNeedleImage(QUrl("qrc:/resources/RelojtechoAGUJA02.png"),104,113);
    m_ammeter->setMinMaxValue(-4000,4000);
    m_ammeter->setMaxAngle(115);
    m_ammeter->setOffsetAngle(115);

    m_effortmeter = effortmeter;
    m_effortmeter->setBackgroudImage(QUrl("qrc:/resources/Relojtecho03.png"));
    m_effortmeter->setNeedleImage(QUrl("qrc:/resources/RelojtechoAGUJA03.png"),104,113);
    m_effortmeter->setMinMaxValue(-100,100);
    m_effortmeter->setMaxAngle(117);
    m_effortmeter->setOffsetAngle(117);

    connect(m_subte,SIGNAL(effortChanged(double)),this,SLOT(updateEffort(double)));
    connect(m_subte,SIGNAL(voltChanged(double)),this,SLOT(updateVolts(double)));
    connect(m_subte,SIGNAL(ampsChanged(double)),this,SLOT(updateAms(double)));

}

TopGauges_Controller::~TopGauges_Controller()
{

}

void TopGauges_Controller::updateEffort(double effort){
    m_effortmeter->updateNeedle(effort);
}

void TopGauges_Controller::updateVolts(double volts){
    m_voltmeter->updateNeedle(volts);
}

void TopGauges_Controller::updateAms(double ams){
    m_ammeter->updateNeedle(ams);
}

void TopGauges_Controller::turnOffGauges()
{
    m_ammeter->updateNeedle(-4000.0);
    m_effortmeter->updateNeedle(-100.0);
    m_voltmeter->updateNeedle(0.0);

    disconnect(m_subte,SIGNAL(effortChanged(double)),this,SLOT(updateEffort(double)));
    disconnect(m_subte,SIGNAL(voltChanged(double)),this,SLOT(updateVolts(double)));
    disconnect(m_subte,SIGNAL(ampsChanged(double)),this,SLOT(updateAms(double)));
}

void TopGauges_Controller::turnOnGauges()
{
    m_ammeter->updateNeedle(0.0);
    m_effortmeter->updateNeedle(0.0);
    //TODO: este valor deberia ser leido desde el blackboard
    m_voltmeter->updateNeedle(117);

    connect(m_subte,SIGNAL(effortChanged(double)),this,SLOT(updateEffort(double)));
    connect(m_subte,SIGNAL(voltChanged(double)),this,SLOT(updateVolts(double)));
    connect(m_subte,SIGNAL(ampsChanged(double)),this,SLOT(updateAms(double)));
}
