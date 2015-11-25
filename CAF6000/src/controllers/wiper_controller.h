#ifndef WIPER_CONTROLLER_H
#define WIPER_CONTROLLER_H

#include <wiper.h>
#include "src/models/subtestatus.h"

class Wiper_Controller : public QObject
{
    Q_OBJECT

public:
    Wiper_Controller(SubteStatus * subte, Wiper * wiper);
    ~Wiper_Controller();

private:
    Wiper * m_wiper;
    SubteStatus * m_subte;
};

#endif // WIPER_CONTROLLER_H
