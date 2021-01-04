#ifndef VEHICLEPISPAGE_H
#define VEHICLEPISPAGE_H
#include "mybase.h"
#include "qlist.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class VehiclePISPage;
}

class VehiclePISPage : public MyBase
{
    Q_OBJECT

public:
    explicit VehiclePISPage(QWidget *parent = 0);
    ~VehiclePISPage();
    void updatePage();

private:
    Ui::VehiclePISPage *ui;
    QList<QLabel *> label;
    QList<bool> status;
    void PISStatus(QList<QLabel *> label, QList<bool> status, bool online);
};

#endif // VEHICLEPISPAGE_H
