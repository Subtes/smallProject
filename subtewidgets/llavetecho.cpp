#include "llavetecho.h"
#include "ui_llavetecho.h"

LlaveTecho::LlaveTecho(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LlaveTecho)
{
    ui->setupUi(this);

    m_qml = ui->quickWidget->rootObject();

    ui->quickWidget->setClearColor(Qt::transparent);
    ui->quickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);

    connect(m_qml, SIGNAL(pressedKeyButton()), this, SIGNAL(kHardPressed()));
    connect(m_qml, SIGNAL(releasedKeyButton()), this, SIGNAL(lHardPressed()));
}

QVariant LlaveTecho::isPressed(){
    QVariant returnedValue(false);
    QMetaObject::invokeMethod(m_qml, "isPressed", Q_RETURN_ARG(QVariant, returnedValue));
    //qDebug() << "Valor retornado Llave Techo Activada: " << returnedValue;
    return returnedValue.toBool();
}

LlaveTecho::~LlaveTecho()
{
    delete ui;
}

void LlaveTecho::setOff()
{
    m_qml->setState("State1_keyOFF");
    emit lHardPressed();
    qDebug() << "Entro en llavetecho.cpp enviar señal L";
}

void LlaveTecho::setOn()
{
    m_qml->setState("State1_keyON");
    emit kHardPressed();
    qDebug() << "Entro en llavetecho.cpp enviar señal K";
}


