#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include "src/controllers/eventhandler.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, EventHandler *eventHandler = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void clickAction(QModelIndex hoja);
    void clickActionDecision(QModelIndex hoja,QModelIndex root);

protected:
    EventHandler    *m_eventHandler;

};

#endif // MAINWINDOW_H
