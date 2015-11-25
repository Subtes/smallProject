#include "speedgauge.h"
#include "ui_speedgauge.h"

SpeedGauge::SpeedGauge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpeedGauge)
{
    ui->setupUi(this);

    ui->quickWidget->setClearColor(Qt::transparent);
    ui->quickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);

    m_qmlView = ui->quickWidget->rootObject();

}

SpeedGauge::~SpeedGauge()
{
    delete ui;
}

void SpeedGauge::updateNeedle(double speed){

    QVariant returnedValue;

    QMetaObject::invokeMethod(m_qmlView, "updateNeedle",
            Q_RETURN_ARG(QVariant, returnedValue),
            Q_ARG(QVariant, speed));
}
