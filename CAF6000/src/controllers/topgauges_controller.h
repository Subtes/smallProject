#ifndef TOPGAUGES_CONTROLLER_H
#define TOPGAUGES_CONTROLLER_H
#include "analoggauge.h"
#include "src/models/subtestatus.h"

class TopGauges_Controller : public QObject
{
    Q_OBJECT

private:
    AnalogGauge * m_voltmeter;
    AnalogGauge * m_ammeter;
    AnalogGauge * m_effortmeter;
    SubteStatus * m_subte;

public:
    TopGauges_Controller(SubteStatus * subte, AnalogGauge * voltmeter, AnalogGauge * ammeter, AnalogGauge * effortmeter);
    ~TopGauges_Controller();

public slots:
    void updateEffort(double effort);
    void updateVolts(double effort);
    void updateAms(double effort);
    void turnOffGauges();
    void turnOnGauges();
};

#endif // TOPGAUGES_CONTROLLER_H
