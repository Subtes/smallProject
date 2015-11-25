#ifndef CIRCUITBREAKERCON_CONTROLLER_H
#define CIRCUITBREAKERCON_CONTROLLER_H

#include <QObject>
#include <singlebutton.h>
#include "src/models/subtestatus.h"

class CircuitBreakerCON_Controller : public QObject
{
    Q_OBJECT
public:
    explicit CircuitBreakerCON_Controller(SubteStatus *subte,SingleButton *button=0);
    ~CircuitBreakerCON_Controller();

public slots:
    void pressCircuitBreakerCON();
    
private:
    SubteStatus *m_model = NULL;
    SingleButton *m_view = NULL;
    
};

#endif // CIRCUITBREAKERCON_CONTROLLER_H
