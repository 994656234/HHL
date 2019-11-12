#ifndef VEHICLEFIREWARNINGPAGE_H
#define VEHICLEFIREWARNINGPAGE_H
#include "mybase.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class VehicleFireWarningPage;
}

class VehicleFireWarningPage : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleFireWarningPage(QWidget *parent = 0);
    ~VehicleFireWarningPage();
    void updatePage();
    void setFireStatus(QLabel *label,QList<bool> status);

private:
    Ui::VehicleFireWarningPage *ui;
    QList<bool>  FASstatus;
    QList<QLabel *> FASlabel;
};

#endif // VEHICLEFIREWARNINGPAGE_H
