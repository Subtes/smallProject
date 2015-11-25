#include "subtestatus.h"
SubteStatus::SubteStatus()
{
    m_cscp = new CSCP();
    m_brake = new Brake();
    m_ATP_model = new ATP_model();
    m_traction = new Traction();

    m_brake->linkTraction(m_traction);
    m_traction->linkBrake(m_brake);
    m_traction->linkCSCP(m_cscp);
    m_traction->linkATP(m_ATP_model);

    m_speed = 0;
    m_effort = 0;
    m_volts = 0;
    m_amps = 0;

    //Manometer
    m_pressure_red=0;
    m_pressure_white = 0;

    m_horn = false;
    m_emergencyOverride = false;
    m_seta = false;
    m_keyATP = false;
    m_rana = "0";
    m_CMC = true;
    m_modeOperation = 0;
}

SubteStatus::~SubteStatus()
{
    delete m_cscp;
    delete m_brake;
    delete m_ATP_model;
    delete m_traction;
}

void SubteStatus::setHandler(EventHandler *eventHandler)
{
    m_eventHandler = eventHandler;
    m_brake->setHandler(eventHandler);
    m_traction->setHandler(eventHandler);
    m_cscp->setHandler(eventHandler);
}

void SubteStatus::reset()
{
    //STATUS
    m_cscp->reset();
    m_brake->reset();
    m_ATP_model->reset();
    m_traction->reset();
    m_speed = 0;

    //CONTROLS
    m_rana = "0";
    m_seta = false;
    m_keyATP = false;
}

bool SubteStatus::cscp() const
{
    return m_cscp->evalCircuit();
}

bool SubteStatus::leftDoors() const
{
    return m_cscp->leftDoors();
}

bool SubteStatus::rightDoors() const
{
    return m_cscp->rightDoors();
}

double SubteStatus::speed() const
{
    return m_speed;
}

double SubteStatus::targetSpeed() const
{
    return m_ATP_model->targetSpeed();
}

double SubteStatus::allowedSpeed() const
{
    return m_ATP_model->allowedSpeed();
}

int SubteStatus::traction() const
{
    return m_traction->getTraction();
}

int SubteStatus::brake() const
{
    return m_brake->getBrake();
}

bool SubteStatus::emergencyBrake() const
{
    return m_brake->getEmergencyBrake();
}

/**
 * @brief SubteStatus::getHiloLazo
 * @return true si se cumple, o false si esta el freno de emergencia activado o existe alguna averia.
 */
bool SubteStatus::getHiloLazo()
{
    return m_brake->getHiloLazo();
}

bool SubteStatus::horn() const
{
    return m_horn;
}

bool SubteStatus::emergencyOverride() const
{
    return m_emergencyOverride;
}

bool SubteStatus::seta() const
{
    return m_seta;
}

bool SubteStatus::keyTopBoard() const
{
    return m_keyATP;
}

std::string SubteStatus::rana() const
{
    return m_rana;
}

// SLOTS ///////////////////
/**
 * @brief SubteStatus::updateSpeed: checkea que haya un cambio de velocidad, si hay,
 * actualiza el valor en el modelo y en caso de volver a velocidad 0 reactiva la
 * evaluacion del sistema de cierre de puertas.
 * @param value: nueva velocidad
 */
void SubteStatus::updateSpeed(double value){
    if(m_speed != value){
        m_speed = value;
        emit speedChanged(m_speed);
        if( m_speed <= 0 && m_cscp->getBypass()){
            m_cscp->setBypass(false);
            emit CSCPChanged(m_cscp->evalCircuit());
        }

        if( m_speed <= 0 && m_brake->getEmergencyBrake()){
            m_brake->setEmergencyBrake_atp(false);
        }

        if((m_speed>4) && (m_cscp->leftDoors() || m_cscp->rightDoors())){
            m_cscp->notifyActionLeftDoors(CSCP::CLOSE);
            m_cscp->notifyActionRightDoors(CSCP::CLOSE);
        }
    }
}

void SubteStatus::updateTargetSpeed(double value){
    m_ATP_model->setTargetSpeed(value);
    emit targetSpeedChanged(value);
}

void SubteStatus::updateAllowedSpeed(double value){
    m_ATP_model->setAllowedSpeed(value);
    emit allowedSpeedChanged(value);
}

void SubteStatus::wiperOn()
{
    m_eventHandler->notifyValueChanged("c_limpiaParabrisas","on");
}

void SubteStatus::wiperOff()
{
    m_eventHandler->notifyValueChanged("c_limpiaParabrisas","off");
}

