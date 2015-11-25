#ifndef RANA_CONTROLLER_H
#define RANA_CONTROLLER_H

#include <QObject>
#include <rana.h>
#include <tractionhardware.h>
#include "src/models/subtestatus.h"

class Rana_Controller : public QObject
{
    Q_OBJECT

public:
    Rana_Controller(SubteStatus *modelo, Rana *vista, TractionHardware *th);
    ~Rana_Controller();

public slots:
    void processValue(int);
    void setValue(int v);

private:
    Rana *m_ranaTraction;
    SubteStatus *m_subte;
    TractionHardware *m_tractionHardware;
};

#endif // RANA_CONTROLLER_H
