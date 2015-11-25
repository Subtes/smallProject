#include "llavemodoconduccion.h"
#include "ui_llavemodoconduccion.h"

LlaveModoConduccion::LlaveModoConduccion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LlaveModoConduccion)
{
    ui->setupUi(this);

    ui->llave3ptos->setClearColor(Qt::transparent);
    ui->llave3ptos->setAttribute(Qt::WA_AlwaysStackOnTop);

    m_qmlView = ui->llave3ptos->rootObject();

    connect (m_qmlView,SIGNAL(pos1()),this,SIGNAL(maniobraMode()));
    connect (m_qmlView,SIGNAL(pos2()),this,SIGNAL(atpMode()));
    connect (m_qmlView,SIGNAL(pos3()),this,SIGNAL(acopleMode()));
}

LlaveModoConduccion::~LlaveModoConduccion()
{
    delete ui;
}

void LlaveModoConduccion::setManiobraMode(){
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "setPos1",
            Q_RETURN_ARG(QVariant, returnedValue));
}

void LlaveModoConduccion::setAcopleMode(){
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "setPos3",
            Q_RETURN_ARG(QVariant, returnedValue));
}

void LlaveModoConduccion::setAtpMode(){
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "setPos2",
            Q_RETURN_ARG(QVariant, returnedValue));
}
