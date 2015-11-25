#ifndef TRACTIONHARDWARE_H
#define TRACTIONHARDWARE_H

#include <QObject>
#include <QTimer>

#include "SDL.h"
#include "SDL_mixer.h"
#undef main

class TractionHardware : public QObject
{
    Q_OBJECT
public:
     TractionHardware();
    ~TractionHardware();
    void getdata();

signals:
    positionChanged(int);
    manDiedPressed();
    manDiedReleased();

    brakeBypassPressed();
    brakeBypassReleased();

    tractionBypassPressed();
    tractionBypassReleased();

    ranaY(int);
    seta(int);

    processKeyTop(int);

public slots:
    void processValueChanged();
    void processBottonChanged();
    void processRanaChanged();
    void processSetaChanged();
    void processKeyTop();
    bool isHardwareEnable();
    void reset();
    void onSound(int s);

private:
    SDL_Joystick *m_joystick;
    QList<int> axis;
    QList<bool> buttons;
    QString joystickName(int id);

    int m_neutral;
    int m_neutralLower;
    int m_neutralTop;
    int m_breakEmergency;
    int m_maxInterval;
    int m_minInterval;

    int m_traction;
    int m_value;
    int m_rangoT;
    int m_rangoB;

    bool m_diedMan;
    bool m_bypassBrake;
    bool m_bypassTraction;

    bool m_ranaAD;
    bool m_ranaAT;
    //bool m_ranaC;
    bool m_seta;
    bool m_keyTop;

    Mix_Music *m_sound_atp_target = NULL;
    Mix_Music *m_sound_atp_warning = NULL;
    Mix_Music * m_sound_sicas_warning = NULL;

};

#endif // TRACTIONHARDWARE_H
