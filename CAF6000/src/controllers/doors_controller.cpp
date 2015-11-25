#include "doors_controller.h"

Doors_Controller::Doors_Controller(SubteStatus *subte, SingleButton *openLeftDoors, SingleButton *closeLeftDoors, SingleButton *selectLeftDoors, SingleButton *openRightDoors, SingleButton *closeRightDoors, SingleButton *selectRightDoors, SingleButton *silbato)
    : Base_Controller(subte)
{   
    m_selectLeftDoors = selectLeftDoors;
    m_openLeftDoors = openLeftDoors;
    m_closeLeftDoors = closeLeftDoors;
    m_selectRightDoors = selectRightDoors;
    m_openRightDoors = openRightDoors;
    m_closeRightDoors = closeRightDoors;
    m_silbato = silbato;

    m_closeRightDoors->setButtonImage(QUrl("qrc:/resources/greenON.png"),QUrl("qrc:/resources/green.png"));
    m_closeLeftDoors->setButtonImage(QUrl("qrc:/resources/greenON.png"),QUrl("qrc:/resources/green.png"));
    m_openRightDoors->setButtonImage(QUrl("qrc:/resources/greenON.png"),QUrl("qrc:/resources/green.png"));
    m_openLeftDoors->setButtonImage(QUrl("qrc:/resources/greenON.png"),QUrl("qrc:/resources/green.png"));
    m_silbato->setButtonImage(QUrl("qrc:/resources/blueON.png"),QUrl("qrc:/resources/blueplane.png"));

    m_closeLeftDoors->setLightManagement(false);
    m_closeRightDoors->setLightManagement(false);
    m_openLeftDoors->setLightManagement(false);
    m_openRightDoors->setLightManagement(false);

    turnOn();

    connect(m_closeLeftDoors,SIGNAL(buttonClicked()),this,SLOT(closeLeft()));
    connect(m_openLeftDoors,SIGNAL(buttonClicked()),this,SLOT(openLeft()));
    connect(m_closeRightDoors,SIGNAL(buttonClicked()),this,SLOT(closeRight()));
    connect(m_openRightDoors,SIGNAL(buttonClicked()),this,SLOT(openRight()));

    connect(m_selectLeftDoors,SIGNAL(buttonClicked()),this,SLOT(enableLeftPanel()));
    connect(m_selectRightDoors,SIGNAL(buttonClicked()),this,SLOT(enableRightPanel()));

    connect(m_subte,SIGNAL(CSCPChanged(bool)),this,SLOT(updatePanel(bool)));
}

Doors_Controller::~Doors_Controller(){}

void Doors_Controller::reset()
{
    m_closeLeftDoors->turnOff();
    m_closeRightDoors->turnOff();
    m_openLeftDoors->turnOff();
    m_openRightDoors->turnOff();
    m_selectLeftDoors->turnOff();
    m_selectRightDoors->turnOff();
    m_silbato->turnOff();
    m_closeLeftDoors->setClickeable(false);
    m_closeRightDoors->setClickeable(false);
    m_openLeftDoors->setClickeable(false);
    m_openRightDoors->setClickeable(false);
}

void Doors_Controller::turnOff()
{
    m_selectLeftDoors->setClickeable(false);
    m_selectRightDoors->setClickeable(false);
    m_silbato->setClickeable(false);

    m_closeLeftDoors->setLighted(false);
    m_closeRightDoors->setLighted(false);
    m_openLeftDoors->setLighted(false);
    m_openRightDoors->setLighted(false);
    m_selectLeftDoors->setLighted(false);
    m_selectRightDoors->setLighted(false);
    m_silbato->setLighted(false);

    reset();
}

void Doors_Controller::turnOn()
{
    m_selectLeftDoors->setClickeable(true);
    m_selectRightDoors->setClickeable(true);
    m_silbato->setClickeable(true);

    m_closeLeftDoors->setLighted(true);
    m_closeRightDoors->setLighted(true);
    m_openLeftDoors->setLighted(true);
    m_openRightDoors->setLighted(true);
    m_selectLeftDoors->setLighted(true);
    m_selectRightDoors->setLighted(true);
    m_silbato->setLighted(true);

    reset();
}

void Doors_Controller::enableLeftPanel(){
    if(!m_selectLeftDoors->buttonState()){
        updateLeft();
    }else{
        m_closeLeftDoors->setClickeable(false);
        m_openLeftDoors->setClickeable(false);
        m_closeLeftDoors->turnOff();
        m_openLeftDoors->turnOff();
    }
}

void Doors_Controller::enableRightPanel(){
    if(!m_selectRightDoors->buttonState()){
        updateRight();
    }else{
        m_closeRightDoors->setClickeable(false);
        m_openRightDoors->setClickeable(false);
        m_closeRightDoors->turnOff();
        m_openRightDoors->turnOff();
    }
}

void Doors_Controller::updateLeft(){
    if(m_subte->leftDoors()){
        m_openLeftDoors->turnOn();
    }else{
        m_openLeftDoors->turnOff();
    }
    m_closeLeftDoors->setClickeable(m_subte->leftDoors());
    m_openLeftDoors->setClickeable(!m_subte->leftDoors());
}

void Doors_Controller::updateRight(){
    if(m_subte->rightDoors()){
        m_openRightDoors->turnOn();
    }else{
        m_openRightDoors->turnOff();
    }
    m_closeRightDoors->setClickeable(m_subte->rightDoors());
    m_openRightDoors->setClickeable(!m_subte->rightDoors());
}

void Doors_Controller::updatePanel(bool b){
    if(m_subte->leftDoors()){
        m_openLeftDoors->turnOn();
    }else{
        m_openLeftDoors->turnOff();
    }
    m_closeLeftDoors->setClickeable(m_subte->leftDoors());
    m_openLeftDoors->setClickeable(!m_subte->leftDoors());

    if(m_subte->rightDoors()){
        m_openRightDoors->turnOn();
    }else{
        m_openRightDoors->turnOff();
    }
    m_closeRightDoors->setClickeable(m_subte->rightDoors());
    m_openRightDoors->setClickeable(!m_subte->rightDoors());
}

void Doors_Controller::closeLeft(){
    m_subte->updateLeftDoorsButtons(SubteStatus::PUERTAS_CERRADAS);
}

void Doors_Controller::closeRight(){
    m_subte->updateRightDoorsButtons(SubteStatus::PUERTAS_CERRADAS);
}

void Doors_Controller::openLeft(){
    m_subte->updateLeftDoorsButtons(SubteStatus::PUERTAS_ABIERTAS);
}

void Doors_Controller::openRight(){
    m_subte->updateRightDoorsButtons(SubteStatus::PUERTAS_ABIERTAS);
}

