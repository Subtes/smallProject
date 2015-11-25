#ifndef SINGLEBUTTON_H
#define SINGLEBUTTON_H

#include <QWidget>
#include <QQuickItem>

namespace Ui {
class SingleButton;
}

class SingleButton : public QWidget
{
    Q_OBJECT

public:
    explicit SingleButton(QWidget *parent = 0);
    ~SingleButton();

    bool buttonState();
    bool isClickeable();
    bool isNestled();
    bool isLighted();
    void setButtonImage(QUrl on,QUrl off);
    void setButtonImageNestled(QUrl on,QUrl off);
    void setClickeable(bool clickeable);
    void setNestled(bool nestled);
    void setLighted(bool lighted);
    void setOnPressAsDriver();
    void setOnClickAsDriver();
    void setLightManagement(bool status);
    void setSize(QSize size);

private:
    Ui::SingleButton *ui;
    QQuickItem *m_qmlView;    

public slots:
    void startBlink();
    void stopBlink();
    void turnOn();
    void turnOff();
    void push();
    void release();

signals:
    buttonClicked();
    buttonPressed();
    buttonReleased();

};

#endif // SINGLEBUTTON_H
