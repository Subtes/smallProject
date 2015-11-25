#ifndef ALSTOMTRACTIONLEVER_H
#define ALSTOMTRACTIONLEVER_H

#include <QWidget>

namespace Ui {
class AlstomTractionLever;
}

class AlstomTractionLever : public QWidget
{
    Q_OBJECT

public:
    explicit AlstomTractionLever(QWidget *parent = 0);
    void setValue(int v);
    ~AlstomTractionLever();

private:
    Ui::AlstomTractionLever *ui;

signals:
    positionChanged(int);
    hmPressed();
    hmReleased();
};

#endif // ALSTOMTRACTIONLEVER_H
