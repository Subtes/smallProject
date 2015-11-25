#ifndef SPEEDGAUGE_H
#define SPEEDGAUGE_H

#include <QWidget>
#include <QQuickItem>

namespace Ui {
class SpeedGauge;
}

class SpeedGauge : public QWidget
{
    Q_OBJECT

public:
    explicit SpeedGauge(QWidget *parent = 0);
    ~SpeedGauge();

private:
    Ui::SpeedGauge *ui;
    QQuickItem *m_qmlView;

public slots:
    void updateNeedle(double speed);
};

#endif // SPEEDGAUGE_H
