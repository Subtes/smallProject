#include "enethelper.h"

ENetHelper::ENetHelper(ENetClient *client)
{
    eNetClient = client;
}

ENetHelper::~ENetHelper()
{

}

void ENetHelper::initENet(ENetClient *eNetClient, EventHandler *eventHandler){
    //=== eNet setup ===
    readIni();

    using namespace std::placeholders;
    eNetClient->OnCambioValClave = std::bind(&EventHandler::processValueChanged, eventHandler, _1, _2, _3);

    if (!eNetClient->Conectar(serverIp, serverPort, controlsHostName)){
        qDebug() << "ERROR AL CONECTAR CON EL SERVIDOR";
        qDebug() << "Intento conectar con:: servidor " << serverIp.c_str() << " , puerto "<< serverPort << " , host "<< controlsHostName.c_str();
    }
    eNetClient->Suscribirse(instructionsHostName,"i_iniciar_simulador");
}

void ENetHelper::readIni()
{
    QDomDocument xml;

    QString fileName = QDir(qApp->applicationDirPath())
            .absoluteFilePath("etc/control.ini");

    qDebug() << "LECTURA DEL ARCHIVO DE CONFIGURACION .INI: " ;
    qDebug() << "Ubicacion del archivo: " << fileName;

    QFile f(fileName);
    if (!f.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error en la carga del archivo de configuracion control.ini";
        return;
    }

    xml.setContent(&f);
    f.close();

    QDomElement root=xml.documentElement();

    qDebug() << "XML: root object" << root.nodeName();

    serverIp = root.namedItem("serverIp").toElement().text().toStdString();
    serverPort = root.namedItem("serverPort").toElement().text().toInt();
    controlsHostName = root.namedItem("m_controlsHostName").toElement().text().toStdString();
    visualHostName = root.namedItem("m_visualHostName").toElement().text().toStdString();
    instructionsHostName = root.namedItem("m_instructionsHostName").toElement().text().toStdString();

    qDebug() << "XML: server Ip: " << serverIp.c_str();
    qDebug() << "XML: server Port: " << serverPort;
    qDebug() << "XML: controls Host Name: " << controlsHostName.c_str();
    qDebug() << "XML: visual Host Name: " << visualHostName.c_str();
    qDebug() << "XML: instructions Host Name: " << instructionsHostName.c_str();
}

