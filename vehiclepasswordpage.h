#ifndef VEHICLEPASSWORDPAGE_H
#define VEHICLEPASSWORDPAGE_H
#include "MainGetDefaultPara.h"

#include <mybase.h>

namespace Ui {
    class VehiclePasswordPage;
}

class VehiclePasswordPage : public MyBase
{
    Q_OBJECT

public:
    explicit VehiclePasswordPage(QWidget *parent = 0);
    ~VehiclePasswordPage();
    static int passWordLength;
    static QString password;


private:
    Ui::VehiclePasswordPage *ui;
    MainGetDefaultPara *getParam;


private slots:
    void on_BTNNumClear_pressed();
    void on_BTN1back_clicked();
    void on_BTN9OK_clicked();
    void on_BTNNumC_clicked();
    void on_BTNNum0_clicked();
    void on_BTNNum9_clicked();
    void on_BTNNum8_clicked();
    void on_BTNNum7_clicked();
    void on_BTNNum6_clicked();
    void on_BTNNum5_clicked();
    void on_BTNNum4_clicked();
    void on_BTNNum3_clicked();
    void on_BTNNum2_clicked();
    void on_BTNNum1_clicked();

};

#endif // VEHICLEPASSWORDPAGE_H
