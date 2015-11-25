#ifndef BOARDHARDWARE_H
#define BOARDHARDWARE_H

#include <tractionhardware.h>

#include "baseboard.h"
#include "src/controllers/horn_controller.h"
//#include "src/controllers/tractionlever_controller.h"
//#include "src/controllers/rana_controller.h"
//#include "src/controllers/hombremuerto_controller.h"
#include "src/controllers/seta_controller.h"

namespace Ui {
class BoardHardware;
}

class BoardHardware : public BaseBoard
{
    Q_OBJECT

public:
    explicit BoardHardware(QWidget *parent = 0, SubteStatus *subte = 0, EventHandler *eventHandler = 0);
    ~BoardHardware();



public slots:
    void startBoard();
    void enableScreen();
    void disableScreen();
    void resetControls();
    void loadState(int state);

    void bocinaON();
    void bocinaOFF();
    void ranaAD();
    void ranaCERO();
    void ranaAT();
    void setaON();
    void setaOFF();

    void setHardware(TractionHardware *th);

private:
    Ui::BoardHardware *ui;

    Horn_Controller *m_horn;
 //   TractionLever_Controller *m_tractionLever;
//    Rana_Controller *m_rana;
 //   HombreMuerto_Controller *m_hombreMuerto;
    Seta_Controller *m_setaButton;
    TractionHardware *m_tractionHardware;
};

#endif // BOARDHARDWARE_H
