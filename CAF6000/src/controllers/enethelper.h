#ifndef ENETHELPER_H
#define ENETHELPER_H

#include <QtXml>
#include <QFile>

#include "src/controllers/eventhandler.h"
#include "ENetClient.h"

class EventHandler;

class ENetHelper
{
public:
    ENetHelper(ENetClient *eNetClient);
    ~ENetHelper();

    void initENet(ENetClient *eNetClient, EventHandler *eventHandler);

    //=== eNet setup ===
    ENetClient *eNetClient;
    std::string serverIp;
    int serverPort;
    std::string controlsHostName;
    std::string visualHostName;
    std::string instructionsHostName;

private:
    void readIni();

};

#endif // ENETHELPER_H
