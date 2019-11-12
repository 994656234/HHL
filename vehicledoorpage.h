#ifndef VEHICLEDOORPAGE_H
#define VEHICLEDOORPAGE_H
#include "mybase.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class VehicleDoorPage;
}

class VehicleDoorPage : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleDoorPage(QWidget *parent = 0);
    ~VehicleDoorPage();
    void setDoorStatus(QLabel *label,QList<bool> status);
    void updatePage();

private:
    Ui::VehicleDoorPage *ui;
    QList<bool> DOORstatus;
};

#endif // VEHICLEDOORPAGE_H
