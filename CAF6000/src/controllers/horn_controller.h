#ifndef HORN_CONTROLLER_H
#define HORN_CONTROLLER_H

#include <QObject>
#include <foothorn.h>
#include "src/models/subtestatus.h"

class Horn_Controller : public QObject
{
    Q_OBJECT

public:
    Horn_Controller(SubteStatus *subte,FootHorn *pedal=0);
    ~Horn_Controller();

    void setBocina(bool);

private:
    SubteStatus *m_subte;
    FootHorn *m_pedal;
};

#endif // HORN_CONTROLLER_H
