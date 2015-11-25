#ifndef ALSTOMSELECTORMODOCONDUCCION_H
#define ALSTOMSELECTORMODOCONDUCCION_H

#include <QWidget>
#include <QQuickItem>

namespace Ui {
class AlstomSelectorModoConduccion;
}

class AlstomSelectorModoConduccion : public QWidget
{
    Q_OBJECT

public:
    explicit AlstomSelectorModoConduccion(QWidget *parent = 0);
    ~AlstomSelectorModoConduccion();

    //void setModoXX();
    //void setModoXX();
    //void setModoXX();

private:
    Ui::AlstomSelectorModoConduccion *ui;
    QQuickItem *m_qmlView;

signals:
    adelante();
    cochera();
    neutro();
    clr();
};

#endif // ALSTOMSELECTORMODOCONDUCCION_H
