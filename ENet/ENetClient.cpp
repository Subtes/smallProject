#include "stdafx.h"
#include "ENetClient.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "AdmClaves.h"
#include <algorithm>

//#include <future>

ENetClient::ENetClient(void)
{
  Terminar = true;
  _fCliente = nullptr;
  _fServidor = nullptr;
  Inicializado = false;
  _dicClientes.clear();
  FMilisegundosEspera = 75;
}

ENetClient::~ENetClient(void)
{
  this-> Desconectar();

  if (_fServidor != nullptr)
  {
    Desconectar();
    _fServidor = nullptr;
  }

  if (_fCliente != nullptr)
  {
    enet_host_destroy(_fCliente);
    _fCliente = nullptr;
    _fServidor = nullptr;
  }
  enet_deinitialize();
}

bool ENetClient::EstaConectado()
{
  return _fServidor != nullptr && _fServidor->state == ENET_PEER_STATE_CONNECTED;
}

bool ENetClient::Conectar(std::string unaIP, int unPuerto, std::string unNombre)
{
  auto result = false;

  if (_fCliente == nullptr)
  {
    try
    {
      if (!Inicializado) Inicializado = enet_initialize() == 0;
    }
    catch (std::exception& e)
    {
      std::cout<<e.what();
      Inicializado = false;
    }

    if (!Inicializado) return false;

    try
    {
      _fCliente = enet_host_create(nullptr, 1, 5, 0, 0);
    }
    catch (std::exception& e1)
    {
      std::cout<<e1.what();
      _fCliente = nullptr;
    }

    if (_fCliente == nullptr) return result;

    ENetAddress direccionServidor;
    enet_address_set_host (&direccionServidor, unaIP.c_str());
    direccionServidor.port = unPuerto;

    try
    {
      //ENetEvent evento;
      _fServidor = enet_host_connect(_fCliente, &direccionServidor, 5, 0);
      int quepaso = enet_host_service (_fCliente, &_fEvento, 1500);
      if (quepaso > 0)
        ProcesarEvento();
      if (!EstaConectado())
      {
        _fServidor = nullptr;
        _fCliente = nullptr;
      }
    }
    catch (std::exception& e3)
    {
      std::cout<<e3.what();
      _fServidor = nullptr;
      _fCliente = nullptr;
    }

    if (EstaConectado())
    {
      result = true;
      Terminar = false;
      FMilisegundosEspera = 25;
      _threads.push_back(std::thread(&ENetClient::ProcesarBuffersENet, this, true)); // Pos 0, thread que encola los mensajes
      _threads.push_back(std::thread(&ENetClient::ProcesarColaMensajes, this)); // Pos 1, thread que saca los mensajes
      ColocarMiNombre(unNombre);
    }
  }

  return result;
}

bool ENetClient::Desconectar()
{
  bool result = false;
  if (EstaConectado())
  {
    Terminar = true;
    enet_peer_disconnect_now(_fServidor, 0);

    _threads[0].join();
    _threads[1].join();
    result = true;
    _fServidor = nullptr;
    _fCliente = nullptr;
    if (OnDisconnect != nullptr) OnDisconnect();
  }
  return result;
}

void ENetClient::do_work()
{
  try
  {
    while (_fServidor != nullptr && _fServidor->state == ENET_PEER_STATE_CONNECTED && enet_host_service (_fCliente, &_fEvento, FMilisegundosEspera) > 0)
    {
      ProcesarEvento();
    }
  }
  catch (std::exception& e)
  {
    std::cout<<"Hubo un error"<<e.what();
  }
}

void ENetClient::ProcesarBuffersENet(bool continuo)
{
  if (continuo) Terminar = false;
  while (!Terminar)
  {
    do_work();
  }
  if (!continuo)
  {
    do_work();
  }
}

void ENetClient::ProcesarColaMensajes()
{
  while (!Terminar)
  {
    while (!_fColaMsj.empty())
    {
      std::string mensaje;
      s_mutex.lock();

      mensaje = _fColaMsj.front();
      _fColaMsj.pop();

      s_mutex.unlock();

      std::vector<std::string> partes = StringSplit2(mensaje, "||");

      if (partes.size() <= 1 && OnErrorRecibir != nullptr)
      {
        OnErrorRecibir("Mensaje Erroneo Recibido", mensaje);
        return;
      }

#pragma region Difusion
      if (partes[0] == "difusion")
      {
        bool estadoDifusion = ConvertStrToBool(partes[2]);
        std::string cliente = partes[1];

        _dicClientes[cliente] = estadoDifusion;

        if (OnClienteCambiaDifusion != nullptr)
          OnClienteCambiaDifusion(cliente, estadoDifusion);
      }
#pragma endregion

#pragma region Cambio de Clave
      if (partes[0] == "valClave" && OnCambioValClave != nullptr)
      {
        if (partes.size() == 3) partes.push_back("");
        if (partes.size()!=4)
        {
          if (OnErrorRecibir != nullptr)
            OnErrorRecibir("Se recibió mal el valor de una clave desde el servidor",mensaje);
        }
        else
        {
          Claves.AgregarClave(partes[1], partes[2], partes[3]);
          if (!ExisteCliente(partes[1]) || _dicClientes[partes[1]])
            OnCambioValClave(partes[1], partes[2], partes[3]);
        }
      }
#pragma endregion 

#pragma region Conexión de Cliente
      if (partes[0] == "seConectoCliente" && OnConnectHost != nullptr)
      {
        if (partes.size() != 2)
          if (OnErrorRecibir != nullptr)
            OnErrorRecibir("Se recibió mal el valor de conexión de un Host",mensaje);
          else
            OnConnectHost(partes[1]);
      }
#pragma endregion 

#pragma region Desconexión de Cliente
      if (partes[0] == "seDesConectoCliente" && OnDisconnectHost != nullptr)
      {
        if (partes.size() != 2)
          if (OnErrorRecibir != nullptr)
            OnErrorRecibir("Se recibió mal el valor de desconexión de un Host",mensaje);
          else
            OnDisconnectHost(partes[1]);
      }
#pragma endregion
    }
  }
}

