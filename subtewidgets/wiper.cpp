#include "wiper.h"
#include "ui_wiper.h"

Wiper::Wiper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Wiper)
{
    ui->setupUi(this);

    ui->selector->setClearColor(Qt::transparent);
    ui->selector->setAttribute(Qt::WA_AlwaysStackOnTop);

    m_qmlView = ui->selector->rootObject();

    connect (m_qmlView,SIGNAL(wiper()),this,SIGNAL(wiperOn()));
    connect (m_qmlView,SIGNAL(washer()),this,SIGNAL(washer()));
    connect (m_qmlView,SIGNAL(off()),this,SIGNAL(wiperOff()));
}

Wiper::~Wiper()
{
    delete ui;
}
