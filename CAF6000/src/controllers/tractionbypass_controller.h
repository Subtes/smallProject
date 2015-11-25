#ifndef TRACTIONBYPASS_CONTROLLER_H
#define TRACTIONBYPASS_CONTROLLER_H

#include <QObject>
#include <singlebutton.h>
#include <tractionhardware.h>
#include "src/models/subtestatus.h"

class TractionBypass_Controller : public QObject
{
    Q_OBJECT

public:
    TractionBypass_Controller(SubteStatus *subte,SingleButton *button=0, TractionHardware *th=0);
    ~TractionBypass_Controller();

private:
    SubteStatus *m_subte;
    SingleButton *m_button;
    TractionHardware *m_tractionHardware;
    QTimer * m_checkTB;

public slots:
    void updateStatus(bool status);
    void pressBypass();
    void releaseBypass();
    void onBypassHD();
    void offBypassHD();

};

#endif // TRACTIONBYPASS_CONTROLLER_H
