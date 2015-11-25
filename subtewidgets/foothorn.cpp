#include "foothorn.h"
#include "ui_foothorn.h"

FootHorn::FootHorn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FootHorn)
{
    ui->setupUi(this);
    ui->pedal->setClearColor(Qt::transparent);
    ui->pedal->setAttribute(Qt::WA_AlwaysStackOnTop);

    m_qmlView = ui->pedal->rootObject();

    connect (m_qmlView,SIGNAL(pedalPressed()),this,SIGNAL(hornPressed()));
    connect (m_qmlView,SIGNAL(pedalReleased()),this,SIGNAL(hornReleased()));
}

FootHorn::~FootHorn()
{
    delete ui;
}

void FootHorn::setBocina(bool v)
{
    QVariant returnedValue;

    if(v){
    QMetaObject::invokeMethod(m_qmlView, "press",
        Q_RETURN_ARG(QVariant, returnedValue)
        );
    }else{
        QMetaObject::invokeMethod(m_qmlView, "release",
        Q_RETURN_ARG(QVariant, returnedValue)
        );
    }

}
