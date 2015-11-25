#include "failures_controller.h"

Failures_Controller::Failures_Controller(SubteStatus *subte)
{
    m_subte = subte;
    m_brakeFailing = false;
    m_cscpFailing = false;
    m_tractionFailing = false;
}

Failures_Controller::~Failures_Controller()
{

}

void Failures_Controller::setFailure(std::string f)
{
    try{
        QString mensaje = QString(f.c_str());
        QStringList parametros = mensaje.split(";");
        QString failureCSCP = parametros.at(1);
        QString failureBrake = parametros.at(3);
        QString failureTraction = parametros.at(2);

        if(failureCSCP.compare("ok") == 0){
            if(m_cscpFailing){
                m_subte->resolveCSCPFailure();
                m_cscpFailing = false;
                qDebug() << "failureCSCP // ok //" ;
            }
        }else if(failureCSCP.compare("falla") == 0){
            if(!m_cscpFailing){
                m_subte->setCSCPFailure();
                m_cscpFailing = true;
                qDebug() << "failureCSCP XX averia XX" ;
            }
        }else{
            qDebug() << "ERROR EN EL PARSEO DEL VALOR DE FALLA DEL CSCP";
        }

        if(failureBrake.compare("ok") == 0){
            if(m_brakeFailing){
                m_subte->resolveBrakeFailure();
                m_brakeFailing = false;
                qDebug() << "failureBrake // ok //" ;
            }
        }else if(failureBrake.compare("falla") == 0){
            if(!m_brakeFailing){
                m_subte->setBrakeFailure();
                m_brakeFailing = true;
                qDebug() << "failureBrake XX averia XX" ;
            }
        }else{
            qDebug() << "ERROR EN EL PARSEO DEL VALOR DE FALLA DE FRENOS";
        }

        if(failureTraction.compare("ok") == 0){
            if(m_tractionFailing){
                m_subte->resolveTractionFailure();
                m_tractionFailing = false;
                qDebug() << "failureTraction // ok //" ;
            }
        }else if(failureTraction.compare("falla") == 0){
            if(!m_tractionFailing){
                m_subte->setTractionFailure();
                m_tractionFailing = true;
                qDebug() << "failureTraction XX averia XX" ;
            }
        }else{
            qDebug() << "ERROR EN EL PARSEO DEL VALOR DE FALLA DE TRACCION";
        }
    } catch (...) {
        qDebug() << "ERROR EN EL PARSEO DE FALLAS";
    }
}
