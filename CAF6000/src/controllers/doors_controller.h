#ifndef DOORS_CONTROLLER_H
#define DOORS_CONTROLLER_H

#include "base_controller.h"
#include "singlebutton.h"

class Doors_Controller : public Base_Controller
{
    Q_OBJECT
public:
    Doors_Controller(SubteStatus *subte, SingleButton *openLeftDoors, SingleButton *closeLeftDoors, SingleButton *selectLeftDoors, SingleButton *openRightDoors, SingleButton *closeRightDoors, SingleButton *selectRightDoors, SingleButton *silbato);
    ~Doors_Controller();
    void reset();
    void turnOn();
    void turnOff();

public slots:
    void enableLeftPanel();
    void enableRightPanel();
    void openLeft();
    void openRight();
    void closeLeft();
    void closeRight();

private:
    SingleButton *m_selectLeftDoors;
    SingleButton *m_openLeftDoors;
    SingleButton *m_closeLeftDoors;
    SingleButton *m_selectRightDoors;
    SingleButton *m_openRightDoors;
    SingleButton *m_closeRightDoors;
    SingleButton *m_silbato;

private slots:
    void updateLeft();
    void updateRight();
    void updatePanel(bool b);
};

#endif // DOORS_CONTROLLER_H
