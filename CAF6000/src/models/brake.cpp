#include "brake.h"
#include <QDebug>

Brake::Brake()
{
    m_emergencyBrake_atp = false;
    m_emergencyBrake_setas = false;
    m_emergencyBrake_tractionLever = false;
    m_emergencyBrake_HM = false;
    m_brake = 0;
    m_lastBrake = 0;
    m_bypass = false;
    m_retentioBrake = false;
    m_anulacionFrenoRetencion = false;
    m_averia = false;
}

Brake::~Brake()
{
}

void Brake::linkTraction(Traction *traction)
{
    m_traction = traction;
}

void Brake::setHandler(EventHandler * eventHandler)
{
    m_eventHandler = eventHandler;
}

bool Brake::braking()
{
    if (m_bypass){
        return false;
    }

    if(m_averia){
        return true;
    }

    return m_brake>0 || getEmergencyBrake();
}

void Brake::reset()
{
    m_emergencyBrake_atp = false;
    m_emergencyBrake_setas = false;
    m_emergencyBrake_tractionLever = false;
    m_emergencyBrake_HM = false;
    m_brake = 0;
    m_lastBrake = 0;
    m_bypass = false;
    m_averia = false;
    m_retentioBrake = false;
    m_anulacionFrenoRetencion = false;
}

bool Brake::getHiloLazo(){
    if (m_bypass)
        return true;

    return  m_traction->hombreMuerto() &&
            !m_averia &&
            !m_emergencyBrake_atp &&
            !m_emergencyBrake_setas &&
            !m_emergencyBrake_tractionLever;
}

bool Brake::getEmergencyBrake() const
{
   if (m_bypass)
       return false;

    if (m_averia)
        return true;

    return m_emergencyBrake_atp || m_emergencyBrake_setas || m_emergencyBrake_tractionLever || m_emergencyBrake_HM;
}

void Brake::setEmergencyBrake_atp(bool value)
{
    m_emergencyBrake_atp = value;
    notifyEmergencyBrake();
}

void Brake::setEmergencyBrake_seta(bool value)
{
    m_emergencyBrake_setas = value;
    notifyEmergencyBrake();
}


void Brake::setEmergencyBrake_HM(bool value)
{
    m_emergencyBrake_HM = value;
    notifyEmergencyBrake();
}

double Brake::getBrake() const
{
    return m_brake;
}

void Brake::setBrake(double value)
{
    if (value==100){
        m_brake = value;
        m_lastBrake = value;
        m_emergencyBrake_tractionLever = true;
        notifyEmergencyBrake();
    } else if((value<10) || (abs(value - m_lastBrake) >= 3)){
        if (m_emergencyBrake_tractionLever){
            m_emergencyBrake_tractionLever = false;
            notifyEmergencyBrake();
        }
        m_brake = value;
        notifyBrake();
        m_lastBrake = value;
    }
}

bool Brake::bypass() const
{
    return m_bypass;
}

void Brake::setBypass(bool status)
{
    m_bypass = status;
}

bool Brake::retentioBrake() const
{
    if(m_anulacionFrenoRetencion)
        return false;

    return m_retentioBrake;
}

void Brake::setRetentioBrake(bool retentioBrake)
{
    m_retentioBrake = retentioBrake;
}

bool Brake::averia() const
{
    return m_averia;
}

void Brake::setAveria(bool averia)
{
    m_averia = averia;
}

bool Brake::anulacionFrenoRetencion() const
{
    return m_anulacionFrenoRetencion;
}

void Brake::setAnulacionFrenoRetencion(bool anulacionFrenoRetencion)
{
    m_anulacionFrenoRetencion = anulacionFrenoRetencion;
}

void Brake::notifyEmergencyBrake(){
    if (getEmergencyBrake()){
        m_eventHandler->notifyValueChanged(NOMBRE_FRENO_EMERGENCIA,VALOR_CON_FRENO_EMERGENCIA);
    }else{
        m_eventHandler->notifyValueChanged(NOMBRE_FRENO_EMERGENCIA,VALOR_DES_FRENO_EMERGENCIA);
    }
}

void Brake::notifyBrake(){
    m_eventHandler->notifyValueChanged(NOMBRE_FRENO,std::to_string(getBrake()));
}
