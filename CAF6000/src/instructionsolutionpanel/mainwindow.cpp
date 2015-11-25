#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "treemodel.h"

#include <QFile>
#include <QDebug>
#include <QString>

MainWindow::MainWindow(QWidget *parent, EventHandler *eventHandler) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_eventHandler = eventHandler;

    connect(ui->view, SIGNAL(clicked(QModelIndex)), this, SLOT(clickAction(QModelIndex)));

    QStringList headers;
    headers << tr("Operacion");

    QFile file(":/resources/instructionsolutionpanel.txt");
    file.open(QIODevice::ReadOnly);
    TreeModel *model = new TreeModel(headers, file.readAll());
    file.close();

    ui->view->setModel(model);
    for (int column = 0; column < model->columnCount(); ++column)
        ui->view->resizeColumnToContents(column);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clickAction(QModelIndex hoja)
{
  if (! hoja.model()->hasChildren(hoja))
  {
     QModelIndex root = hoja;
     while (root.parent().isValid())
            root = root.parent();
     clickActionDecision(hoja,root);
 }
}

void MainWindow::clickActionDecision(QModelIndex hoja, QModelIndex root)
{
    QString action = hoja.data(0).toString();
    QString father = hoja.parent().data(0).toString();
    QString category = hoja.parent().parent().data(0).toString();
    QString nrocoche = (root.data(0).toString());

    nrocoche.remove(0,nrocoche.size()-1); //Me quedo con el ultimo caracter, seria el nro de coche.

    if (nrocoche.operator ==("1"))
        nrocoche = "";
    else
        nrocoche = ("_" + nrocoche);

    if (category.operator ==("Grifos")){
        if (father.operator ==("B-138"))
            if (action.operator ==("CON"))
                m_eventHandler->notifyValueChanged("c_grifob138"+nrocoche.toStdString(),"con");
            else
                m_eventHandler->notifyValueChanged("c_grifob138"+nrocoche.toStdString(),"des");
        if (father.operator ==("L-2"))
            if (action.operator ==("CON"))
                m_eventHandler->notifyValueChanged("c_grifol2"+nrocoche.toStdString(),"con");
            else
                m_eventHandler->notifyValueChanged("c_grifol2"+nrocoche.toStdString(),"des");
        if (father.operator ==("B-73"))
            if (action.operator ==("CON"))
                m_eventHandler->notifyValueChanged("c_grifob73"+nrocoche.toStdString(),"con");
            else
                m_eventHandler->notifyValueChanged("c_grifob73"+nrocoche.toStdString(),"des");
    }
    else{
        if (category.operator ==("Termicos")){
            if (father.operator ==("57F1"))
                if (action.operator ==("CON"))
                    m_eventHandler->notifyValueChanged("c_termico_57f1"+nrocoche.toStdString(),"con");
                else
                    m_eventHandler->notifyValueChanged("c_termico_57f1"+nrocoche.toStdString(),"des");
            if (father.operator ==("53F1"))
                if (action.operator ==("CON"))
                    m_eventHandler->notifyValueChanged("c_termico_53f1"+nrocoche.toStdString(),"con");
                else
                    m_eventHandler->notifyValueChanged("c_termico_53f1"+nrocoche.toStdString(),"des");
            if (father.operator ==("33F1"))
                if (action.operator ==("CON"))
                    m_eventHandler->notifyValueChanged("c_termico_33f1"+nrocoche.toStdString(),"con");
                else
                    m_eventHandler->notifyValueChanged("c_termico_33f1"+nrocoche.toStdString(),"des");
        }
        else{
            if (category.operator ==("Pupitre")){
                if (father.operator ==("RANA"))
                    if (action.operator ==("AD"))
                        m_eventHandler->notifyValueChanged("c_rana"+nrocoche.toStdString(),"ad");
                    else
                        if (action.operator ==("0"))
                            m_eventHandler->notifyValueChanged("c_rana"+nrocoche.toStdString(),"0");
                        else
                            m_eventHandler->notifyValueChanged("c_rana"+nrocoche.toStdString(),"at");
                 if (father.operator ==("SETA"))
                     if (action.operator ==("CON"))
                         m_eventHandler->notifyValueChanged("c_seta_emergencia"+nrocoche.toStdString(),"con");
                     else
                         if (action.operator ==("DES"))
                             m_eventHandler->notifyValueChanged("c_seta_emergencia"+nrocoche.toStdString(),"des");
                         else
                             m_eventHandler->notifyValueChanged("c_seta_emergencia"+nrocoche.toStdString(),"inhabilitado");
            }
        }
    }
    qDebug() << "Clickeado!!!!" + action + " " + father + " " + category + " " + root.data(0).toString()+ " " + "c_rana" + nrocoche;
    //m_eventHandler->notifyValueChanged("c_grifoB138_N",action.toStdString());
    //qDebug() << "Clickeado!!!!" + (hoja.data(0)).toString();
}
