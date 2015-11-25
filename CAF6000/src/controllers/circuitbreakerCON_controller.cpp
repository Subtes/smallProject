#include "circuitbreakercon_controller.h"

CircuitBreakerCON_Controller::CircuitBreakerCON_Controller(SubteStatus *subte, SingleButton *button)
{
    m_model = subte;
    m_view = button;

    m_view->setNestled(false);
    m_view->setLighted(true);
    m_view->setOnPressAsDriver();

    m_view->setButtonImage(QUrl("qrc:/resources/redON.png"),QUrl("qrc:/resources/red.png"));

    connect(m_view,SIGNAL(buttonPressed()),this,SLOT(pressCircuitBreakerCON()));

}

void CircuitBreakerCON_Controller::pressCircuitBreakerCON(){
    m_model->disyuntoresCon();
}

CircuitBreakerCON_Controller::~CircuitBreakerCON_Controller(){
    delete m_model;
    delete m_view;
}
