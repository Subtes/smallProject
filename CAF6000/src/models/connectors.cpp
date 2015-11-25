#include "connectors.h"


bool Connectors::getBatteryConnector() const
{
    return batteryConnector;
}

void Connectors::setBatteryConnector(bool value)
{
    batteryConnector = value;
}

bool Connectors::getPantographConnector() const
{
    return pantographConnector;
}

void Connectors::setPantographConnector(bool value)
{
    pantographConnector = value;
}

bool Connectors::getCompressorAuxConnector() const
{
    return compressorAuxConnector;
}

void Connectors::setCompressorAuxConnector(bool value)
{
    compressorAuxConnector = value;
}

bool Connectors::getConverterConnector() const
{
    return converterConnector;
}

void Connectors::setConverterConnector(bool value)
{
    converterConnector = value;
}

bool Connectors::getMainCompressorConnector() const
{
    return mainCompressorConnector;
}

void Connectors::setMainCompressorConnector(bool value)
{
    mainCompressorConnector = value;
}

bool Connectors::getLightingConnector() const
{
    return lightingConnector;
}

void Connectors::setLightingConnector(bool value)
{
    lightingConnector = value;
}

bool Connectors::getAirConnector() const
{
    return airConnector;
}

void Connectors::setAirConnector(bool value)
{
    airConnector = value;
}

bool Connectors::getMegaphoneConnector() const
{
    return megaphoneConnector;
}

void Connectors::setMegaphoneConnector(bool value)
{
    megaphoneConnector = value;
}

bool Connectors::getParkingBrakeConnector() const
{
    return parkingBrakeConnector;
}

void Connectors::setParkingBrakeConnector(bool value)
{
    parkingBrakeConnector = value;
}
Connectors::Connectors()
{

}

Connectors::~Connectors()
{

}

