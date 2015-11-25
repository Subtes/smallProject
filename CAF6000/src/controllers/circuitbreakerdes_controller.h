#ifndef CIRCUITBREAKERDES_CONTROLLER_H
#define CIRCUITBREAKERDES_CONTROLLER_H

#include <QObject>
#include <singlebutton.h>
#include "src/models/subtestatus.h"

class CircuitBreakerDES_Controller : public QObject
{
    Q_OBJECT
public:
    explicit CircuitBreakerDES_Controller(SubteStatus *subte,SingleButton *button=0);
    ~CircuitBreakerDES_Controller();

public slots:
    void pressCircuitBreakerDES();

private:
    SubteStatus *m_model = NULL;
    SingleButton *m_view = NULL;
};

#endif // CIRCUITBREAKERDES_CONTROLLER_H
