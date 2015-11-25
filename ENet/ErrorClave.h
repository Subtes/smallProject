#pragma once
#include <string>
#include <list>

enum class TipoErrorClave
{
  Ok,
  ClaveInexistente,
  HostInexistente
};


struct ErrorClave{
  TipoErrorClave Error;
  std::string TextoError;
  std::list<std::string> Valores;

  static ErrorClave CrearOK(std::string unValor)
  {
    ErrorClave result;
    result.Error = TipoErrorClave::Ok;
    result.TextoError = "";
    result.Valores.push_back(unValor);
    return result;
  }

  static ErrorClave CrearOK(void)
  {
    ErrorClave result;
    result.Error = TipoErrorClave::Ok;
    result.TextoError = "";
    return result;
  }

  static ErrorClave CrearClaveInexistente()
  {
    ErrorClave result;
    result.Error = TipoErrorClave::ClaveInexistente;
    result.TextoError = "Clave Inexistente";
    return result;
  }

  static ErrorClave CrearHostInexistente()
  {
    ErrorClave result;
    result.Error = TipoErrorClave::HostInexistente;
    result.TextoError = "Host Inexistente";
    return result;
  }
};

