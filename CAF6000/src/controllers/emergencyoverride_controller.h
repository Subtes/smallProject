#ifndef EMERGENCYOVERRIDE_CONTROLLER_H
#define EMERGENCYOVERRIDE_CONTROLLER_H

#include <QObject>
#include <singlebutton.h>
#include "src/models/subtestatus.h"

class EmergencyOverride_Controller : public QObject
{
    Q_OBJECT

public:
    EmergencyOverride_Controller(SubteStatus *subte,SingleButton *button=0);
    ~EmergencyOverride_Controller();

private:
    SubteStatus *m_subte;
    SingleButton *m_button;

private slots:
    void emergencyOverrideClicked();
};

#endif // EMERGENCYOVERRIDE_CONTROLLER_H
