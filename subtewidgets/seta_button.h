#ifndef SETA_BUTTON_H
#define SETA_BUTTON_H

#include <QWidget>
#include <QQuickItem>

namespace Ui {
class Seta_Button;
}

/**
  * Seta is device that, when you preesed the button is preesed to be preesed again,
  *  at this moment the button state is preesed changing to released.
  *
  * This are the signals on QML Seta_Button
  * signal preesedButton()
  * signal releasedButton()
  *
  * The Slot isPressed is a state function that return the state value at the QML seta device.
  */

class Seta_Button : public QWidget
{
    Q_OBJECT

public:
    explicit Seta_Button(QWidget *parent = 0);
    ~Seta_Button();
    void setOff();
    void setOn();

signals:
    void m_pressed();
    void m_released();

public slots:
    QVariant isPressed();

private:
    Ui::Seta_Button *ui = NULL;
    QQuickItem *qml = NULL;
};

#endif // SETA_BUTTON_H
