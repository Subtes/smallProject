#include "seta_button.h"
#include "ui_seta_button.h"

Seta_Button::Seta_Button(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Seta_Button)
{
    ui->setupUi(this);

    ui->quickWidget_SetaButton->setClearColor(Qt::transparent);
    ui->quickWidget_SetaButton->setAttribute(Qt::WA_AlwaysStackOnTop);

    this->qml = ui->quickWidget_SetaButton->rootObject();

    connect(this->qml, SIGNAL(pressedButton()), this, SIGNAL(m_pressed()));
    connect(this->qml, SIGNAL(releasedButton()), this, SIGNAL(m_released()));

}

QVariant Seta_Button::isPressed(){
    QVariant returnedValue(false);
    QMetaObject::invokeMethod(this->qml, "isPressed", Q_RETURN_ARG(QVariant, returnedValue));
    //qDebug() << "Valor retornado Seta Activado: " << returnedValue;
    return returnedValue.toBool();
}

Seta_Button::~Seta_Button()
{
    delete ui;
}

void Seta_Button::setOff()
{
    this->qml->setState("State2_SetaOFF");
    emit m_released();
}

void Seta_Button::setOn()
{
    this->qml->setState("State1_SetaON");
    emit m_pressed();
}
