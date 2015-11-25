#include "llavemodoconduccion_controller.h"

LlaveModoConduccion_Controller::LlaveModoConduccion_Controller(SubteStatus *subte, LlaveModoConduccion *llave)
    : Base_Controller(subte)
{
    m_subte = subte;
    m_llave = llave;

    connect(m_llave,SIGNAL(acopleMode()),this,SLOT(setAcopleMode()));
    connect(m_llave,SIGNAL(atpMode()),this,SLOT(setAtpMode()));
    connect(m_llave,SIGNAL(maniobraMode()),this,SLOT(setManiobraMode()));
    connect(m_llave,SIGNAL(acopleMode()),this,SIGNAL(menssajeModeAcople()));
    connect(m_llave,SIGNAL(maniobraMode()),this,SIGNAL(mensajeModeManiobra()));
    connect(m_llave,SIGNAL(atpMode()),this,SIGNAL(mensajeModeNormal()));


}

LlaveModoConduccion_Controller::~LlaveModoConduccion_Controller()
{

}

void LlaveModoConduccion_Controller::setManiobraMode(){
    m_llave->setManiobraMode();
    m_subte->setManiobraMode();
}

void LlaveModoConduccion_Controller::setAtpMode(){
    m_llave->setAtpMode();
    m_subte->setAtpMode();
}

void LlaveModoConduccion_Controller::setAcopleMode(){
    m_llave->setAcopleMode();
    m_subte->setAcopleMode();
}