void SubteStatus::washer()
{
    m_eventHandler->notifyValueChanged("c_lavaParabrisas","on");
}

/**
 * @brief SubteStatus::tractionReceived: Cambia la posicion de la palanca de traccion
 * desde el widget o harware, y se conecta a este slot. El subsistema de traccion decide
 * si hay traccion o no. en caso de que la diferencia entre la ultima traccion emitida y
 * la nueva sea mayor a 5, se notifica el cambio en blackboard.
 * @param value: posicion de la palanca
 */
void SubteStatus::tractionReceived(int value){
    m_traction->updateTraction(value);
}

void SubteStatus::brakeReceived(int value){
    m_brake->setBrake(value);
}

/**
 * @brief SubteStatus::emergencyBrakeActived: se corta el hilo de lazo
 */
void SubteStatus::ATP_emergencyBrakeActivated(){
    m_brake->setEmergencyBrake_atp(true);
    m_traction->notifyTraction();
    emit hiloLazoChanged(getHiloLazo());
}

void SubteStatus::ATP_emergencyBrakeReleased(){
    m_brake->setEmergencyBrake_atp(false);
    m_traction->notifyTraction();
    emit hiloLazoChanged(getHiloLazo());
}

void SubteStatus::hombreMuertoPressed(){
    m_traction->setHombreMuerto(true);
    m_traction->notifyTraction();
    emit hiloLazoChanged(getHiloLazo());
}

void SubteStatus::hombreMuertoReleased(){
    m_traction->setHombreMuerto(false);
    m_traction->notifyTraction();
    emit hiloLazoChanged(getHiloLazo());
}

/**
 * @brief SubteStatus::disyuntoresCON: Para poder conectar los disyuntores, es necesario:
    Tensión normal de Batería
    Tensión suficiente en el Hilo de Trabajo
    Rana en AD o AT, con mando en su cabina
    Regulador de Mando en posición “0”
    Pulsar “CON”
 */
void SubteStatus::disyuntoresCon(){
    m_eventHandler->notifyValueChanged("c_disyuntor","con");
    emit senalDisyuntorCon();
    qDebug() << "Pressed CON Disyuntor";
}

/**
 * @brief SubteStatus::disyuntoresDes:  Para desconectar los disyuntores, solo se pulsa “DES”, en cualquiera de las cabinas de conducción.
 */
void SubteStatus::disyuntoresDes(){
    m_eventHandler->notifyValueChanged("c_disyuntor","des");
    emit senalDisyuntorDes();
    qDebug() << "Pressed DES Disyuntor";
    }

void SubteStatus::hornOn()
{
    qDebug() << "c_bocina: on";
    m_eventHandler->notifyValueChanged("c_bocina","on");
    m_horn = true;
}

void SubteStatus::hornOff()
{
    qDebug() << "c_bocina: off";
    m_eventHandler->notifyValueChanged("c_bocina","Off");
    m_horn = false;
}

void SubteStatus::emergencyOverridePressed(){
    m_emergencyOverride = !m_emergencyOverride;
    if(m_emergencyOverride){
        qDebug() << "c_emergencyOverride: con";
        m_eventHandler->notifyValueChanged("c_emergencyOverride","con");
    }else{
        qDebug() << "c_emergencyOverride: des";
        m_eventHandler->notifyValueChanged("c_emergencyOverride","des");
    }
}

void SubteStatus::setaActivated(){
    m_seta = true;
    m_brake->setEmergencyBrake_seta(true);
    m_traction->notifyTraction();
    m_eventHandler->notifyValueChanged("c_seta_emergencia","con");
    emit hiloLazoChanged(getHiloLazo());
}

void SubteStatus::setaDeactivated(){
    m_seta = false;
    m_brake->setEmergencyBrake_seta(false);
    m_traction->notifyTraction();
    m_eventHandler->notifyValueChanged("c_seta_emergencia","des");
    emit hiloLazoChanged(getHiloLazo());
}

void SubteStatus::keyActivated(){
    m_keyATP = true;
    m_eventHandler->notifyValueChanged("c_llave_atp","con");
    emit atpOn();
    qDebug() << "keyATP Model: " << m_keyATP;
}

void SubteStatus::keyDeactivated(){
    m_keyATP = false;
    m_eventHandler->notifyValueChanged("c_llave_atp","des");
    emit atpOff();
    qDebug() << "keyATP Model: " << m_keyATP;
}

void SubteStatus::ranaAD(){
    m_rana = "ad";
    m_traction->setDirection(Traction::RANA::AD);
    m_eventHandler->notifyValueChanged("c_rana","ad");
    qDebug() << "c_rana: AD";
}

