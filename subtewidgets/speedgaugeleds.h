#ifndef SPEEDGAUGELEDS_H
#define SPEEDGAUGELEDS_H

#include <QWidget>
#include <QQuickItem>

namespace Ui {
class SpeedGaugeLeds;
}

class SpeedGaugeLeds : public QWidget
{
    Q_OBJECT

public:
    explicit SpeedGaugeLeds(QWidget *parent = 0);
    ~SpeedGaugeLeds();

private:
    Ui::SpeedGaugeLeds *ui;
    QQuickItem *m_qmlView;

public slots:
    void updateAllowedSpeed(double speed);
    void updateTargetSpeed(double speed);
    void updateSpeed(double speed);
    void turnOff();
    void turnOn();
    void setMode(int);
};

#endif // SPEEDGAUGELEDS_H
