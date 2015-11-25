#include "atp_controller.h"
#include <QtMath>
#include <QTimer>
#include <QElapsedTimer>

#include <math.h>
#include <stdio.h>

Atp_Controller::Atp_Controller(SubteStatus *subte, Atp *view, EventHandler *eventHandler)
{
    this->m_subte = subte;
    this->m_view = view;
    this->m_eventHandler = eventHandler;

    this->m_onATP = false;
    this->m_transition = false;

    this->onATP();

    //Conexiones del ATP.

        //Conexiones Externas-IN:
    connect(subte,SIGNAL(speedChanged(double)),this,SLOT(updateSpeed(double)));
    connect(subte,SIGNAL(targetSpeedChanged(double)),this,SLOT(updateTargetSpeed(double)));
    connect(subte,SIGNAL(atpOn()),this,SLOT(initATP()));
    connect(subte,SIGNAL(atpOff()),this,SLOT(resetATP()));


    connect(eventHandler,SIGNAL(accelerationInstant(double)),this,SLOT(setACE(double)));
    connect(eventHandler,SIGNAL(nextToEstation()),this,SLOT(nextToEstation()));
    connect(eventHandler,SIGNAL(departureEstation()),this,SLOT(departureEstation()));

        //Conexiones de control Internas
    connect(this,SIGNAL(allowedSpeedChange(double)),this,SLOT(superviseSpeed()));

        //Salidas Externas:
    connect(this, SIGNAL(cutTraction()),subte,SLOT(cutTraction()));
    connect(this, SIGNAL(enableTraction()),subte,SLOT(enableTraction()));
    connect(this, SIGNAL(enableBreakEmergency()),subte,SLOT(ATP_emergencyBrakeActivated()));
    connect(this, SIGNAL(desableBreakEmergency()),subte,SLOT(ATP_emergencyBrakeReleased()));
    connect(this, SIGNAL(enableBreakService(int)),subte,SLOT(brakeReceived(int)));
    connect(this, SIGNAL(desableBreakService(int)),subte,SLOT(brakeReceived(int)));
    connect(this, SIGNAL(allowedSpeedChange(double)),subte,SLOT(updateAllowedSpeed(double)));

}

/**************************************** Nuevo ATP ******************************************/
    //Acciones, rutinas a realizar en los estados:

void Atp_Controller::set_uTVC(){
/**
  * Va a ser 0 si no es CMC, caso contrario va a ser CTE porque si es CMC
  * y esta iniciando arranca con velocidad 0. O sea arrancaría con una transición peldaño.
  */
    if (!m_drivingModeCMC){
        m_uTVC = 0;
    }
    else{
        m_uTVC = 2;
    }
}

//Inicia la maquina de estados, o sea el ATP, deberia estar conectado a la senal salida de Plataforma.
void Atp_Controller::initATP(){
//VV
    //HH Deberian ir en setter´s y getter´s luego.
    //Tiempo T1 de la Transicion G Tiempo
    this->m_t_TGT = 3000;
    //VV aceleración instantánea, cambiar por la el modelo fisico cunado lo terminen.
    this->m_ACE = 0.5;
    //JF – Jerk de frenado: 0.89m/s3 (peor caso para 1 coche sin freno – vea [REF-9]).
    this->m_Jerk = 0.89;
    //Grade máximo de la vía (en módulo):
    this->m_Gm = 3.75;
    //TC – Tasa de la curva de reducción de código: 0,7m/s2.
    this->m_Tc = 0.7;
    //AF – Atraso de freno: 1.75s (incluye peor caso de reacción de freno del tren, en 1 coche
    //[REF-9]: 1.25s y tiempo de reacción del ATP: 0.50s).
    this->m_A_freno = 1.75;

    this->m_view->setReset(true);

    if(this->m_subte->getDrivingModeATP()){
        setDrivingMode(0);
    }else{
        setDrivingMode(1);
    }

    set_uTVC();

    m_speed = 0.0;
    m_speedAllowed = 0.0;
    m_speedCritique = 0.0;
    m_speedTargetPrevious = 0.0;
    m_speedTarget = 60.0;
    m_AF = "6";

    this->calculateDistance();

    m_onATP = true;
    if (m_transition){
        qDebug() << "ATP reinicializado cuando estaba en transicion, ---> TARGET SPEED: 0.0, ALLOWED SPEED: 15.0";
        updateTargetSpeed(15.0);
        m_subte->updateTargetSpeed(0.0);
        m_subte->updateAllowedSpeed(15.0);
        m_speedAllowed = 15.0;
        m_speedAllowedPrevious = 15.0;
        m_speedTarget = 0.0;
        m_speedTargetPrevious = 0.0;
        m_view->updateTargetSpeed(0.0);
        m_view->updateAllowedSpeed(15.0);
        m_transition = false;
    }else{
        qDebug() << "ATP reinicializado fuera de transicioncuando";
        if((this->m_subte->targetSpeed()) > 0.0){
            this->updateTargetSpeed(this->m_subte->targetSpeed());
            qDebug()<<"ATP init, TargetSpeed from MODEL: " << m_subte->targetSpeed();
        }else{
            this->updateTargetSpeed(60.0);
            qDebug()<<"ATP init, TargetSpeed from DEFAULT ATP: 60.0";
        }
    }


    //Intervalo de trabajo del ATP, salva en caso de quedar la velocidad planchada CTE y no recibir muestreo.
    //VV No estaria haciendo Falta no recuerdo bien porque pense esto, salio de la charla con Fabri, VER. (Luego de la limpieza de codigo quitar, parece que hace falta por una cuestionde refresco)
    this->m_machineATP->start();
    m_t_evalChangeSpeed->setInterval(500);
    m_t_evalChangeSpeed->start();

}

