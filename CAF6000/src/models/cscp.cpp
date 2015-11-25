#include "cscp.h"

CSCP::CSCP()
{
    m_leftDoors = CLOSE;
    m_rightDoors = CLOSE;
    m_bypass = false;
    m_averia = false;
}

CSCP::~CSCP()
{

}

void CSCP::setHandler(EventHandler * eventHandler)
{
    m_eventHandler = eventHandler;
}

void CSCP::reset()
{
    m_leftDoors = CLOSE;
    m_rightDoors = CLOSE;
    m_bypass = false;
    m_averia = false;
    m_parkingBrake = false;
}

bool CSCP::evalCircuit()
{
    if (m_bypass) return true;
    if(m_averia) return false;
    if(m_parkingBrake) return false;
    return !m_leftDoors && !m_rightDoors;
}

bool CSCP::getBypass() const
{
    return m_bypass;
}

void CSCP::setBypass(bool value)
{
    m_bypass = value;
}

bool CSCP::averia() const
{
    return m_averia;
}

void CSCP::setAveria(bool averia)
{
    m_averia = averia;
}

bool CSCP::leftDoors() const
{
    return m_leftDoors;
}

bool CSCP::rightDoors() const
{
    return m_rightDoors;
}

void CSCP::openLeftDoors()
{
    m_leftDoors = OPEN;
}

void CSCP::openRightDoors()
{
    m_rightDoors = OPEN;
}

void CSCP::closeLeftDoors()
{
    m_leftDoors = CLOSE;
}

void CSCP::closeRightDoors()
{
    m_rightDoors = CLOSE;
}

bool CSCP::parkingBrake() const
{
    return m_parkingBrake;
}

void CSCP::setParkingBrake(bool parkingBrake)
{
    m_parkingBrake = parkingBrake;
}

void CSCP::notifyActionLeftDoors(bool state)
{
    if (state)
        m_eventHandler->notifyValueChanged(NOMBRE_PUERTAS, LADO_IZ + ';' + ACCION_ABR);
    else
        m_eventHandler->notifyValueChanged(NOMBRE_PUERTAS, LADO_IZ + ';' + ACCION_CRR);
}

void CSCP::notifyActionRightDoors(bool state)
{
    if (state)
        m_eventHandler->notifyValueChanged(NOMBRE_PUERTAS, LADO_DE + ';' + ACCION_ABR);
    else
        m_eventHandler->notifyValueChanged(NOMBRE_PUERTAS, LADO_DE + ';' + ACCION_CRR );
}
