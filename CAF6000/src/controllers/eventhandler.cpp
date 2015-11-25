#include "eventhandler.h"

EventHandler::EventHandler(QDesktopWidget *desktop)
{
    F1_down = false;
    F2_down = false;
    F3_down = false;
    F4_down = false;
    F5_down = false;

    A_down = false;
    B_down = false;
    C_down = false;
    F_down = false;
    H_down = false;
    J_down = false;
    K_down = false;
    L_down = false;
    R_down = false;
    T_down = false;

    CERO_down = false;
    UNO_down = false;
    DOS_down = false;
    TRES_down = false;
    CUATRO_down = false;
    CINCO_down = false;
    SEIS_down = false;
    SIETE_down = false;
    OCHO_down = false;
    NUEVE_down = false;

    MAS_down = false;
    MENOS_down = false;

    m_eNetClient = new ENetClient();
    m_eNetHelper = new ENetHelper(m_eNetClient);

    KeyPressEater *kel = KeyPressEater::instance();
    kel->setConnected(TRUE);
    connect(kel,SIGNAL(keyPressed(DWORD)),this,SLOT(processKeyPressed(DWORD)));
    connect(kel,SIGNAL(keyReleased(DWORD)),this,SLOT(processKeyReleased(DWORD)));

////    m_imageSplash = QPixmap(":/resources/splash.jpg");
//    if(m_desktop->screenCount() == 4){
//        m_splash1 = new QSplashScreen(m_imageSplash);
//        m_splash1->setWindowFlags(Qt::WindowStaysOnTopHint);
//        m_splash2 = new QSplashScreen(m_imageSplash);
//        m_splash2->setWindowFlags(Qt::WindowStaysOnTopHint);
//        m_splash3 = new QSplashScreen(m_imageSplash);
//        m_splash3->setWindowFlags(Qt::WindowStaysOnTopHint);
//        m_splash4 = new QSplashScreen(m_imageSplash);
//        m_splash4->setWindowFlags(Qt::WindowStaysOnTopHint);

//        QRect s0 = m_desktop->screenGeometry(0);
//        QRect s1 = m_desktop->screenGeometry(1);
//        QRect s2 = m_desktop->screenGeometry(2);
//        QRect s3 = m_desktop->screenGeometry(3);

//        m_splash1->move(s0.topLeft());
//        m_splash2->move(s1.topLeft());
//        m_splash3->move(s2.topLeft());
//        m_splash4->move(s3.topLeft());
//    }else{
////        m_splash1 = new QSplashScreen(m_imageSplash);
////        m_splash1->setWindowFlags(Qt::WindowStaysOnTopHint);
//    }

//    subirSplash();
}

EventHandler::~EventHandler(){
}

void EventHandler::initConnection()
{
    m_eNetHelper->initENet(m_eNetClient, this);
}

void EventHandler::setModel(SubteStatus *subte)
{
    m_subte = subte;
}

void EventHandler::setFailures(Failures_Controller *failures)
{
    m_failures = failures;
}

void EventHandler::notifyValueChanged(std::string key, std::string value)
{
    m_eNetClient->CambiarValorClave(key,value);
}

