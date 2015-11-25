#ifndef TOPBOARDCONNECTORS_CONTROLLER_H
#define TOPBOARDCONNECTORS_CONTROLLER_H

#include <QObject>
#include <singlebutton.h>
#include "src/models/subtestatus.h"

class TopBoardConnectors_Controller : public QObject
{
    Q_OBJECT
public:

    static const int EN_MARCHA = 1;
    static const int APAGADO = 0;

    explicit TopBoardConnectors_Controller(SubteStatus *subte);
    ~TopBoardConnectors_Controller();

    void setBattery(SingleButton *batteryCon, SingleButton *batteryDes);
    void setConmutadorPuestaServicio(SingleButton *conmutador, SingleButton *luzLlaveDes, SingleButton *luzLlaveCon, SingleButton *arranqueDes, SingleButton *arranqueCon);
    void setPantograph(SingleButton *pantographCon, SingleButton *pantographDes);
    void setCompressorAux(SingleButton *compressorAuxCon, SingleButton *compressorAuxDes);
    void setConverter(SingleButton *converterCon,SingleButton *converterDes );
    void setMainCompressor(SingleButton *mainCompressorCon, SingleButton *mainCompressorDes);
    void setLighting(SingleButton *lightingCon, SingleButton *lightingDes);
    void setAir(SingleButton *airCon, SingleButton *airDes);
    void setMegaphone(SingleButton *megaphoneCon, SingleButton *megaphoneDes);
    void setParkingBrake(SingleButton *parkingBrakeCon, SingleButton *parkingBrakeDes);

    void setEstado(int state);
    void reset();

private:

    void resetToMarcha();
    void resetToApagado();

    SubteStatus *m_subte;
    SingleButton *m_batteryCon;
    SingleButton *m_conmutador;
    SingleButton *m_luzLlaveDes;
    SingleButton *m_luzLlaveCon;
    SingleButton *m_arranqueDes;
    SingleButton *m_arranqueCon;
    SingleButton *m_batteryDes;
    SingleButton *m_pantographCon;
    SingleButton *m_pantographDes;
    SingleButton *m_compressorAuxCon;
    SingleButton *m_compressorAuxDes;
    SingleButton *m_converterCon;
    SingleButton *m_converterDes;
    SingleButton *m_mainCompressorCon;
    SingleButton *m_mainCompressorDes;
    SingleButton *m_lightingCon;
    SingleButton *m_lightingDes;
    SingleButton *m_airCon;
    SingleButton *m_airDes;
    SingleButton *m_megaphoneCon;
    SingleButton *m_megaphoneDes;
    SingleButton *m_parkingBrakeCon;
    SingleButton *m_parkingBrakeDes;

    bool m_conmutadorPuestaServicioStatus;
    bool m_enMarcha;
    int m_lastState=APAGADO;

private slots:
    void batteryConPressed();
    void batteryDesPressed();
    void conmutadorPuestaServicioPressed();
    void conmutadorPuestaServicioAutomaticaConPressed();
    void conmutadorPuestaServicioAutomaticaDesPressed();
    void pantographConPressed();
    void pantographDesPressed();
    void compressorAuxConPressed();
    void compressorAuxDesPressed();
    void converterConPressed();
    void converterDesPressed();
    void mainCompressorConPressed();
    void mainCompressorDesPressed();
    void lightingConPressed();
    void lightingDesPressed();
    void airConPressed();
    void airDesPressed();
    void megaphoneConPressed();
    void megaphoneDesPressed();
    void parkingBrakeConPressed();
    void parkingBrakeDesPressed();

signals:
    batteryCon();
    batteryDes();
};

#endif // TOPBOARDCONNECTORS_CONTROLLER_H
