#ifndef FAILURES_CONTROLLER_H
#define FAILURES_CONTROLLER_H

#include <QObject>
#include "src/models/subtestatus.h"

class SubteStatus;
class EventHandler;

class Failures_Controller : public QObject
{
    Q_OBJECT

private:
    SubteStatus *m_subte;
    bool m_cscpFailing;
    bool m_brakeFailing;
    bool m_tractionFailing;

public:
    Failures_Controller(SubteStatus *subte);
    ~Failures_Controller();

public slots:
    void setFailure(std::string f);
};

#endif // FAILURES_CONTROLLER_H
