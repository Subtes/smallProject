#include "alstomtractionlever.h"
#include "ui_alstomtractionlever.h"

AlstomTractionLever::AlstomTractionLever(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlstomTractionLever)
{
    ui->setupUi(this);

    connect (ui->verticalSlider,SIGNAL(valueChanged(int)),this,SIGNAL(positionChanged(int)));
    connect (ui->verticalSlider,SIGNAL(sliderPressed()),this,SIGNAL(hmPressed()));
    connect (ui->verticalSlider,SIGNAL(sliderReleased()),this,SIGNAL(hmReleased()));
}

AlstomTractionLever::~AlstomTractionLever()
{
    delete ui;
}

void AlstomTractionLever::setValue(int v)
{
    ui->verticalSlider->setValue(v);
}