void Atp_Controller::resetATP(){

    this->m_onATP = false;
    this->off_ATP();
    this->m_view->setReset(true);
}

void Atp_Controller::setDrivingMode(int d){
 //VV Falta chequear off sets, y ver modo AL AT si van en true y se prende falla en ATP.
    switch(d){
    case 0:
        m_drivingModeCMC = true;
        this->m_view->setCMC(true);
        this->m_view->setCL(false);
        m_OS_ACT = 4.0;
        m_OS_LCT = 5.0;
        m_OS_AFS = 2.0;
        m_OS_LFS = 3.0;
        m_OS_AFE = 0.0;
        break;
    case 1:
        m_drivingModeCL = true;
        this->m_view->setCL(true);
        this->m_view->setCMC(false);
        m_OS_ACT = 2.0;
        m_OS_LCT = 3.0;
        m_OS_AFS = 1.0;
        m_OS_LFS = 2.0;
        m_OS_AFE = 0.0;
        break;
    case 2:
        m_drivingModeAL = true;
        this->m_view->setFalla(true);
        m_OS_ACT = 0.0;
        m_OS_LCT = 1.0;
        m_OS_AFS = -100.0;
        m_OS_LFS = -100.0;
        m_OS_AFE = -100.0;
        break;
     case 3:
        m_drivingModeAT = true;
        this->m_view->setFalla(true);
        m_OS_ACT = -100.0;
        m_OS_LCT = -100.0;
        m_OS_AFS = -100.0;
        m_OS_LFS = -100.0;
        m_OS_AFE = -100.0;
        break;
    }
}

void Atp_Controller::updateTargetSpeed(double speed){

    if (m_onATP){
        if (m_AF!="1"){
            this->m_view->updateTargetSpeed(speed);
            emit playSound(1);
            this->setSpeedTarget(speed);
            this->updateAllowedSpeed(speed);
        }else{
            this->setSpeedTarget(speed);
        }

    }
}

void Atp_Controller::nextToEstation(){

//Esto es un Parche debido al modelo!! ojo ver. Es porque no manda señales manda velocidades que no son unicas.
    if (m_onATP && (m_AF != "1")){

        this->m_view->updateTargetSpeed(0.0);
        this->m_view->setBlinkSpeedTarget(true);
        m_AF_previous = m_AF;
        m_AF = "1";
        m_speedTargetPrevious = m_speedTarget;
        m_speedTarget = 15.0;
        this->updateAllowedSpeed(m_speedTargetPrevious);

    }

}

void Atp_Controller::departureEstation(){
    //VV
    if (m_onATP && (m_AF == "1")){

        this->m_view->setBlinkSpeedTarget(false);
        qDebug()<<"departure Estation: m_speedTargetPrevious"<< m_speedTargetPrevious;
        m_AF = "6";
        updateTargetSpeed(m_speedTargetPrevious);
        critiqueSpeed(2);
    }

}

void Atp_Controller::updateSpeed(double speed){
    //Tiene dos conecciones por lo menos
    //Controla velocidad con permitida y acciona
        //Si todo bien update en vista real speed
        //en else voy a emitir una senal privada cuando no verifique ahi engancho
   if (m_onATP){
       this->m_view->updateSpeed(speed);
       this->m_speed = speed;
       superviseSpeed();
   }
}

