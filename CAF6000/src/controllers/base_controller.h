#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

#include <QObject>
#include "src/models/subtestatus.h"

class Base_Controller  : public QObject
{
    Q_OBJECT

public:
    Base_Controller(SubteStatus *subte);
    ~Base_Controller();

protected:
    SubteStatus *m_subte;
};

#endif // BASE_CONTROLLER_H
