#ifndef LLAVETECHO_H
#define LLAVETECHO_H

#include <QWidget>
#include <QQuickItem>

namespace Ui {
class LlaveTecho;
}

class LlaveTecho : public QWidget
{
    Q_OBJECT

public:
    explicit LlaveTecho(QWidget *parent = 0);
    ~LlaveTecho();
    void setOff();
    void setOn();

signals:
    void kHardPressed();
    void lHardPressed();

public slots:
    QVariant isPressed();

private:
    Ui::LlaveTecho *ui;
    QQuickItem *m_qml = NULL;
};

#endif // LLAVETECHO_H
