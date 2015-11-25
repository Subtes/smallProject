#ifndef SICASMAC_CONTROLLER_H
#define SICASMAC_CONTROLLER_H

#include <tractionhardware.h>

#include "sicasmac.h"
#include "base_controller.h"
#include "QString"
#include "QStringList"
#include "vector"
#include "math.h"
class SicasMac_Controller : public Base_Controller
{
    Q_OBJECT

 private:
    //NOSE SI TENGO QUE GENERAR ACÁ LA MATRIZ!
    SicasMac * m_sicasmac;
    int cantPantallasSicas;
    int renglon;
    int cantCochesTotal;
    int indiceArre;
    int DatosPorCoche;
    int maxRenglonesSicas;
    QStringList pantallasicas ;
    QStringList saveId ;
    QStringList estAnteriorFallaCocheSicas;
    int buscoPosicion(QString mensaje);
    void borrarSicas();
    void verificoEstFalla(QString falla, int coche);
    void verificoEstPuertas(QString falla, int coche);
    QStringList separoCaracteres(QString mensaje);
    void bajaMensaje(QString texto);
    void refrescoVista();
    void borrarPantallaSicas();
    void generoRenglonesSicas(QString texto, QString trenes, QString letra, int renglon);
    void cargoVectorEstadoAnteriorFalla();

    TractionHardware *m_hardwareSupport = NULL;


signals:
    playSound(int);


public:
    SicasMac_Controller(SubteStatus * subte, SicasMac * sicas, TractionHardware *th);
    ~SicasMac_Controller();
     void resetSicas();

public slots:
    void onPressSigRow();
    void onPressAntRow();
    void prendoSicas();
    void separoMensajes(QString mensaje);
    void cargoCoches(QString mensajeCoches);
    void cargarDestinoSicas(QString destino);
    void estadoFreno(bool state);
    void cargarMensajeAcople();
    void sacoMensajeAcople();
    void logicaPuertasSicas(bool b);
    void cargarMensajeDisyuntor();
    void sacoMensajeDisyuntor();
    void cargarMensajeCompDesconectado();
    void sacoMensajeCompDesconectado();
    void cargarMensajeConvFueraServicio();
    void sacoMensajeConvFueraServicio();
    void cargarMensajeFrenoEstacAplicado();
    void sacoMensajeFrenoEstacAplicado();
    void turnOnSicas();


};

#endif // SICASMAC_CONTROLLER_H
