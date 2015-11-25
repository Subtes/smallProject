#ifndef SPEEDGAUGELEDS_CONTROLLER_H
#define SPEEDGAUGELEDS_CONTROLLER_H
#include "speedgaugeleds.h"
#include "src/models/subtestatus.h"

class SpeedGaugeLeds_Controller : public QObject
{
    Q_OBJECT

private:
    SpeedGaugeLeds * m_gauge;
    SubteStatus * m_subte;

public:
    SpeedGaugeLeds_Controller(SubteStatus * subte, SpeedGaugeLeds * gauge);
    ~SpeedGaugeLeds_Controller();

public slots:
    void updateSpeed(double speed);
    void updateTargetSpeed(double speed);
    void updateAllowedSpeed(double speed);
    void modeOperation(int m);
};

#endif // SPEEDGAUGELEDS_CONTROLLER_H
