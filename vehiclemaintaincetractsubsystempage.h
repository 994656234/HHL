#ifndef VEHICLEMAINTAINCETRACTSUBSYSTEMPAGE_H
#define VEHICLEMAINTAINCETRACTSUBSYSTEMPAGE_H
#include "mybase.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class VehicleMaintainceTractSubsystemPage;
}

static int current;

class VehicleMaintainceTractSubsystemPage : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleMaintainceTractSubsystemPage(QWidget *parent = 0);
    ~VehicleMaintainceTractSubsystemPage();
    void updatePage();
    void updateStatus(QList<QLabel*> lbl, QList<QString> status);

private:
    Ui::VehicleMaintainceTractSubsystemPage *ui;
    QList<QLabel*> line1,line2,line3,line4,line5,line6,line7,line8,line9;
    QList<QString> line1Status,line2Status,line3Status,line4Status,line5Status,line6Status,line7Status,line8Status;
    QString isVelid(bool haha,QString status);

private slots:
    void on_BTN3_pressed();
    void on_BTN2_pressed();
    void on_BTNHome_pressed();
    void on_BTN1_pressed();
};

#endif // VEHICLEMAINTAINCETRACTSUBSYSTEMPAGE_H
