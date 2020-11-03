#ifndef VEHICLEMAINTAINPAGE_H
#define VEHICLEMAINTAINPAGE_H
#include "mybase.h"
#include "qpushbutton.h"

#include <QWidget>

namespace Ui {
    class VehicleMaintainPage;
}

class VehicleMaintainPage : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleMaintainPage(QWidget *parent = 0);
    ~VehicleMaintainPage();


private:
    Ui::VehicleMaintainPage *ui;
    QList<QPushButton*>buttons;
    bool fangyouFlag,qiangqiflag;

private slots:
    void NBpressEvent();
    void on_BTN_fangyou_pressed();
    void on_BTN_qiangqi_pressed();
};

#endif // VEHICLEMAINTAINPAGE_H
