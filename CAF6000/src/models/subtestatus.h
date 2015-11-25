#ifndef SUBTESTATUS_H
#define SUBTESTATUS_H

#include <QObject>
#include <QDebug>
#include <QtXml>
#include <QFile>
#include <QSplashScreen>
#include <QPixmap>

#include "src/controllers/eventhandler.h"
#include "src/models/cscp.h"
#include "src/models/brake.h"
#include "src/models/traction.h"
#include "src/models/atp_model.h"

class EventHandler;
class Brake;
class Traction;
class CSCP;

class SubteStatus : public QObject
{
    Q_OBJECT

private:
    EventHandler *m_eventHandler;

    // SUBTE STATUS
    CSCP *m_cscp;
    Brake *m_brake;
    ATP_model *m_ATP_model;
    Traction *m_traction;
    double m_speed;
    double m_effort;
    double  m_volts;
    double m_amps;
    //MANOMETER NEEDLE
    double m_pressure_red;
    double m_pressure_white;

    // CONTROL STATUS
    bool m_horn;
    bool m_emergencyOverride;
    bool m_seta;
    bool m_keyATP;
    std::string m_rana;
    bool m_CMC;
    bool m_CL;
    int m_modeOperation;

signals:
    // STATE CHANGE NOTIFICATION
    speedChanged(double speed);
    allowedSpeedChanged(double speed);
    targetSpeedChanged(double speed);
    hiloLazoChanged(bool status);
    effortChanged(double s_effort);
    voltChanged(double s_effort);
    ampsChanged(double s_effort);
    CSCPChanged(bool status);
    rightDoorsOpened();
    rightDoorsClosed();
    leftDoorsOpened();
    leftDoorsClosed();
    manometerWhiteChange(double s_effort);
    manometerRedChange(double s_effort);
    atpOn();
    atpOff();
    retentionBrakeChanged(bool status);
    bateriaCon();
    bateriaDes();
    modeOperation(int m);
    conmutadorServicioAutomatic();
    conmutadorServicioManual();
    conmutadorPServicioBotonCon();
    conmutadorPServicioBotonDes();
    senalDisyuntorDes();
    senalDisyuntorCon();
    frenoEstacionamientoCon();
    frenoEstacionamientoDes();
    estadoNormal();
    estadoManioAcople();



public:

    static const bool PUERTAS_CERRADAS = false;
    static const bool PUERTAS_ABIERTAS = true;

    SubteStatus();
    ~SubteStatus();

    void setHandler(EventHandler *eventHandler);
    void reset();

    // STATUS GETTERS
    bool cscp() const;
    bool leftDoors() const;
    bool rightDoors() const;
    double speed() const;
    double targetSpeed() const;
    double allowedSpeed() const;
    int traction() const;
    int brake() const;
    bool emergencyBrake() const;
    bool getHiloLazo();
    double getPressureRed() const;
    double getPressureWhite() const;

    // CONTROL GETTERS
    bool horn() const;
    bool emergencyOverride() const;
    bool seta() const;
    bool keyTopBoard() const;
    std::string rana() const;
    bool getDrivingModeATP();

public slots:
    // STATE CHANGE INVOCATIONS - SETTERS
    void updateSpeed(double value);
    void updateTargetSpeed(double value);
    void updateAllowedSpeed(double value);
    void wiperOn();
    void wiperOff();
    void washer();
    void tractionReceived(int value);
    void brakeReceived(int value);
    void ATP_emergencyBrakeActivated();
    void ATP_emergencyBrakeReleased();
    void hombreMuertoPressed();
    void hombreMuertoReleased();
    void openRightDoors();
    void openLeftDoors();
    void closeLeftDoors();
    void closeRightDoors();
    void disyuntoresCon();
    void disyuntoresDes();
    void hornOn();
    void hornOff();
    void emergencyOverridePressed();
    void setaActivated();
    void setaDeactivated();
    void keyActivated();
    void keyDeactivated();
    void ranaAD();
    void ranaCERO();
    void ranaAT();
    void cutTraction();
    void enableTraction();
    void setBatteryConnector(bool status);
    void setConmutadorPuestaServicio(bool status);
    void setConmutadorPuestaServicioAutomatica(bool status);
    void setPantographConnector(bool status);
    void setCompressorAuxConnector(bool status);
    void setConverterConnector(bool status);
    void setMainCompressorConnector(bool status);
    void setLightingConnector(bool status);
    void setAirConnector(bool status);
    void setMegaphoneConnector(bool status);
    void setParkingBrakeConnector(bool status);
    void updateEffort(double value);
    void updateVolt(double value);
    void updateAmm(double value);
    void bypassBrake(bool status);
    void bypassCSCP(bool status);
    void updatePreassureRed(double value);
    void updatePreassureWhite(double value);
    void updateLeftDoorsButtons(bool state);
    void updateRightDoorsButtons(bool state);
    void setTractionFailure();
    void setBrakeFailure();
    void setCSCPFailure();
    void resolveTractionFailure();
    void resolveBrakeFailure();
    void resolveCSCPFailure();
    void setManiobraMode();
    void setAtpMode();
    void setAcopleMode();
    void setRetentionBrakeBypass(bool state);
    void setRetentionBrake(bool state);
    void setSicasOk();
    // CMC, CL
    void setDrivingModeATP(bool status);
    void setModeOperation(int m);
};

#endif // SUBTESTATUS_H
