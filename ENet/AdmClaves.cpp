#include "stdafx.h"
#include "AdmClaves.h"
#include "string"

AdmClaves::AdmClaves(void)
{
  _fValClaves.clear();
}

AdmClaves::~AdmClaves(void)
{
  _fValClaves.clear();
}

ErrorClave AdmClaves::AltaClave(std::string unHost, std::string unaClave)
{
  auto result = ErrorClave::CrearOK();

  _fValClaves[unHost][unaClave] = "";

  return result; 
}

ErrorClave AdmClaves::AgregarClave(std::string unHost, std::string unaClave, std::string unValor)
{
  auto result = ErrorClave::CrearOK();

  _fValClaves[unHost][unaClave] = unValor;

  return result; 
}

ErrorClave AdmClaves::ValorClave(std::string unHost, std::string unaClave)
{
  if (_fValClaves.find(unHost) == _fValClaves.end())
    return ErrorClave::CrearHostInexistente();

  if (_fValClaves[unHost].find(unaClave) == _fValClaves[unaClave].end())
    return ErrorClave::CrearClaveInexistente();

  return ErrorClave::CrearOK(_fValClaves[unHost][unaClave]);
}

ErrorClave AdmClaves::ClavesDeHost(std::string unHost)
{
  if (_fValClaves.find(unHost) == _fValClaves.end())
    return ErrorClave::CrearHostInexistente();

  auto result = ErrorClave::CrearOK();
  for(std::map<std::string, std::string>::iterator ii=_fValClaves[unHost].begin(); ii != _fValClaves[unHost].end(); ++ii)
    result.Valores.push_back(_fValClaves[unHost][ii->first]);
 
  return result;
}