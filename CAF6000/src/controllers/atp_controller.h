#ifndef ATP_CONTROLLER_H
#define ATP_CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QState>
#include <QFinalState>
#include <QStateMachine>
#include <QString>

#include <atp.h>
#include "src/models/subtestatus.h"
#include "src/controllers/eventhandler.h"


/**
 * @brief The Atp_Controller class
 */


class Atp_Controller : public QObject
{
    Q_OBJECT

public:

    Atp_Controller (SubteStatus *model, Atp *view, EventHandler *eventHandler);
    ~Atp_Controller();

signals:
    void enableBreakEmergency();
    void desableBreakEmergency();
    void cutTraction();
    void enableTraction();
    void speedRecovered();
    void subteStoped();
    void signalAnden();
    void reset();
    void enableBreakService(int);
    void desableBreakService(int);
    void offATP();

    void _1AtoB();
    void _2BtoA();
    void _3BtoC();
    void _4CtoB();
    void _5CtoD();
    void _6DtoC();

    void allowedSpeedChange(double);
    void playSound(int);

public slots:

    void updateTargetSpeed(double speed);
    void updateAllowedSpeed(double speed);
    void updateSpeed(double speed);
    void setDrivingMode(int);
    //Inicia la maquina de estados
    void initATP();
    void resetATP();

    void setSpeedTarget(double s);
    void setACE(double a);

    void departureEstation();

    void calculateDistance();

private slots:

    void routingA();
    void routingB();
    void routingC();
    void routingD();

    void setAllowedSpeed(double s);
    void transitionGT();

    void superviseSpeed();

    void nextToEstation();

private:
    Atp *m_view = NULL;
    SubteStatus *m_subte = NULL;
    EventHandler *m_eventHandler = NULL;

    double m_speed;
    double m_speedPrevious;

    double m_speedTarget;
    double m_speedTargetPrevious;

    double m_speedAllowed;
    double m_speedAllowedPrevious;

    //State transition, true if ATP is on transition
    bool m_transition;

    //Tasa desaceleracion
    double m_A1 = 0.7;

    //Atraso de freno
    double m_A_freno;

    //Grade maximo de la via
    double m_Gm;

    //Tada de la curva de reduccion de codigo
    double m_Tc;

    //Jerk de frenado
    double m_Jerk;

    //Speed Critique
    double m_speedCritique;

    //Driving Mode
    bool m_drivingModeCMC;
    bool m_drivingModeCL;
    bool m_drivingModeAL;
    bool m_drivingModeAT;

    //Speed Target Signal
    //HH Hacer que directamente reciba los codigo de via y según eso traduce a la speedTarget
    double m_AF_0 = 0;
    double m_AF_1 = 15;
    double m_AF_2 = 15;
    double m_AF_3 = 25;
    double m_AF_4 = 30;
    double m_AF_5 = 40;
    double m_AF_6 = 50;
    double m_AF_7 = 60;

    //Target Signal Recived
    QString m_AF;
    QString m_AF_previous;

    //Instant Acceleration
    double m_ACE;

    //Offset
    double m_OS_ACT;
    double m_OS_LCT;
    double m_OS_AFS;
    double m_OS_LFS;
    double m_OS_AFE;

    //uTVC (inhabilitado, curva, constante).
    int m_uTVC;

    //Distance GD
    double m_distanceGD;
    //Control Distance GD
    bool m_changeDistance;

    //Maquina de estados:
        //Estados:
    QState *m_e_A = NULL;
    QState *m_e_B = NULL;
    QState *m_e_C = NULL;
    QState *m_e_D = NULL;

        //Estado Final:
    QFinalState *m_e_Final_State = NULL;

        //Maquina de Estados:
    QStateMachine *m_machineATP = NULL;

        //Timer's:
    QTimer *m_t_evalChangeSpeed = NULL;
    QTimer *m_t_shot = NULL;

    //Timer T1 tiempo de la Transicion Gradual por Tiempo --> 3000
    int m_t_TGT;

    //Test if ATP is on
    bool m_onATP;
    QHash<int,int> *m_speedAD = NULL;

    void set_uTVC();
    void transitionGD();

    void critiqueSpeed(int);
    void onATP();
    void off_ATP();
    void setSignalTarget(QString s);

};

#endif // ATP_CONTROLLER_H