void Atp_Controller::setAllowedSpeed(double s){

        m_speedAllowedPrevious = m_speedAllowed;
        m_speedAllowed = s;
        m_view->updateAllowedSpeed(s);
        emit allowedSpeedChange(s);

}

void Atp_Controller::setSpeedTarget(double speed){
//Parche. Es porque no manda señales manda velocidades que no son unicas.
    if (m_AF == "1"){
        m_speedTargetPrevious = speed;
    }else{
        int s = static_cast<int>(speed);
        switch(s){
            case 0:
                m_AF_previous = m_AF;
                m_AF = "0";
            break;
            case 15:
                m_AF_previous = m_AF;
                m_AF = "2";
            break;
            case 25:
                m_AF_previous = m_AF;
                m_AF = "3";
            break;
            case 30:
                m_AF_previous = m_AF;
                m_AF = "4";
            break;
            case 40:
                m_AF_previous = m_AF;
                m_AF = "5";
            break;
            case 50:
                m_AF_previous = m_AF;
                m_AF = "6";
            break;
            case 60:
                m_AF_previous = m_AF;
                m_AF = "7";
            break;
        }
        m_speedTargetPrevious = m_speedTarget;
        m_speedTarget = speed;
    }

}

void Atp_Controller::critiqueSpeed(int op){

    m_uTVC = op;

    if (!m_uTVC){
        m_speedCritique = 0;
    }else if ( m_uTVC == 1 ){
        //Curva
        m_speedCritique = 3.6*((m_ACE + m_Tc)*m_A_freno + pow( (fmin(m_ACE,-0.098*m_Gm)+m_Tc),2 )/(2*m_Jerk) );
    }else{
        //CTE
        m_speedCritique = 3.6*(m_ACE*m_A_freno + pow( (fmin(m_ACE,-0.098*m_Gm)),2 )/(2*m_Jerk));
    }
}

/**
 * @brief Atp_Controller::updateAllowedSpeed
 * Siempre que exista una variación en la Velocidad Objetivo, la Velocidad Permitida
 * podrá sufrir variación.
 * A continuación se describen las diversas transiciones posibles, siendo que el orden sigue la
 * prioridad decreciente. De esta manera, solamente si la primera transición no es identificada es
 * que las transiciones subsiguientes podrán ocurrir.
 * @param speedTargetNew
 */
void Atp_Controller::updateAllowedSpeed(double speedTargetNew){

    critiqueSpeed(2);

    if ( (m_speed <= 0.00)||(m_speedTargetPrevious < m_speedTarget)||((m_speedTargetPrevious >= m_speedTarget)&&(m_speed <= (m_speedTarget - 5.00))&&(m_AF != "1"))||
             (m_AF == "0" && m_AF_previous == "1")||(m_AF == "0" && m_AF_previous == "2")){
            //Transicion Peldano
            setAllowedSpeed(speedTargetNew);
        }else if ((m_speedTarget < m_speedTargetPrevious)&&(m_AF != "1")){
            //Transicion Gradual por Tiempo (3 seg; 0,7 m/s2)
            //Conectar con transitionGT() agregar setter para variable con los 3000
            QTimer::singleShot(m_t_TGT,this,SLOT(transitionGT()));
        }else if ((m_speedTarget < m_speedTargetPrevious)&&(/*m_speedTarget == m_AF_1*/m_AF == "1")){
            //Transicion Gradual por distancia
            transitionGD();
        }
}

void Atp_Controller::transitionGT(){
    // V = Vo + At
    m_transition = true;
    double t = ((m_speedTarget - m_speedTargetPrevious)*0.277777777777778)/(-0.7);
    int tAux = static_cast<int>(t*1000);

    QTime lapTime = QTime::currentTime();
    QTime ts = QTime::currentTime().addMSecs(tAux);

    double vAllowed;
    vAllowed = m_speedTargetPrevious;
    setAllowedSpeed(vAllowed);

    if (m_drivingModeCMC) critiqueSpeed(1);

    //WHILE timeLAP ...
    int lap = 0;
    lapTime.start();
    while ((lapTime.currentTime() < ts) && (m_speedAllowed > m_speedTarget)){
        lap = lapTime.elapsed();
        if (lap % 2 == 0){
            //update allowedSpeed hacer calculo en funcion del tiempo transcurrido
            vAllowed = m_speedTargetPrevious + ((-0.7)*(static_cast<double>(lapTime.elapsed())/static_cast<double>(1000)))*3.6;
            setAllowedSpeed(((vAllowed>m_speedTarget)?vAllowed:m_speedTarget));
        }
        QCoreApplication::processEvents(QEventLoop::AllEvents);

    }
    critiqueSpeed(2);
    setAllowedSpeed(m_speedTarget);
    m_transition = false;
}