void EventHandler::processValueChanged(std::string host, std::string key, std::string value){
    qDebug() << "value - key:: host:" << host.c_str() << " key:"<< key.c_str() << " value:" << value.c_str() << "time: " << QTime::currentTime().toString() ;

    if(key.compare("i_iniciar_simulador") == 0){
        if (value.compare("con") == 0){
            qDebug() << "i_iniciar_simulador con recibido" ;
            m_eNetClient->CambiarValorClave("c_listo","0");

            emit controlReady();

            m_eNetClient->Suscribirse(m_eNetHelper->instructionsHostName,"i_estado_simulador");
            m_eNetClient->Suscribirse(m_eNetHelper->instructionsHostName,"i_cargar_estado");
            m_eNetClient->Suscribirse(m_eNetHelper->instructionsHostName,"i_averia");

            m_eNetClient->Suscribirse(m_eNetHelper->instructionsHostName,"i_coches_sicas");
            m_eNetClient->Suscribirse(m_eNetHelper->instructionsHostName,"i_renglon_sicas");
            m_eNetClient->Suscribirse(m_eNetHelper->instructionsHostName,"i_estacion_destino_sicas");
            m_eNetClient->Suscribirse(m_eNetHelper->instructionsHostName,"i_salir_de_estacion");
            m_eNetClient->Suscribirse(m_eNetHelper->visualHostName,"v_freno_retencion");
            m_eNetClient->Suscribirse(m_eNetHelper->visualHostName,"v_velocidad");
            m_eNetClient->Suscribirse(m_eNetHelper->visualHostName,"v_tramo_vel");
            m_eNetClient->Suscribirse(m_eNetHelper->visualHostName,"v_esfuerzo");
            m_eNetClient->Suscribirse(m_eNetHelper->visualHostName,"v_intensidad");
            m_eNetClient->Suscribirse(m_eNetHelper->visualHostName,"v_voltaje");
            m_eNetClient->Suscribirse(m_eNetHelper->visualHostName,"v_llego_senial");
            m_eNetClient->Suscribirse(m_eNetHelper->visualHostName,"v_presion_cilindro");
            m_eNetClient->Suscribirse(m_eNetHelper->visualHostName,"v_presion_alimentacion");
            m_eNetClient->Suscribirse(m_eNetHelper->visualHostName,"v_proximo_a_estacion");
            m_eNetClient->Suscribirse(m_eNetHelper->visualHostName,"v_estado_puertas");
            m_subte->reset();
            emit controlReset();

            m_eNetClient->CambiarValorClave("c_grifob138","con");
            m_eNetClient->CambiarValorClave("c_grifol2","con");
            m_eNetClient->CambiarValorClave("c_grifob73","con");
            m_eNetClient->CambiarValorClave("c_termico_57f1","con");
            m_eNetClient->CambiarValorClave("c_termico_53f1","con");
            m_eNetClient->CambiarValorClave("c_termico_33f1","con");
            m_eNetClient->CambiarValorClave("c_grifob138_2","con");
            m_eNetClient->CambiarValorClave("c_grifol2_2","con");
            m_eNetClient->CambiarValorClave("c_grifob73_2","con");
            m_eNetClient->CambiarValorClave("c_termico_57f1_2","con");
            m_eNetClient->CambiarValorClave("c_termico_53f1_2","con");
            m_eNetClient->CambiarValorClave("c_termico_33f1_2","con");
            m_eNetClient->CambiarValorClave("c_rana_2","0");
            m_eNetClient->CambiarValorClave("c_seta_emergencia_2","des");
            m_eNetClient->CambiarValorClave("c_grifob138_3","con");
            m_eNetClient->CambiarValorClave("c_grifol2_3","con");
            m_eNetClient->CambiarValorClave("c_grifob73_3","con");
            m_eNetClient->CambiarValorClave("c_termico_57f1_3","con");
            m_eNetClient->CambiarValorClave("c_termico_53f1_3","con");
            m_eNetClient->CambiarValorClave("c_termico_33f1_3","con");
            m_eNetClient->CambiarValorClave("c_rana_3","0");
            m_eNetClient->CambiarValorClave("c_seta_emergencia_3","des");
            m_eNetClient->CambiarValorClave("c_grifob138_4","con");
            m_eNetClient->CambiarValorClave("c_grifol2_4","con");
            m_eNetClient->CambiarValorClave("c_grifob73_4","con");
            m_eNetClient->CambiarValorClave("c_termico_57f1_4","con");
            m_eNetClient->CambiarValorClave("c_termico_53f1_4","con");
            m_eNetClient->CambiarValorClave("c_termico_33f1_4","con");
            m_eNetClient->CambiarValorClave("c_rana_4","0");
            m_eNetClient->CambiarValorClave("c_seta_emergencia_4","des");
            m_eNetClient->CambiarValorClave("c_grifob138_5","con");
            m_eNetClient->CambiarValorClave("c_grifol2_5","con");
            m_eNetClient->CambiarValorClave("c_grifob73_5","con");
            m_eNetClient->CambiarValorClave("c_termico_57f1_5","con");
            m_eNetClient->CambiarValorClave("c_termico_53f1_5","con");
            m_eNetClient->CambiarValorClave("c_termico_33f1_5","con");
            m_eNetClient->CambiarValorClave("c_rana_5","0");
            m_eNetClient->CambiarValorClave("c_seta_emergencia_5","des");
            m_eNetClient->CambiarValorClave("c_grifob138_6","con");
            m_eNetClient->CambiarValorClave("c_grifol2_6","con");
            m_eNetClient->CambiarValorClave("c_grifob73_6","con");
            m_eNetClient->CambiarValorClave("c_termico_57f1_6","con");
            m_eNetClient->CambiarValorClave("c_termico_53f1_6","con");
            m_eNetClient->CambiarValorClave("c_termico_33f1_6","con");
            m_eNetClient->CambiarValorClave("c_rana_6","0");
            m_eNetClient->CambiarValorClave("c_seta_emergencia_6","des");

            emit controlDisable();
            m_eNetClient->CambiarValorClave("c_listo","1");

        }else if (value.compare("des") == 0){
            m_eNetClient->CambiarValorClave("c_listo","0");
            m_eNetClient->CambiarValorClave("c_regulador_mando","");
            m_eNetClient->CambiarValorClave("c_llave_atp","");
            m_eNetClient->CambiarValorClave("c_modo_conduccion","");

            m_eNetClient->CambiarValorClave("c_grifob138","con");
            m_eNetClient->CambiarValorClave("c_grifol2","con");
            m_eNetClient->CambiarValorClave("c_grifob73","con");
            m_eNetClient->CambiarValorClave("c_termico_57f1","con");
            m_eNetClient->CambiarValorClave("c_termico_53f1","con");
            m_eNetClient->CambiarValorClave("c_termico_33f1","con");
            m_eNetClient->CambiarValorClave("c_grifob138_2","con");
            m_eNetClient->CambiarValorClave("c_grifol2_2","con");
            m_eNetClient->CambiarValorClave("c_grifob73_2","con");
            m_eNetClient->CambiarValorClave("c_termico_57f1_2","con");
            m_eNetClient->CambiarValorClave("c_termico_53f1_2","con");
            m_eNetClient->CambiarValorClave("c_termico_33f1_2","con");
            m_eNetClient->CambiarValorClave("c_rana_2","0");
            m_eNetClient->CambiarValorClave("c_seta_emergencia_2","des");
            m_eNetClient->CambiarValorClave("c_grifob138_3","con");
            m_eNetClient->CambiarValorClave("c_grifol2_3","con");
            m_eNetClient->CambiarValorClave("c_grifob73_3","con");
            m_eNetClient->CambiarValorClave("c_termico_57f1_3","con");
            m_eNetClient->CambiarValorClave("c_termico_53f1_3","con");
            m_eNetClient->CambiarValorClave("c_termico_33f1_3","con");
            m_eNetClient->CambiarValorClave("c_rana_3","0");
            m_eNetClient->CambiarValorClave("c_seta_emergencia_3","des");
            m_eNetClient->CambiarValorClave("c_grifob138_4","con");
            m_eNetClient->CambiarValorClave("c_grifol2_4","con");
            m_eNetClient->CambiarValorClave("c_grifob73_4","con");
            m_eNetClient->CambiarValorClave("c_termico_57f1_4","con");
            m_eNetClient->CambiarValorClave("c_termico_53f1_4","con");
            m_eNetClient->CambiarValorClave("c_termico_33f1_4","con");
            m_eNetClient->CambiarValorClave("c_rana_4","0");
            m_eNetClient->CambiarValorClave("c_seta_emergencia_4","des");
            m_eNetClient->CambiarValorClave("c_grifob138_5","con");
            m_eNetClient->CambiarValorClave("c_grifol2_5","con");
            m_eNetClient->CambiarValorClave("c_grifob73_5","con");
            m_eNetClient->CambiarValorClave("c_termico_57f1_5","con");
            m_eNetClient->CambiarValorClave("c_termico_53f1_5","con");
            m_eNetClient->CambiarValorClave("c_termico_33f1_5","con");
            m_eNetClient->CambiarValorClave("c_rana_5","0");
            m_eNetClient->CambiarValorClave("c_seta_emergencia_5","des");
            m_eNetClient->CambiarValorClave("c_grifob138_6","con");
            m_eNetClient->CambiarValorClave("c_grifol2_6","con");
            m_eNetClient->CambiarValorClave("c_grifob73_6","con");
            m_eNetClient->CambiarValorClave("c_termico_57f1_6","con");
            m_eNetClient->CambiarValorClave("c_termico_53f1_6","con");
            m_eNetClient->CambiarValorClave("c_termico_33f1_6","con");
            m_eNetClient->CambiarValorClave("c_rana_6","0");
            m_eNetClient->CambiarValorClave("c_seta_emergencia_6","des");

            //m_eNetClient->Desconectar();

            Sleep(1000);
            emit closeApp();
        }
    }

    else if(key.compare("i_estado_simulador") == 0){
        if (value.compare("0") == 0){

            qDebug() << "i_estado_simulador 0 recibido" ;
            m_eNetClient->CambiarValorClave("c_listo","0");
            subirSplash();

            m_subte->reset();
            emit controlReset();
            //emit controlReady();
            emit controlDisable();
            m_eNetClient->CambiarValorClave("c_listo","1");
        }

        else if(value.compare("1") == 0){
            bajarSplash();
            emit controlEnable();
        }

        else if(value.compare("2") == 0){
            //TODO: GRISAR o MOSTRAR UN LABEL DE PAUSA
            emit controlDisable();
        }
    }

    else if(key.compare("v_llego_senial") == 0){
        qDebug() << "cambio de llego senial." ;

        if(value.compare("none") != 0){

            QString message = value.c_str();
            QStringList parameters = message.split(";");

            std::string state = parameters.at(1).toStdString();

            if (state.compare("0")==0){
                //TODO: llamar al ATP para que cambie target a 0 - eso fuerza modo CL
                m_subte->ATP_emergencyBrakeActivated();
            }
        }
    }

    else if(key.compare("v_velocidad") == 0){
        m_subte->updateSpeed(std::stod(value));
    }

    else if(key.compare("v_tramo_vel") == 0){
        m_subte->updateTargetSpeed(std::stod(value));
    }

    else if(key.compare("i_cargar_estado") == 0){

        m_eNetClient->CambiarEstadoDifusion(false);

        QCoreApplication::processEvents(QEventLoop::AllEvents);
        m_boardsReady = 0;

        int intState = -1; //default - ningun estado
        if (value.compare("apagado") == 0){
            m_cargandoEstado = "apagado";
            intState = 0;
        } else if(value.compare("puesta_servicio") == 0){
            m_cargandoEstado = "puesta_servicio";
            intState = 1;
        }
        emit cargarEstado(intState);
    }

    else if(key.compare("v_voltaje") == 0){
        m_subte->updateVolt(std::stod(value));
    }

    else if(key.compare("v_intensidad") == 0){
        m_subte->updateAmm(std::stod(value));
    }

    else if(key.compare("v_esfuerzo") == 0){
        m_subte->updateEffort(std::stod(value));
    }

    else if(key.compare("v_presion_cilindro") == 0){
        try{
            m_subte->updatePreassureRed(std::stod(value));
        }
        catch (...) {
            qDebug() << "Presion de cilindro incorrecta." ;
        }
    }

    else if(key.compare("v_presion_alimentacion") == 0){
        try{
            m_subte->updatePreassureWhite(std::stod(value));
        }
        catch(...){
            qDebug() << "presion de frenado incorrecta." ;
        }
    }

    else if (key.compare("a_ACE") == 0){
        emit accelerationInstant(std::stod(value));
    }

    else if (key.compare("v_proximo_a_estacion") == 0){
        if (value.compare("1") == 0){
            qDebug() << " v_proximo_a_estacion, --> 1";
            emit nextToEstation();
        }
    }

    else if(key.compare("v_estado_puertas") == 0){
        qDebug() << "cambio de estado de puertas";

        QString message = value.c_str();
        QStringList parameters = message.split(";");
        std::string side = parameters.at(0).toStdString();
        std::string state = parameters.at(1).toStdString();

        if(side.compare("derecha") == 0){
            if(state.compare("abierto") == 0){
                m_subte->openRightDoors();
                qDebug() << "puertas derechas abiertas";
            }
            else if(state.compare("cerrado") == 0){
                m_subte->closeRightDoors();
                qDebug() << "puertas derechas cerradas";
            }
        } else {
            if(state.compare("abierto") == 0){
                m_subte->openLeftDoors();
                qDebug() << "puertas izquierdas abiertas";
            }
            else if(state.compare("cerrado") == 0){
                m_subte->closeLeftDoors();
                qDebug() << "puertas izquierdas cerrado";
            }
        }
    }

    else if(key.compare("v_freno_retencion") == 0){
        qDebug() << "cambio estado freno retencion." ;
        if (value.compare("des") == 0)
            m_subte->setRetentionBrake(false);
        else
            m_subte->setRetentionBrake(true);
    }

    else if(key.compare("i_averia") == 0){
        qDebug() << "i_averia recibido." ;
        m_failures->setFailure(value);
    }

    else if(key.compare("i_renglon_sicas") == 0){
        qDebug() << "renglon sicas recibido." ;
        QString mensaje = value.c_str();
        emit cargarMensaje(mensaje);
    }

    else if(key.compare("i_coches_sicas") == 0){
        qDebug() << "fallas y puertas recibidas." ;
        QString mensaje = value.c_str();
        emit cargarMensajeCocheSicas(mensaje);
    }
    else if(key.compare("i_estacion_destino_sicas") == 0){
        qDebug() << "cargo destino sicas." ;
        QString mensaje = value.c_str();
        emit cargarDestinoSicas(mensaje);
    }
    else if(key.compare("i_salir_de_estacion") == 0){
        if (value.compare("1") == 0){
            qDebug() << "i_salir_de_estacion: --> 1";
            emit departureEstation();
        }
    }
}

