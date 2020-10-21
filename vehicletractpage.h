#ifndef VEHICLETRACTPAGE_H
#define VEHICLETRACTPAGE_H
#include "mybase.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class VehicleTractPage;
}

class VehicleTractPage : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleTractPage(QWidget *parent = 0);
    ~VehicleTractPage();
    void updatePage();

private:
    Ui::VehicleTractPage *ui;
    void setTractStatus(QLabel *label,bool cut,bool guohaha, bool status);
};

#endif // VEHICLETRACTPAGE_H