void SubteStatus::ranaCERO(){
    m_rana = "0";
    m_traction->setDirection(Traction::RANA::CERO);
    m_eventHandler->notifyValueChanged("c_rana","0");
    m_traction->notifyTraction();
    qDebug() << "c_rana: 0";
    qDebug() << "c_traccion: " << m_traction->getTraction();
}

void SubteStatus::ranaAT(){
    m_rana = "at";
    m_traction->setDirection(Traction::RANA::AT);
    m_eventHandler->notifyValueChanged("c_rana","at");
    qDebug() << "c_rana: AT";
}

void SubteStatus::cutTraction(){
    qDebug() << "SubteStatus::cutTraction()";
    m_ATP_model->cutTraction();
}

void SubteStatus::enableTraction(){
    qDebug() << "SubteStatus::enableTraction()";
    m_ATP_model->enableTraction();
}

void SubteStatus::setBatteryConnector(bool status){
    if (status){
        m_eventHandler->notifyValueChanged("c_pulsador_bateria","con");
        emit bateriaCon();
        qDebug() << "c_pulsador_bateria: con";
    }else{
        m_eventHandler->notifyValueChanged("c_pulsador_bateria","des");
        emit bateriaDes();
        qDebug() << "c_pulsador_bateria: des";
    }
}
void SubteStatus::setConmutadorPuestaServicio(bool status){
    if (status){
        m_eventHandler->notifyValueChanged("c_conmutador_puesta_en_servicio","automatica");
        emit conmutadorServicioAutomatic();
        qDebug() << "c_conmutador_puesta_en_servicio: automatica";
    }else{
        m_eventHandler->notifyValueChanged("c_conmutador_puesta_en_servicio","manual");
        emit conmutadorServicioManual();
        qDebug() << "c_conmutador_puesta_en_servicio :manual";
    }
}

void SubteStatus::setConmutadorPuestaServicioAutomatica(bool status){
    if (status){
        m_eventHandler->notifyValueChanged("c_conmutador_puesta_en_servicio_automatica","con");
        emit conmutadorPServicioBotonCon();
        qDebug() << "c_conmutador_puesta_en_servicio_automatica :con";
    }else{
        m_eventHandler->notifyValueChanged("c_conmutador_puesta_en_servicio_automatica","des");
        emit conmutadorPServicioBotonDes();
        qDebug() << "c_conmutador_puesta_en_servicio_automatica: des";
    }
}

void SubteStatus::setPantographConnector(bool status){}
void SubteStatus::setCompressorAuxConnector(bool status){}
void SubteStatus::setConverterConnector(bool status){}
void SubteStatus::setMainCompressorConnector(bool status){}
void SubteStatus::setLightingConnector(bool status){}
void SubteStatus::setAirConnector(bool status){}
void SubteStatus::setMegaphoneConnector(bool status){}
void SubteStatus::setParkingBrakeConnector(bool status){
    if (status){
        m_eventHandler->notifyValueChanged("c_freno_estacionamiento","con");
        qDebug() << "c_freno_estacionamiento: con";
        m_cscp->setParkingBrake(true);
        emit CSCPChanged(m_cscp->evalCircuit());
        emit frenoEstacionamientoCon();
    }else{
        m_eventHandler->notifyValueChanged("c_freno_estacionamiento","des");
        qDebug() << "c_freno_estacionamiento: des";
        m_cscp->setParkingBrake(false);
        emit CSCPChanged(m_cscp->evalCircuit());
        emit frenoEstacionamientoDes();
    }
}

void SubteStatus::updateEffort(double value)
{
    m_effort = value;
    emit effortChanged(m_effort);
}

void SubteStatus::updateVolt(double value)
{
    m_volts = value;
    emit voltChanged(m_volts);
}

void SubteStatus::updateAmm(double value)
{
    m_amps = value;
    emit ampsChanged(m_amps);
}

void SubteStatus::bypassBrake(bool status)
{
    m_brake->setBypass(status);
    if(status){
        m_eventHandler->notifyValueChanged("c_bypass_freno","con");
        qDebug() << "Brake bypassed";
    } else {
        m_eventHandler->notifyValueChanged("c_bypass_freno","des");
        qDebug() << "Brake reactivated";
    }
    emit hiloLazoChanged(getHiloLazo());
    m_traction->notifyTraction();
    m_brake->notifyEmergencyBrake();
}

