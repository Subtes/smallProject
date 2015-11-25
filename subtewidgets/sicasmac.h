#ifndef SICASMAC_H
#define SICASMAC_H
#include <vector>
#include <QWidget>
#include <QQuickItem>
#include <QString>


namespace Ui {
class SicasMac;
}

class SicasMac : public QWidget
{
    Q_OBJECT

public:
    explicit SicasMac(QWidget *parent = 0);
    ~SicasMac();
    void setBackgroudImage(QUrl bg);
    void setGlassImage(QUrl gl);
    void setFailure1(QUrl fl);
    void setFailure2(QUrl f2);
    void setFailure3(QUrl f3);
    void setFailure4(QUrl f4);
    void setFailure5(QUrl f5);
    void setFailure6(QUrl f6);
    void setStartTrain(QUrl at1);
    void setEndTrain(QUrl atend);
    void actualizarTamArreRenglon(int finRenglon);

signals:
    onPressSigRow();
    onPressAntRow();
    sicasOk();

protected:
    Ui::SicasMac *ui;
    QQuickItem *m_qmlView;

public slots:
       void startBlinkFailure(int failure);
       void stopBlink(int failure);
       void textEditSicas(QString pos1,QString pos2,QString pos3, int index);
       void insertTrainSicas(QString coche, QString estFreno);
       void turnOffFailure(int coche);
       void turnOnFailure(int coche);
       void turnBlinkFailure(int coche);
       void turnInhabFailure(int coche);
       void turnOffDoors(int coche);
       void turnOnDoors(int coche);
       void sigPosicionSicas();
       void antPositionSicas();
       void endRenglonSicas();
       void initRenglonSicas();
       void turnOnSiguiente();
       void turnOffSiguiente();
       void turnOnAnterior();
       void turnOffAnterior();
       int getPosActualRenglon();
       void turnOnSicas();
       void turnOffSicas();
       void cargoDestinoSicas(QString destino);
       void generarTrenesBlink(QString trenes, int index,bool parpadeo);
       void borrarArregloBlinkSicas(QString trenes, int index);
       void ponerOnSicasSinIncidencia();
       void ponerValoresInicio(int cantPantallas);


};

#endif // SICASMAC_H
