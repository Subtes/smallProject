#include "circuitbreakerdes_controller.h"

CircuitBreakerDES_Controller::CircuitBreakerDES_Controller(SubteStatus *subte, SingleButton *button)
{
    m_model = subte;
    m_view = button;

    m_view->setNestled(false);
    m_view->setLighted(true);
    m_view->setOnPressAsDriver();

    m_view->setButtonImage(QUrl("qrc:/resources/greenON.png"),QUrl("qrc:/resources/green.png"));

}

void CircuitBreakerDES_Controller::pressCircuitBreakerDES(){
    m_model->disyuntoresDes();
}

CircuitBreakerDES_Controller::~CircuitBreakerDES_Controller(){
    delete m_model;
    delete m_view;
}

