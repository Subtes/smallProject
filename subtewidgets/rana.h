#ifndef RANA_H
#define RANA_H

#include <QWidget>

namespace Ui {
class Rana;
}

class Rana : public QWidget
{
    Q_OBJECT

public:
    explicit Rana(QWidget *parent = 0);
    ~Rana();
    void setValue(int v);

signals:
    void ranaAD();
    void ranaCERO();
    void ranaAT();

private slots:
    void processValueChanged(int value);

private:
    Ui::Rana *ui;
};

#endif // RANA_H
