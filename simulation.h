#ifndef SIMULATION_H
#define SIMULATION_H

#include <QWidget>
#include "mybase.h"
#include "qtimer.h"

namespace Ui {
    class Simulation;
}

class Simulation : public MyBase
{
    Q_OBJECT

public:
    explicit Simulation(QWidget *parent = 0);
    ~Simulation();
    void installMvb(CrrcRicoMvb* crrcRicoMvb);

private:
    Ui::Simulation *ui;
    void setMessage(QString message);
    CrrcRicoMvb* crrcRicoMvb;
    QTimer* timer;
    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_btnConfirm_clicked();
    void on_btnClose_clicked();
    void updatePage();

};

#endif // SIMULATION_H
