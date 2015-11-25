#ifndef LLAVEMODOCONDUCCION_H
#define LLAVEMODOCONDUCCION_H

#include <QWidget>
#include <QQuickItem>

namespace Ui {
class LlaveModoConduccion;
}

class LlaveModoConduccion : public QWidget
{
    Q_OBJECT

public:
    explicit LlaveModoConduccion(QWidget *parent = 0);
    ~LlaveModoConduccion();

    void setManiobraMode();
    void setAcopleMode();
    void setAtpMode();

private:
    Ui::LlaveModoConduccion *ui;
    QQuickItem *m_qmlView;

signals:
    maniobraMode();
    acopleMode();
    atpMode();

};

#endif // LLAVEMODOCONDUCCION_H
