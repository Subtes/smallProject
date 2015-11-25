#define _F1 0x70
#define _F2 0x71
#define _F3 0x72
#define _F4 0x73
#define _F5 0x73

#define _A 0x41
#define _B 0x42
#define _H 0x48
#define _J 0x4A
#define _K 0x4B
#define _L 0x4C
#define _R 0x52
#define _tF 0x46
#define _T 0x54

#define _CERO 0x30
#define _UNO 0x31
#define _DOS 0x32
#define _TRES 0x33
#define _CUATRO 0x34
#define _CINCO 0x35
#define _SEIS 0x36
#define _SIETE 0x37
#define _OCHO 0x38
#define _NUEVE 0x39

#define _MAS 0xBB
#define _MENOS 0xBD

#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <QObject>
#include <QSplashScreen>
#include <QPixmap>
#include <QDesktopWidget>
#include <vector>
#include <stdio.h>
#include <ENetClient.h>
#include <Windows.h>
#include <QString>
#include <QTime>
#include "src/controllers/enethelper.h"
#include "src/controllers/keypresseater.h"
#include "src/controllers/failures_controller.h"
#include "src/models/subtestatus.h"


class SubteStatus;
class ENetHelper;
class Failures_Controller;

class EventHandler : public QObject
{
    Q_OBJECT

public:
    EventHandler(QDesktopWidget *desk);
    ~EventHandler();

    void processValueChanged(std::string host, std::string key, std::string value);
    void notifyValueChanged(std::string key, std::string value);
    void initConnection();

    void setModel(SubteStatus *subte);
    void setFailures(Failures_Controller *failures);

    void enableDiffusion();

private:
    ENetClient * m_eNetClient;
    ENetHelper * m_eNetHelper;
    Failures_Controller * m_failures;
    SubteStatus * m_subte;

    QSplashScreen *m_splash1;
    QSplashScreen *m_splash2;
    QSplashScreen *m_splash3;
    QSplashScreen *m_splash4;
    QDesktopWidget *m_desktop;
    QPixmap m_imageSplash;
    bool m_splashOn;
    int m_boardsReady = 0;
    std::string m_cargandoEstado = "";


    bool F1_down;
    bool F2_down;
    bool F3_down;
    bool F4_down;
    bool F5_down;
    bool A_down;
    bool B_down;
    bool C_down;
    bool F_down;
    bool H_down;
    bool J_down;
    bool K_down;
    bool L_down;
    bool R_down;
    bool T_down;
    bool CERO_down;
    bool UNO_down;
    bool DOS_down;
    bool TRES_down;
    bool CUATRO_down;
    bool CINCO_down;
    bool SEIS_down;
    bool SIETE_down;
    bool OCHO_down;
    bool NUEVE_down;
    bool MAS_down;
    bool MENOS_down;

    std::vector<std::string> split(std::string,char);
    void bajarSplash();
    void subirSplash();

signals:
    controlReady();
    controlDisable();
    controlEnable();
    controlReset();    
    closeApp();
    iCambioSenial1();
    bPressed();
    bReleased();
    aPressed();
    ceroPressed();
    rPressed();
    fPressed();
    tPressed();
    kPressed();
    lPressed();
    f3Pressed();
    f4Pressed();
    cPressed();
    frenoEstDes();
    doorsChanged(bool);
    downLoaderBoarders();
    accelerationInstant(double);
    nextToEstation();
    departureEstation();
    cargarEstado(int);
    kHardPressed();
    lHardPressed();
    masPressed();
    masReleased();
    menosPressed();
    menosReleased();

    cargarMensaje(QString);
    cargarMensajeCocheSicas(QString);
    cargarDestinoSicas(QString);

    newTarget(int);

public slots:
    void processKeyPressed(DWORD k);
    void processKeyReleased(DWORD k);

};

#endif // EVENTHANDLER_H