void ENetClient::ProcesarEvento()
{
  std::string mensaje;
  std::vector<std::string> partes;
  std::vector<char> myString;
  switch (_fEvento.type)
  {
  case ENET_EVENT_TYPE_RECEIVE:
#pragma region Recepcion
    myString = std::vector<char>(_fEvento.packet->dataLength + 1);
    myString[_fEvento.packet->dataLength] = '\0';
    memcpy(&myString[0], _fEvento.packet->data, _fEvento.packet->dataLength);

    s_mutex.lock();
    _fColaMsj.push(std::string(&myString[0]));
    s_mutex.unlock();

    enet_packet_destroy (_fEvento.packet);
#pragma endregion
    break;

  case ENET_EVENT_TYPE_CONNECT:
#pragma region Conexión
    if(OnConnect != nullptr) OnConnect();
#pragma endregion
    break;

  case ENET_EVENT_TYPE_DISCONNECT:
#pragma region DesConexión
    Terminar = true;
    _threads[0].join();
    _threads[1].join();
    _fServidor = nullptr;
    _fCliente = nullptr;
    _fEvento.peer -> data = nullptr;
    if (OnDisconnect != nullptr) OnDisconnect();
#pragma endregion
    break;

  case ENET_EVENT_TYPE_NONE: 
    break;
  default: break;
  }
}

bool ENetClient::ConvertStrToBool(std::string str)
{
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  std::istringstream is(str);
  bool b;
  is >> std::boolalpha >> b;
  return b;
}

bool ENetClient::Suscribirse(std::string unCliente, std::string unaClave)
{
  return EnviarMensaje(1, "suscripPeer||"+unCliente+"||"+unaClave);
}

bool ENetClient::DeSuscribirse(std::string unCliente, std::string unaClave)
{
  return EnviarMensaje(1, "dsuscripPeer||"+unCliente+"||"+unaClave);
}

bool ENetClient::CambiarValorClave(std::string unaClave, std::string unNuevoValor)
{
  return EnviarMensaje(1, "valClave||"+unaClave+"||"+unNuevoValor);
}

bool ENetClient::CambiarValorClave(std::string unCliente, std::string unaClave, std::string unNuevoValor)
{
  return EnviarMensaje(1, "valCClave||"+unCliente+"||"+unaClave+"||"+unNuevoValor);
}

bool ENetClient::ColocarMiNombre(std::string unNombre)
{
  return EnviarMensaje(2, "miNombre||"+unNombre);
}

bool ENetClient::CambiarEstadoDifusion(bool unNuevoEstado)
{
  //return EnviarMensaje(1, "difusion||"+ unNuevoEstado);
    std::string texto = "false";
     if (unNuevoEstado)
       texto = "true";
     return EnviarMensaje(1, "difusion||" + texto);
}

bool ENetClient::EnviarMensaje(short idCanal, std::string unTexto)
{
  if (!EstaConectado()) return false;
  bool result;

  const char* mensaje = unTexto.c_str();
  size_t longitud = strlen(mensaje) + 1;
  ENetPacket* packet = enet_packet_create (mensaje, longitud, ENET_PACKET_FLAG_RELIABLE);

  try
  {
    enet_peer_send (_fServidor, idCanal, packet);  
    //enet_host_flush(_fCliente);
    result = true;
  }
  catch (std::exception& e)
  {
    std::cout<<e.what();
    result = false;
  }

  return result;
}

std::vector<std::string> ENetClient::StringSplit2(std::string str, std::string delimiter) 
{
  std::vector<std::string> internal;

  size_t pos = 0;
  std::string token;
  while ((pos = str.find(delimiter)) != std::string::npos) 
  {
    token = str.substr(0, pos);
    //std::cout << token << std::endl;
    internal.push_back(token);
    str.erase(0, pos + delimiter.length());
  }
  internal.push_back(str);

  return internal;
}

std::vector<std::string> ENetClient::StringSplit(std::string str, char delimiter) 
{
  std::vector<std::string> internal;
  std::stringstream ss(str); // Turn the string into a stream.
  std::string tok;

  while(std::getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }

  return internal;
}

bool ENetClient::ExisteCliente(std::string unNombreCliente)
{
  return _dicClientes.find(unNombreCliente) != _dicClientes.end();
}
