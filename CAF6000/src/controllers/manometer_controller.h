#ifndef MANOMETER_CONTROLLER_H
#define MANOMETER_CONTROLLER_H
#include "manometer.h"
#include "base_controller.h"

class Manometer_Controller : public Base_Controller
{
    Q_OBJECT

private:
     Manometer * m_manometer;



public:
    Manometer_Controller(SubteStatus * subte, Manometer * manometer);
    ~Manometer_Controller();

public slots:
    void updatePressureRed(double m_needle_red);
    void updatePressureWhite(double m_needle_white);

};
#endif // MANOMETER_CONTROLLER_H
