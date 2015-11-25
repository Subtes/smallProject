#ifndef BRAKE_H
#define BRAKE_H

#include "traction.h"
#include "src/controllers/eventhandler.h"

class Traction;
class EventHandler;

class Brake
{

private:
    const std::string NOMBRE_FRENO = "c_freno";
    const std::string NOMBRE_FRENO_EMERGENCIA = "c_freno_emergencia";
    const std::string VALOR_CON_FRENO_EMERGENCIA = "con";
    const std::string VALOR_DES_FRENO_EMERGENCIA = "des";

    Traction *m_traction;
    EventHandler * m_eventHandler;

    bool m_emergencyBrake_tractionLever;
    bool m_emergencyBrake_atp;
    bool m_emergencyBrake_setas;
    bool m_emergencyBrake_HM;
    double m_brake;
    double m_lastBrake;
    bool m_bypass;
    bool m_retentioBrake;
    bool m_anulacionFrenoRetencion;
    bool m_averia;

public:
    Brake();
    ~Brake();
    void linkTraction(Traction *traction);
    void setHandler(EventHandler * eventHandler);
    bool braking();
    void reset();

    void notifyEmergencyBrake();
    void notifyBrake();


    //GETTERS & SETTERS
    bool getEmergencyBrake() const;
    bool getHiloLazo();
    void setEmergencyBrake_atp(bool value);
    void setEmergencyBrake_seta(bool value);
    void setEmergencyBrake_HM(bool value);
    double getBrake() const;
    void setBrake(double value);
    bool bypass() const;
    void setBypass(bool status);
    bool retentioBrake() const;
    void setRetentioBrake(bool retentioBrake);
    bool averia() const;
    void setAveria(bool averia);
    bool anulacionFrenoRetencion() const;
    void setAnulacionFrenoRetencion(bool anulacionFrenoRetencion);
};

#endif // BRAKE_H
