#ifndef TRACTIONLEVER_CONTROLLER_H
#define TRACTIONLEVER_CONTROLLER_H

#include <tractionlever.h>
#include <tractionhardware.h>
#include "src/models/subtestatus.h"
class TractionLever_Controller : public QObject
{
    Q_OBJECT

public:
    TractionLever_Controller(SubteStatus * subte, TractionLever * slider, TractionHardware *th);
    ~TractionLever_Controller();
    void setValue(int v);

public slots:
    void onTractionLever();
    void offTractionLever();
    void processValue(int);

private:
    TractionHardware * m_tractionHardware;
    TractionLever * m_tractionLever;
    SubteStatus * m_subte;
    QTimer * m_checkJ;
    QTimer * m_checkB;
};

#endif // TRACTIONLEVER_CONTROLLER_H
