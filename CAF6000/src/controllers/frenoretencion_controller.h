#ifndef FRENORETENCION_CONTROLLER_H
#define FRENORETENCION_CONTROLLER_H

#include "base_controller.h"
#include "singlebutton.h"

class FrenoRetencion_Controller : public Base_Controller
{
    Q_OBJECT
        
public:
    FrenoRetencion_Controller(SubteStatus *subte, SingleButton *button);
    ~FrenoRetencion_Controller();

private:
    SingleButton *m_button;

private slots:
    void updateBrakeState();

public slots:
    void turnOn();
    void turnOff();
};

#endif // FRENORETENCION_CONTROLLER_H
