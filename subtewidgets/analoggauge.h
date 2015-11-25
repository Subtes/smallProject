#ifndef ANALOGGAUGE_H
#define ANALOGGAUGE_H

#include <QWidget>
#include <QQuickItem>

namespace Ui {
class AnalogGauge;
}

class AnalogGauge : public QWidget
{
    Q_OBJECT

public:
    explicit AnalogGauge(QWidget *parent = 0);
    ~AnalogGauge();

    void setBackgroudImage(QUrl bg);
    void setNeedleImage(QUrl n);
    void setNeedleImage(QUrl n, int anchorX, int anchorY);
    void setMinMaxValue(int maxV, int minV);
    void setMaxAngle(int angle);
    void setOffsetAngle(int angle);

protected:
    Ui::AnalogGauge *ui;
    QQuickItem *m_qmlView;

public slots:
    void updateNeedle(double value);
};

#endif // ANALOGGAUGE_H
