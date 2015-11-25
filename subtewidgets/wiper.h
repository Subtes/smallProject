#ifndef WIPER_H
#define WIPER_H

#include <QWidget>
#include <QQuickItem>

namespace Ui {
class Wiper;
}

class Wiper : public QWidget
{
    Q_OBJECT

public:
    explicit Wiper(QWidget *parent = 0);
    ~Wiper();

private:
    Ui::Wiper *ui;
    QQuickItem *m_qmlView;

signals:
    wiperOn();
    washer();
    wiperOff();
};

#endif // WIPER_H
