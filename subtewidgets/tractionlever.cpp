#include "tractionlever.h"
#include "ui_tractionlever.h"
#include <QDebug>

TractionLever::TractionLever(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TractionLever)
{
    ui->setupUi(this);

    connect (ui->verticalSlider,SIGNAL(valueChanged(int)),this,SIGNAL(positionChanged(int)));
    connect (ui->verticalSlider,SIGNAL(sliderPressed()),this,SIGNAL(hvPressed()));
    connect (ui->verticalSlider,SIGNAL(sliderReleased()),this,SIGNAL(hvReleased()));
}

void TractionLever::setValue(int v)
{
    ui->verticalSlider->setValue(v);
}

TractionLever::~TractionLever()
{
    delete ui;
}

