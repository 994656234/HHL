#include "vehiclepasswordpage.h"
#include "ui_vehiclepasswordpage.h"
#include "qdebug.h"

VehiclePasswordPage::VehiclePasswordPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehiclePasswordPage)
{
    ui->setupUi(this);
    ui->lbl_worryPassword->hide();  
}

int VehiclePasswordPage::passWordLength=0;
QString VehiclePasswordPage::password="";

VehiclePasswordPage::~VehiclePasswordPage()
{
    delete ui;
}

void VehiclePasswordPage::on_BTNNum1_clicked()
{
    if(passWordLength<4)
    {
        ui->LBLInputpassword->setText(ui->LBLInputpassword->text()+"*");
        password=password+"1";
        passWordLength++;
    }
    else
    {

    }
}

void VehiclePasswordPage::on_BTNNum2_clicked()
{
    if(passWordLength<4)
    {
        ui->LBLInputpassword->setText(ui->LBLInputpassword->text()+"*");
        password=password+"2";
        passWordLength++;
    }
    else
    {

    }
}

void VehiclePasswordPage::on_BTNNum3_clicked()
{
    if(passWordLength<4)
    {
        ui->LBLInputpassword->setText(ui->LBLInputpassword->text()+"*");
        password=password+"3";
        passWordLength++;
    }
    else
    {

    }
}

void VehiclePasswordPage::on_BTNNum4_clicked()
{
    if(passWordLength<4)
    {
        ui->LBLInputpassword->setText(ui->LBLInputpassword->text()+"*");
        password=password+"4";
        passWordLength++;
    }
    else
    {

    }

}

void VehiclePasswordPage::on_BTNNum5_clicked()
{
    if(passWordLength<4)
    {
        ui->LBLInputpassword->setText(ui->LBLInputpassword->text()+"*");
        password=password+"5";
        passWordLength++;
    }
    else
    {

    }

}

void VehiclePasswordPage::on_BTNNum6_clicked()
{
    if(passWordLength<4)
    {
        ui->LBLInputpassword->setText(ui->LBLInputpassword->text()+"*");
        password=password+"6";
        passWordLength++;
    }
    else
    {

    }
}

void VehiclePasswordPage::on_BTNNum7_clicked()
{
    if(passWordLength<4)
    {
        ui->LBLInputpassword->setText(ui->LBLInputpassword->text()+"*");
        password=password+"7";
        passWordLength++;
    }
    else
    {

    }
}

void VehiclePasswordPage::on_BTNNum8_clicked()
{
    if(passWordLength<4)
    {
        ui->LBLInputpassword->setText(ui->LBLInputpassword->text()+"*");
        password=password+"8";
        passWordLength++;
    }
    else
    {

    }

}

void VehiclePasswordPage::on_BTNNum9_clicked()
{
    if(passWordLength<4)
    {
        ui->LBLInputpassword->setText(ui->LBLInputpassword->text()+"*");
        password=password+"9";
        passWordLength++;
    }
    else
    {

    }
}

void VehiclePasswordPage::on_BTNNum0_clicked()
{
    if(passWordLength<4)
    {
        ui->LBLInputpassword->setText(ui->LBLInputpassword->text()+"*");
        password=password+"0";
        passWordLength++;
    }
    else
    {

    }
}

void VehiclePasswordPage::on_BTNNumC_clicked()
{
    ui->LBLInputpassword->setText(ui->LBLInputpassword->text().left(ui->LBLInputpassword->text().length()-1));
    password=password.left(password.length()-1);
    if(passWordLength>0)
    {
        passWordLength--;
    }
    else
    {
        passWordLength=0;
    }
}

void VehiclePasswordPage::on_BTN9OK_clicked()
{
    if(getParam->getString("/Password/Password")==password)
    {
        ui->lbl_worryPassword->hide();
        ui->LBLInputpassword->setText("");
        passWordLength=0;
        password="";
        changePage(uVehicleMaintainPage);
    }
    else if(""==ui->LBLInputpassword->text())
    {
        ui->lbl_worryPassword->setText("密码为空");
        ui->lbl_worryPassword->show();
        password="";
        passWordLength=0;
    }
    else
    {
        ui->lbl_worryPassword->setText("密码错误");
        ui->lbl_worryPassword->show();
        ui->LBLInputpassword->setText("");
        password="";
        passWordLength=0;
    }
}

void VehiclePasswordPage::on_BTN1back_clicked()
{
    changePage(uVehicleTrainArea);
}

void VehiclePasswordPage::on_BTNNumClear_pressed()
{
    ui->LBLInputpassword->setText("");
    passWordLength=0;
    password="";
}
