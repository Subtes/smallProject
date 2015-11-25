#include "alstomselectormodoconduccion.h"
#include "ui_alstomselectormodoconduccion.h"

AlstomSelectorModoConduccion::AlstomSelectorModoConduccion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlstomSelectorModoConduccion)
{
    ui->setupUi(this);
    ui->quickWidget->setClearColor(Qt::transparent);
    ui->quickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);

    m_qmlView = ui->quickWidget->rootObject();

    connect(m_qmlView,SIGNAL(pos1()),this,SIGNAL(clr()));
    connect(m_qmlView,SIGNAL(pos2()),this,SIGNAL(neutro()));
    connect(m_qmlView,SIGNAL(pos3()),this,SIGNAL(cochera()));
    connect(m_qmlView,SIGNAL(pos4()),this,SIGNAL(adelante()));
}

AlstomSelectorModoConduccion::~AlstomSelectorModoConduccion()
{
    delete ui;
}