/**
 * @brief Atp_Controller::transitionGD
 * a: 0.6 Aref, aceleracion de referencia de la curva de plataforma.
 * dp: distancia estandar de plataforma: 403.
 * tbp: tiempo de atraso de B-point de reduccion de codigo: 1.6.
 * d_ini: valor inicial.
 * V = 3.6*RAIZ(2*Aref*D)
 */
void Atp_Controller::transitionGD(){

    m_transition = true;

    double a = 0.6;
    double dp = 403.0;
    double tbp = 1.6;
    double d_ini = 0;
    int v_aux;

    d_ini = dp - m_speed*0.277777777777778*tbp;
    v_aux = static_cast<int>(3.6*qSqrt(2*a*d_ini));
    if (v_aux<m_speedAllowed){
        setAllowedSpeed(v_aux);
    }
    else{
        setAllowedSpeed(m_speedAllowed);
    }

    if (m_drivingModeCMC) critiqueSpeed(0);

    QElapsedTimer timer;
    timer.start();

    double calc;
    double sp;
    double d_aux = d_ini;
    double calc_Ant = 0;

    while ((d_aux >= 0) && (m_speedAllowed > m_speedTarget)){
        calc = (static_cast<double>(timer.elapsed())/static_cast<double>(1000));
        sp = (m_speed*0.277777777777778);
        if (calc_Ant > 0)
            d_aux = d_aux - sp*(calc-calc_Ant);
        calc_Ant = calc;
        QCoreApplication::processEvents(QEventLoop::AllEvents);

        if (d_aux>=0){
            v_aux = static_cast<int>(3.6*qSqrt(2*a*d_aux));
        }
        if (v_aux <= m_speedTargetPrevious){
            setAllowedSpeed(((v_aux>15.0)?v_aux:15.0));
        }
    }
    setAllowedSpeed(15.0);
    m_view->updateTargetSpeed(0.0);

    m_transition = false;
}

void Atp_Controller::calculateDistance(){
    int d = 403;
    int v = 0;
    double a = 0.6;
    this->m_speedAD = new QHash<int, int>;

    while (d >= 0 ){
        v = static_cast<int>(3.6*qSqrt(2*a*d));
        m_speedAD->insert(d,v);
        d--;
    }

}


/**
  * Supervision de la velocidad
  * Senales activadoras
  *  void _1AtoB();
  *  void _2BtoA();
  *  void _3BtoC();
  *  void _4CtoB();
  *  void _5CtoD();
  *  void _6DtoC();
  *   Rutinas
  *  void routingA();
  *  void routingB();
  *  void routingC();
  *  void routingD();
  */
void Atp_Controller::superviseSpeed(){

    if (m_speed == 0.0){
        emit _1AtoB();
    }
    if ((m_speed + m_OS_AFE > m_speedAllowed) || ((m_speed + m_OS_AFE + m_speedCritique > m_speedAllowed) && (m_uTVC!=0)) ){
        emit _2BtoA();
    }
    if ( ((m_speed + m_OS_LFS <= m_speedAllowed)&& (m_uTVC==0)) || (m_speed + m_OS_LFS + m_speedCritique <= m_speedAllowed) ){
        emit _3BtoC();
    }
    if ( ( m_speed + m_OS_AFS > m_speedAllowed ) || ((m_uTVC!=0) && ((m_speed + m_OS_AFS + m_speedCritique) > m_speedAllowed)) ){
        emit _4CtoB();
    }
    if ( (m_speed + m_OS_LCT <= m_speedAllowed && (m_uTVC==0)) || (m_speed + m_OS_LCT + m_speedCritique <= m_speedAllowed) ){
        emit _5CtoD();
    }
    if ( (m_speed + m_OS_ACT > m_speedAllowed) || ((m_uTVC!=0) && (m_speed + m_OS_ACT + m_speedCritique > m_speedAllowed)) ){
        emit _6DtoC();
    }

}

