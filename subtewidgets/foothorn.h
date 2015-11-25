#ifndef FOOTHORN_H
#define FOOTHORN_H

#include <QWidget>
#include <QQuickItem>

namespace Ui {
class FootHorn;
}

class FootHorn : public QWidget
{
    Q_OBJECT

public:
    explicit FootHorn(QWidget *parent = 0);
    ~FootHorn();

    void setBocina(bool v);

private:
    Ui::FootHorn *ui;
    QQuickItem *m_qmlView;

signals:
    hornPressed();
    hornReleased();

};

#endif // FOOTHORN_H
