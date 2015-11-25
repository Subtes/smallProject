#ifndef BOARDCENTER_H
#define BOARDCENTER_H

#include "baseboard.h"
#include "src/controllers/wiper_controller.h"
#include "src/controllers/emergencyoverride_controller.h"
#include "src/controllers/tractionbypass_controller.h"
#include "src/controllers/brakebypass_controller.h"
#include "src/controllers/speedgaugeleds_controller.h"
#include "src/controllers/doors_controller.h"

namespace Ui {
class BoardCenter;
}

class BoardCenter : public BaseBoard
{
    Q_OBJECT

public:
    explicit BoardCenter(QWidget *parent = 0, SubteStatus *subte = 0, EventHandler *eventHandler = 0);
    void onCheckBypass();
    void offCheckBypass();
    ~BoardCenter();

public slots:
    void startBoard();
    void enableScreen();
    void disableScreen();
    void resetControls();
    void loadState(int state);

    void bypassTraccionON();
    void bypassTraccionOFF();
    void bypassFrenoON();
    void bypassFrenoOFF();

    void turnOnWidgets();
    void turnOffWidgets();

    void setHardware(TractionHardware *th);

private:
    Ui::BoardCenter *ui;

    Wiper_Controller                *m_wiper;
    EmergencyOverride_Controller    *m_emergencyOverride;
    TractionBypass_Controller       *m_tractionBypass;
    BrakeBypass_Controller          *m_brakesBypass;
    SpeedGaugeLeds_Controller       *m_speedGauge;
    Doors_Controller                *m_doors;
    TractionHardware                *m_tractionHardware = NULL;
    QTimer * m_checkBypass;
};

#endif // BOARDCENTER_H
