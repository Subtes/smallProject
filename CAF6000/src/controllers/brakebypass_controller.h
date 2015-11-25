#ifndef BRAKEBYPASS_CONTROLLER_H
#define BRAKEBYPASS_CONTROLLER_H

#include <tractionhardware.h>
#include "base_controller.h"
#include "singlebutton.h"

class BrakeBypass_Controller : public Base_Controller
{
    Q_OBJECT

public:
    BrakeBypass_Controller(SubteStatus *subte, SingleButton *button, TractionHardware * th);
    ~BrakeBypass_Controller();

private:
    SingleButton *m_button;
    TractionHardware *m_tractionHardware;

    QTimer * m_checkTB;

public slots:
    void bypassBrakePressed();
    void bypassBrakeReleased();
    void updateHiloLazoStatus(bool status);
//    void onBypassHD();
//    void offBypassHD();
};

#endif // BRAKEBYPASS_CONTROLLER_H