void EventHandler::processKeyPressed(DWORD k)
{
    if ( k == _F1 && !F1_down) {
        F1_down = true;
        qDebug() << "F1 key pressed";
        this->processValueChanged(m_eNetHelper->instructionsHostName, "i_iniciar_simulador", "con");
    } else if ( k == _F2 && !F2_down) {
        F2_down = true;
        qDebug() << "F2 key pressed";
        this->processValueChanged(m_eNetHelper->instructionsHostName, "i_iniciar_simulador", "des");
    } else if ( k == _F3 && !F3_down) {
        F3_down = true;
        qDebug() << "F3 key pressed";
        this->processValueChanged(m_eNetHelper->instructionsHostName, "i_estado_simulador", "0");
    } else if ( k == _F4 && !F4_down) {
        F4_down = true;
        qDebug() << "F4 key pressed";
        this->processValueChanged(m_eNetHelper->instructionsHostName, "i_estado_simulador", "1");
    } else if ( k == _F5 && !F5_down  ){
        F5_down = true;
        qDebug() << "F5 key pressed";
    }  else if ( k == _K && !K_down ){
        K_down = true;
        qDebug() << "K key pressed";
        emit kPressed();
    } else if ( k == _L && !L_down ){
        L_down = true;
        qDebug() << "L key pressed";
        emit lPressed();
    } else if ( k == _A && !A_down ){
        A_down = true;
        emit aPressed();
        qDebug() << "A key pressed";
    } else if ( k == _R  && !R_down ){
        R_down = true;
        emit rPressed();
        qDebug() << "R key pressed";
    } else if ( k == _tF && !F_down ){
        F_down = true;
        qDebug() << "F key pressed";
        emit fPressed();
    } else if ( k == _T && !T_down ){
        T_down = true;
        qDebug() << "T key pressed";
        emit tPressed();
    } else if ( k == _B && !B_down){
        B_down = true;
        qDebug() << "B key pressed";
        emit bPressed();
    } else if ( k == 0x43 && !C_down){
        C_down = true;
        qDebug() << "C key pressed";
        this->notifyValueChanged("c_freno_estacionamiento","con");
        emit cPressed();
    } else if ( k == _CERO && !CERO_down  ){
        CERO_down = true;
        emit ceroPressed();
        qDebug() << "0 key pressed";
    } else if ( k == _UNO && !UNO_down  ){
        UNO_down = true;
        this->notifyValueChanged("c_pulsador_bateria","con");
        qDebug() << "1 key pressed";
    } else if ( k == _DOS && !DOS_down  ){
        DOS_down = true;
        this->notifyValueChanged("c_conmutador_puesta_en_servicio","automatica");
        qDebug() << "2 key pressed";
    } else if ( k == _TRES && !TRES_down  ){
        TRES_down = true;
        qDebug() << "3 key pressed";
        this->notifyValueChanged("c_estado_sicas","ok");
    } else if ( k == _CUATRO && !CUATRO_down  ){
        CUATRO_down = true;
        this->notifyValueChanged("c_conmutador_puesta_en_servicio_automatica","con");
        qDebug() << "4 key pressed";
    } else if ( k == _CINCO && !CINCO_down  ){
        CINCO_down = true;
        this->notifyValueChanged("c_disyuntor","con");
        qDebug() << "5 key pressed";
    } else if ( k == _SEIS && !SEIS_down  ){
        SEIS_down = true;
        this->notifyValueChanged("c_freno_estacionamiento","des");
        emit frenoEstDes();
        qDebug() << "6 key pressed";
    } else if ( k == _SIETE && !SIETE_down  ){
        SIETE_down = true;
        this->processValueChanged(m_eNetHelper->instructionsHostName, "i_cargar_estado", "puesta_servicio");
        qDebug() << "7 key pressed";
    } else if ( k == _OCHO && !OCHO_down  ){
        OCHO_down = true;
        this->notifyValueChanged("c_conmutador_puesta_en_servicio_automatica","des");
        qDebug() << "8 key pressed";
    } else if ( k == _NUEVE && !NUEVE_down  ){
        NUEVE_down = true;
        this->notifyValueChanged("c_pulsador_bateria","des");
        qDebug() << "9 key pressed";
        qDebug() << "9 key pressed, New TARGET 30";
        emit newTarget(1);
    } else if ( k == _H && !H_down  ){
        H_down = true;
        qDebug() << "H key pressed, nextToEstation";
        this->processValueChanged(m_eNetHelper->instructionsHostName, "v_proximo_a_estacion", "1");
    } else if ( k == _J && !J_down  ){
        J_down = true;
        qDebug() << "J key pressed, departureFromEstation";
        this->processValueChanged(m_eNetHelper->instructionsHostName, "i_salir_de_estacion", "1");
    } else if ( k == _MAS && !MAS_down ){
        MAS_down = true;
        qDebug() << "MAS key pressed, ";
        emit masPressed();
    } else if ( k == _MENOS && !MENOS_down ){
        MENOS_down = true;
        qDebug() << "MENOS key pressed, ";
        emit menosPressed();
    }
}