void Atp_Controller::onATP(){

    //Maquina de Estado ATP, solo version CMC
    this->m_machineATP = new QStateMachine();

    //Estados
    this->m_e_A = new QState();
    this->m_e_B = new QState();
    this->m_e_C = new QState();
    this->m_e_D = new QState();

    //Agrego los estados
    this->m_machineATP->addState(this->m_e_A);
    this->m_machineATP->addState(this->m_e_B);
    this->m_machineATP->addState(this->m_e_C);
    this->m_machineATP->addState(this->m_e_D);

    //Estado Final
    this->m_e_Final_State = new QFinalState();

    //Seteamos estado inicial
    this->m_machineATP->setInitialState(this->m_e_A);

    //Transiciones
    //A --to--> B
    m_e_A->addTransition(this,SIGNAL(_1AtoB()),m_e_B);
    //B --to--> A Back
    m_e_B->addTransition(this,SIGNAL(_2BtoA()),m_e_A);
    //B --to--> C
    m_e_B->addTransition(this,SIGNAL(_3BtoC()),m_e_C);
    //C <--to--B Back
    m_e_C->addTransition(this,SIGNAL(_4CtoB()),m_e_B);
    //C --to--> D
    m_e_C->addTransition(this,SIGNAL(_5CtoD()),m_e_D);
    //D --to--> C Back
    m_e_D->addTransition(this,SIGNAL(_6DtoC()),m_e_C);

    //Transicion Final
    m_e_A->addTransition(this,SIGNAL(offATP()),m_e_Final_State);
    m_e_B->addTransition(this,SIGNAL(offATP()),m_e_Final_State);
    m_e_C->addTransition(this,SIGNAL(offATP()),m_e_Final_State);
    m_e_D->addTransition(this,SIGNAL(offATP()),m_e_Final_State);

    //Acciones:
    connect(m_e_A,SIGNAL(entered()),this,SLOT(routingA()));
    connect(m_e_B,SIGNAL(entered()),this,SLOT(routingB()));
    connect(m_e_C,SIGNAL(entered()),this,SLOT(routingC()));
    connect(m_e_D,SIGNAL(entered()),this,SLOT(routingD()));

    //Timer
    m_t_evalChangeSpeed = new QTimer();
    connect(m_t_evalChangeSpeed, SIGNAL(timeout()),this,SLOT(superviseSpeed()));
}

void Atp_Controller::off_ATP(){

    this->m_machineATP->stop();

    this->m_view->setCMC(false);
    this->m_view->setCL(false);
    this->m_view->setFalla(false);
    this->m_view->setCorte(false);
    this->m_view->setCorteBlink(false);
    this->m_view->setFrenoUrg(false);
    this->m_view->setFrenoUrgBlink(false);
}

void Atp_Controller::setACE(double a){
    this->m_ACE = a;
}

void Atp_Controller::routingA(){

    emit playSound(0);
    this->m_view->setFrenoUrg(true);
    this->m_view->setFserv(true);
    this->m_view->setCorte(true);
    emit cutTraction();
    emit enableBreakService(50);
    emit enableBreakEmergency();
}

void Atp_Controller::routingB(){

    emit playSound(0);
    this->m_view->setFrenoUrg(false);
    this->m_view->setFserv(true);
    this->m_view->setCorte(true);
    emit cutTraction();
    emit desableBreakEmergency();
    emit enableBreakService(0);
}

void Atp_Controller::routingC(){

    emit playSound(0);
    this->m_view->setFrenoUrg(false);
    this->m_view->setFserv(false);
    this->m_view->setCorte(true);
    emit cutTraction();
}

void Atp_Controller::routingD(){

    this->m_view->setFrenoUrg(false);
    this->m_view->setFserv(false);
    this->m_view->setCorte(false);
    emit enableTraction();
}

Atp_Controller::~Atp_Controller(){

}

void Atp_Controller::setSignalTarget(QString s){

    int v = s.toInt();
    switch(v){
        case 0:
            m_speedTarget = 0;
        break;
        case 10:
            m_speedTarget = 10;
        break;
        case 15:
            m_speedTarget = 15;
        break;
        case 20:
            m_speedTarget = 20;
        break;
        case 25:
            m_speedTarget = 25;
        break;
        case 30:
            m_speedTarget = 30;
        break;
        case 40:
            m_speedTarget = 40;
        break;
        case 50:
            m_speedTarget = 50;
        break;
        case 60:
            m_speedTarget = 60;
        break;
        default:
            m_speedTarget = 60;
        break;
    }

}
/**
 *
 */
