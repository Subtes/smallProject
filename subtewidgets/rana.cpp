#include "rana.h"
#include "ui_rana.h"
#include <QtDebug>

Rana::Rana(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Rana)
{
    ui->setupUi(this);
    connect (ui->rana_slider,SIGNAL(valueChanged(int)),this,SLOT(processValueChanged(int)));
}

void Rana::processValueChanged(int pos){

    switch ( pos ) {
    case 1:
            emit ranaAD();
            break;
    case 0:
            emit ranaCERO();
            break;
    case -1:
            emit ranaAT();
            break;
    default:
        qDebug() << "Error: Rana value DEVICE" << pos;
        break;
    }

}

Rana::~Rana()
{
    delete ui;
}

void Rana::setValue(int v)
{
    ui->rana_slider->setValue(v);
}
