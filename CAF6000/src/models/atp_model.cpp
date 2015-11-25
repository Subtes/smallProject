#include "atp_model.h"
#include <QDebug>

ATP_model::ATP_model()
{
    m_allowedSpeed = 0;
    m_targetSpeed = 0;
    m_code = "";
    m_traction=true;
}

ATP_model::~ATP_model()
{

}

bool ATP_model::tractionReady()
{
    return m_traction;
}

void ATP_model::reset()
{
    m_allowedSpeed = 0;
    m_targetSpeed = 0;
    m_code = "";
}

double ATP_model::allowedSpeed() const
{
    return m_allowedSpeed;
}

void ATP_model::setAllowedSpeed(double allowedSpeed)
{
    m_allowedSpeed = allowedSpeed;
}

double ATP_model::targetSpeed() const
{
    return m_targetSpeed;
}

void ATP_model::setTargetSpeed(double targetSpeed)
{
    m_targetSpeed = targetSpeed;
}

std::string ATP_model::code() const
{
    qDebug()<< "ERROR std";
    return m_code;
}

void ATP_model::setCode(const std::string &code)
{
    qDebug()<< "ERROR std";
    m_code = code;
}

void ATP_model::cutTraction()
{
    m_traction = false;
}

void ATP_model::enableTraction()
{
    m_traction = true;
}
