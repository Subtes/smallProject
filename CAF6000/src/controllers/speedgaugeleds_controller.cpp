#include "speedgaugeleds_controller.h"

SpeedGaugeLeds_Controller::SpeedGaugeLeds_Controller(SubteStatus *subte, SpeedGaugeLeds * speedGauge)
{
    m_subte = subte;
    m_gauge = speedGauge;

    connect(subte,SIGNAL(speedChanged(double)),this,SLOT(updateSpeed(double)));
    connect(subte,SIGNAL(allowedSpeedChanged(double)),this,SLOT(updateTargetSpeed(double)));
    connect(subte,SIGNAL(modeOperation(int)),this,SLOT(modeOperation(int)));
}

SpeedGaugeLeds_Controller::~SpeedGaugeLeds_Controller()
{

}

void SpeedGaugeLeds_Controller::updateSpeed(double speed){
    m_gauge->updateSpeed(speed);
}

void SpeedGaugeLeds_Controller::updateTargetSpeed(double speed){
    m_gauge->updateTargetSpeed(speed);
}

void SpeedGaugeLeds_Controller::updateAllowedSpeed(double speed){
    m_gauge->updateAllowedSpeed(speed);
}

void SpeedGaugeLeds_Controller::modeOperation(int m){
    m_gauge->setMode(m);
}
