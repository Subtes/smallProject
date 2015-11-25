#pragma once

#include <string>
#include <map>
#include "ErrorClave.h"

class AdmClaves
{
  protected:
    bool FUsarDiccionario;
    std::map<std::string, std::map<std::string, std::string>> _fValClaves;

  public:
    AdmClaves(void);
    ~AdmClaves(void);

    bool UsarDiccionario() {return FUsarDiccionario;}
    void Set_UsarDiccionario(bool usarDiccionario) { FUsarDiccionario = usarDiccionario;}

    ErrorClave AltaClave(std::string unHost, std::string unaClave);
    ErrorClave AgregarClave(std::string unHost, std::string unaClave, std::string unValor);
    ErrorClave ValorClave(std::string unHost, std::string unaClave);
    ErrorClave ClavesDeHost(std::string unHost);
};

