#ifndef CONTROL_H
#define CONTROL_H

#include <QMainWindow>
#include <ENetClient.h>
#include <QDebug>

#include "boardcenter.h"
#include "boardhardware.h"
#include "boardleft.h"
#include "boardright.h"
#include "boardtop.h"
#include "src/models/subtestatus.h"

namespace Ui {
class Control;
}

class Control : public QMainWindow
{
    Q_OBJECT

public:
    explicit Control(QWidget *parent = 0, BoardCenter *c =0);
    ~Control();

    void initApp();
    void startApp();
    void listener(std::string host, std::string clave, std::string valor);

private:
    Ui::Control *ui;

    SubteStatus * m_subte;
    ENetClient *m_eNetClient;
    std::string m_serverIp;
    int m_serverPort;
    std::string m_controlsHostName;
    std::string m_instructionsHostName;
    BoardHardware *m_h;
    BoardCenter * m_c;
    BoardLeft *m_l;
    BoardRight *m_r;
    BoardTop *m_t;
};

#endif // CONTROL_H
