#ifndef MANOMETER_H
#define MANOMETER_H

#include <QWidget>
#include <QQuickItem>


namespace Ui {
class Manometer;
}

class Manometer : public QWidget
{
    Q_OBJECT

public:
    explicit Manometer(QWidget *parent = 0);
    ~Manometer();
    void setBackgroudImage(QUrl bg);
    void setNeedleWhiteImage(QUrl nw);
    void setNeedleRedImage(QUrl nr);
    void setGlassImage(QUrl gl);
    void setNeedleWhiteImage(QUrl nw, int anchorX, int anchorY);
    void setNeedleRedImage(QUrl nr, int anchorX, int anchorY);
    void setMinMaxValue(int maxV, int minV);
    void setMaxAngle(int angle);
    void setOffsetAngle(int angle);

protected:
    Ui::Manometer *ui;
    QQuickItem *m_qmlView;

public slots:
    void updateNeedleRed(double value);
    void updateNeedleWhite(double value);
};


#endif // MANOMETER_H