void SubteStatus::bypassCSCP(bool status)
{
    if(status){
        m_cscp->setBypass(true);
        m_eventHandler->notifyValueChanged("c_bypass_traccion","con");
        qDebug() << "CSCP bypassed";
    } else {
        if(m_speed <= 0) {
            m_cscp->setBypass(false);
            qDebug() << "CSCP re-actived";
        }
        m_eventHandler->notifyValueChanged("c_bypass_traccion","des");
    }
    m_traction->notifyTraction();
    emit CSCPChanged(m_cscp->evalCircuit());
    qDebug() << "CSCPChanged " + m_cscp->evalCircuit();
}

void SubteStatus::openLeftDoors()
{
    m_cscp->openLeftDoors();
    emit CSCPChanged(m_cscp->evalCircuit());
    qDebug() << "CSCPChanged " + m_cscp->evalCircuit();
}

void SubteStatus::openRightDoors()
{
    m_cscp->openRightDoors();
    emit CSCPChanged(m_cscp->evalCircuit());
    qDebug() << "CSCPChanged " + m_cscp->evalCircuit();
}

void SubteStatus::closeLeftDoors()
{
    m_cscp->closeLeftDoors();
    emit CSCPChanged(m_cscp->evalCircuit());
    qDebug() << "CSCPChanged " + m_cscp->evalCircuit();
}

void SubteStatus::closeRightDoors()
{
    m_cscp->closeRightDoors();
    emit CSCPChanged(m_cscp->evalCircuit());
    qDebug() << "CSCPChanged " + m_cscp->evalCircuit();
}

void SubteStatus::updateLeftDoorsButtons(bool state) {
    m_cscp->notifyActionLeftDoors(state);
}

void SubteStatus::updateRightDoorsButtons(bool state) {
    m_cscp->notifyActionRightDoors(state);
}

void SubteStatus::updatePreassureRed(double value)
{
    m_pressure_red = value;
    emit manometerRedChange(m_pressure_red);
}

void SubteStatus::updatePreassureWhite(double value)
{
    m_pressure_white = value;
    emit manometerWhiteChange(m_pressure_white);
}

double SubteStatus::getPressureRed() const
{
    return m_pressure_red;
}

double SubteStatus::getPressureWhite() const
{
    return m_pressure_white;
}

void SubteStatus::setDrivingModeATP(bool status){
    m_CMC = status;
}

bool SubteStatus::getDrivingModeATP(){
    return m_CMC;
}

void SubteStatus::setTractionFailure()
{
    m_traction->setAveria(true);
    m_traction->notifyTraction();
}

void SubteStatus::setBrakeFailure()
{
    m_brake->setAveria(true);
    m_brake->notifyEmergencyBrake();
    emit hiloLazoChanged(getHiloLazo());
}

void SubteStatus::setCSCPFailure()
{
    m_cscp->setAveria(true);
    emit CSCPChanged(m_cscp->evalCircuit());
}

void SubteStatus::resolveTractionFailure()
{
    m_traction->setAveria(false);
    m_traction->notifyTraction();
}

void SubteStatus::resolveBrakeFailure()
{
    m_brake->setAveria(false);
    m_brake->notifyEmergencyBrake();
    emit hiloLazoChanged(getHiloLazo());
}

void SubteStatus::resolveCSCPFailure()
{
    m_cscp->setAveria(false);
    emit CSCPChanged(m_cscp->evalCircuit());
}

void SubteStatus::setManiobraMode()
{
    m_eventHandler->notifyValueChanged("c_modo_conduccion","maniobra");
    emit estadoManioAcople();
}

void SubteStatus::setAtpMode()
{
    m_eventHandler->notifyValueChanged("c_modo_conduccion","atp");
    emit estadoNormal();

}

void SubteStatus::setAcopleMode()
{
    m_eventHandler->notifyValueChanged("c_modo_conduccion","acople");
    emit estadoManioAcople();

}

void SubteStatus::setRetentionBrakeBypass(bool state)
{
    m_brake->setAnulacionFrenoRetencion(state);

    if(state){
        m_eventHandler->notifyValueChanged("c_anulacion_freno_retencion","con");
    }else{
        m_eventHandler->notifyValueChanged("c_anulacion_freno_retencion","des");
    }
}

void SubteStatus::setRetentionBrake(bool state)
{
    m_brake->setRetentioBrake(state);
    qDebug() << "emitida la senial retencion: " << m_brake->retentioBrake();
    emit retentionBrakeChanged(m_brake->retentioBrake());
}


void SubteStatus::setSicasOk(){
    m_eventHandler->notifyValueChanged("c_estado_sicas","ok");
    qDebug() << "c_estado_sicas: ok";
}

void SubteStatus::setModeOperation(int m){
    m_modeOperation = m;
    emit modeOperation(m);
}
