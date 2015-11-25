#ifndef BOARDTOP_H
#define BOARDTOP_H

#include "baseboard.h"
#include "src/controllers/topboardconnectors_controller.h"
#include "src/controllers/topgauges_controller.h"
#include "src/controllers/key_topboard_controller.h"

namespace Ui {
class BoardTop;
}

class BoardTop : public BaseBoard
{
    Q_OBJECT

public:
    explicit BoardTop(QWidget *parent = 0, SubteStatus *subte = 0, EventHandler *eventHandler = 0);
    ~BoardTop();

public slots:
    void startBoard();
    void enableScreen();
    void disableScreen();
    void resetControls();
    void loadState(int state);
    void atpKeyON();
    void atpKeyOFF();
    void setHardware(TractionHardware *);

private:
    Ui::BoardTop *ui;
    TopBoardConnectors_Controller *m_connectors;
    TopGauges_Controller *m_topGauges;
    Key_TopBoard_Controller *m_keyTopBoard;
    TractionHardware *m_tractionHardware;
};

#endif // BOARDTOP_H
