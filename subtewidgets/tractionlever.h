#ifndef TRACTIONLEVER_H
#define TRACTIONLEVER_H

#include <QWidget>

namespace Ui {
class TractionLever;
}

class TractionLever : public QWidget
{
    Q_OBJECT

public:
    explicit TractionLever(QWidget *parent = 0);
    void setValue(int v);
    ~TractionLever();

private:
    Ui::TractionLever *ui;

signals:
    positionChanged(int);

    hvPressed();
    hvReleased();
};

#endif // TRACTIONLEVER_H
