#include "singlebutton.h"
#include "ui_singlebutton.h"

SingleButton::SingleButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleButton)
{
    ui->setupUi(this);

    ui->button->setClearColor(Qt::transparent);
    ui->button->setAttribute(Qt::WA_AlwaysStackOnTop);

    m_qmlView = ui->button->rootObject();
    connect(m_qmlView,SIGNAL(buttonClicked()),this,SIGNAL(buttonClicked()));
    connect(m_qmlView,SIGNAL(buttonReleased()),this,SIGNAL(buttonReleased()));
    connect(m_qmlView,SIGNAL(buttonPressed()),this,SIGNAL(buttonPressed()));
}

SingleButton::~SingleButton()
{
    delete ui;
}

bool SingleButton::buttonState()
{
    QVariant state = m_qmlView->property("state");
    return ((QString::compare(state.toString(),"buttonOnState")==0)
            ||(QString::compare(state.toString(),"buttonOnStateNestled")==0));
}

bool SingleButton::isClickeable()
{
    return m_qmlView->property("enabled").toBool();
}

bool SingleButton::isNestled()
{
    return m_qmlView->property("nestled").toBool();;
}

bool SingleButton::isLighted()
{
    return m_qmlView->property("lighted").toBool();;
}

void SingleButton::setButtonImage(QUrl on,QUrl off)
{
    QObject * button = m_qmlView->findChild<QObject*>("onImage");
    button->setProperty("source", on);
    button = m_qmlView->findChild<QObject*>("offImage");
    button->setProperty("source", off);
}

void SingleButton::setButtonImageNestled(QUrl on,QUrl off)
{
    QObject * button = m_qmlView->findChild<QObject*>("onImageNestled");
    button->setProperty("source", on);
    button = m_qmlView->findChild<QObject*>("offImageNestled");
    button->setProperty("source", off);
}

void SingleButton::setClickeable(bool clickeable)
{
    m_qmlView->setProperty("enabled",clickeable);
}

void SingleButton::setNestled(bool nestled)
{
    m_qmlView->setProperty("nestled", nestled );
}

void SingleButton::setLighted(bool lighted)
{
    m_qmlView->setProperty("lighted", lighted );
}

void SingleButton::setOnPressAsDriver(){
    m_qmlView->setProperty("onPressDriver", true );
}

void SingleButton::setOnClickAsDriver(){
    m_qmlView->setProperty("onPressDriver", false );
}

void SingleButton::setLightManagement(bool status){
    m_qmlView->setProperty("lightManager", status );
}

void SingleButton::startBlink()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "startBlink",
                              Q_RETURN_ARG(QVariant, returnedValue));
}

void SingleButton::stopBlink()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(m_qmlView, "stopBlink",
                              Q_RETURN_ARG(QVariant, returnedValue));
}

void SingleButton::turnOn()
{
    QVariant state = m_qmlView->property("state");
    if(QString::compare(state.toString(),"buttonOffState")==0){
        m_qmlView->setProperty("state", "buttonOnState" );}
    else if(QString::compare(state.toString(),"buttonOffStateNestled")==0){
        m_qmlView->setProperty("state", "buttonOnStateNestled" );
    }
}

void SingleButton::turnOff()
{
    QVariant state = m_qmlView->property("state");
    if(QString::compare(state.toString(),"buttonOnState")==0)
        m_qmlView->setProperty("state", "buttonOffState" );
    else if(QString::compare(state.toString(),"buttonOnStateNestled")==0)
        m_qmlView->setProperty("state", "buttonOffStateNestled" );
}

void SingleButton::push()
{
    QVariant state = m_qmlView->property("state");
    if(QString::compare(state.toString(),"buttonOnState")==0)
        m_qmlView->setProperty("state", "buttonOnStateNestled" );
    else if(QString::compare(state.toString(),"buttonOffState")==0)
        m_qmlView->setProperty("state", "buttonOffStateNestled" );
}

void SingleButton::release()
{
    QVariant state = m_qmlView->property("state");
    if(QString::compare(state.toString(),"buttonOnStateNestled")==0)
        m_qmlView->setProperty("state", "buttonOnState" );
    else if(QString::compare(state.toString(),"buttonOffStateNestled")==0)
        m_qmlView->setProperty("state", "buttonOffState" );
}

void SingleButton::setSize(QSize size)
{
    m_qmlView->setSize(size);
}