void EventHandler::processKeyReleased(DWORD k){
    if ( k == _F1 ) {
        qDebug() << "F1 key released";
        F1_down = false;
    } else if ( k == _F2 ) {
        qDebug() << "F2 key released";
        F2_down = false;
    } else if ( k == _F3 ) {
        qDebug() << "F3 key released";
        F3_down = false;
    } else if ( k == _F4 ) {
        qDebug() << "F4 key released";
        F4_down = false;
    } else if ( k == _F5 ) {
        qDebug() << "F5 key released";
        F5_down = false;
    } else if ( k == _K ){
        qDebug() << "K key released";
        K_down = false;
    } else if ( k == _L ){
        qDebug() << "L key released";
        L_down = false;
    } else if ( k == _A ){
        qDebug() << "A key released";
        A_down = false;
    } else if ( k == _R ){
        qDebug() << "R key released";
        R_down = false;
    } else if ( k == _tF ){
        qDebug() << "F key released";
        F_down = false;
    } else if ( k == _T ){
        qDebug() << "T key released";
        T_down = false;
    } else if ( k == _B ){
        B_down = false;
        qDebug() << "B key released";
        emit bReleased();
    } else if ( k == _CERO ){
        qDebug() << "0 key released";
        CERO_down = false;
    } else if ( k == _UNO ){
        qDebug() << "1 key released";
        UNO_down = false;
    } else if ( k == _DOS ){
        qDebug() << "2 key released";
        DOS_down = false;
    } else if ( k == _TRES ){
        TRES_down = false;
        qDebug() << "3 key released";
    } else if ( k == _CUATRO ){
        CUATRO_down = false;
        qDebug() << "4 key released";
    } else if ( k == _CINCO ){
        CINCO_down = false;
        qDebug() << "5 key released";
    } else if ( k == _SEIS ){
        SEIS_down = false;
        qDebug() << "6 key released";
    } else if ( k == _SIETE ){
        SIETE_down = false;
        qDebug() << "7 key released";
    } else if ( k == _OCHO ){
        OCHO_down = false;
        qDebug() << "8 key released";
    } else if ( k == _NUEVE ){
        NUEVE_down = false;
        qDebug() << "9 key released";
    } else if ( k == _H ){
        H_down = false;
        qDebug() << "H key released";
    } else if ( k == _J ){
        J_down = false;
        qDebug() << "J key released";
    } else if ( k == _MAS ){
        MAS_down = false;
        qDebug() << "MAS key released";
        emit masReleased();
    } else if ( k == _MENOS ){
        MENOS_down = false;
        qDebug() << "MENOS key released";
        emit menosReleased();
    }
}

void EventHandler::enableDiffusion()
{
    m_boardsReady++;
    if(m_boardsReady==5){
        m_eNetClient->CambiarEstadoDifusion(true);
        m_boardsReady = 0;
        m_eNetClient->CambiarValorClave("c_estado_cargado",m_cargandoEstado);
        m_cargandoEstado = "";
    }
}

void EventHandler::bajarSplash(){
    if(m_splashOn){
        if(m_desktop->screenCount() == 4){
            m_splash1->hide();
            m_splash2->hide();
            m_splash3->hide();
            m_splash4->hide();
        }else{
            m_splash1->hide();
        }
        m_splashOn = false;
    }
}

void EventHandler::subirSplash(){
    if(!m_splashOn){
        if(m_desktop->screenCount() == 4){
            m_splash1->showFullScreen();
            m_splash2->showFullScreen();
            m_splash3->showFullScreen();
            m_splash4->showFullScreen();
            //para evitar el cierre con un CLICK
            m_splash1->setDisabled(true);
            m_splash2->setDisabled(true);
            m_splash3->setDisabled(true);
            m_splash4->setDisabled(true);
        }else{
            m_splash1->showMaximized();
            m_splash1->setDisabled(true);
        }
        m_splashOn = true;
    }
}
