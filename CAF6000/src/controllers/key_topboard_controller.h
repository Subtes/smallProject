#ifndef KEY_TOPBOARD_CONTROLLER_H
#define KEY_TOPBOARD_CONTROLLER_H

#include <QObject>
#include <QVariant>
#include <tractionhardware.h>

#include "llavetecho.h"
#include "src/models/subtestatus.h"

class Key_TopBoard_Controller : public QObject
{
    Q_OBJECT

public:
    Key_TopBoard_Controller(SubteStatus *modelo, LlaveTecho *view, TractionHardware *th);
    ~Key_TopBoard_Controller();
    void resetToOff();
    QVariant isON();

    void keyTurnON();
    void keyTurnOFF();

public slots:
    //Acction launched from item ui
    void keyON();
    void keyOFF();
    void processKeyTop(int);
    void onKeyHD();
    void offKeyHD();

private:
    //State of KeyTopBoard
    LlaveTecho *m_keyButton = NULL;
    SubteStatus *m_modelo = NULL;
    TractionHardware *m_tractionHardware = NULL;

    QTimer * m_checkJ;
};

#endif // KEY_TOPBOARD_CONTROLLER_H
