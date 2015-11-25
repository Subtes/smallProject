#ifndef LLAVEMODOCONDUCCION_CONTROLLER_H
#define LLAVEMODOCONDUCCION_CONTROLLER_H

#include "base_controller.h"
#include "llavemodoconduccion.h"

class LlaveModoConduccion_Controller : public Base_Controller
{
    Q_OBJECT
public:
    LlaveModoConduccion_Controller(SubteStatus *subte, LlaveModoConduccion *llave);
    ~LlaveModoConduccion_Controller();
signals:
    menssajeModeAcople();
    mensajeModeManiobra();
    mensajeModeNormal();
private:
    LlaveModoConduccion *m_llave;

public slots:
    void setManiobraMode();
    void setAtpMode();
    void setAcopleMode();

};

#endif // LLAVEMODOCONDUCCION_CONTROLLER_H
