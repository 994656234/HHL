#include "passwordpage.h"
#include "ui_passwordpage.h"
#include "qdebug.h"

PasswordPage::PasswordPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::PasswordPage)
{
    ui->setupUi(this);
    ui->lbl_worryPassword->hide();
}

PasswordPage::~PasswordPage()
{
    delete ui;
}

int PasswordPage::passWordLength=0;
QString PasswordPage::password="";

void PasswordPage::on_BTNNum1_pressed()
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

void PasswordPage::on_BTNNum2_pressed()
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

void PasswordPage::on_BTNNum3_pressed()
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

void PasswordPage::on_BTNNum4_pressed()
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

void PasswordPage::on_BTNNum5_pressed()
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

void PasswordPage::on_BTNNum6_pressed()
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

void PasswordPage::on_BTNNum7_pressed()
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

void PasswordPage::on_BTNNum8_pressed()
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

void PasswordPage::on_BTNNum9_pressed()
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

void PasswordPage::on_BTNNum0_pressed()
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

void PasswordPage::on_BTNNumC_pressed()
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

void PasswordPage::on_BTN9OK_pressed()
{
    if(getParam->getString("/DatamanagePassword/DatamanagePassword")==password)
    {
        ui->lbl_worryPassword->hide();
        ui->LBLInputpassword->setText("");
        passWordLength=0;
        password="";
        changePage(uVehicleMaintainceDataManagePage);
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

void PasswordPage::on_BTN1back_pressed()
{
    changePage(uVehicleMaintainPage);
}

void PasswordPage::on_BTNNumClear_pressed()
{
    ui->LBLInputpassword->setText("");
    passWordLength=0;
    password="";
}

