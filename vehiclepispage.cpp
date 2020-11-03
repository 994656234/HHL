#include "vehiclepispage.h"
#include "ui_vehiclepispage.h"

#define  PISNORMAL "border-image: url(:/images/image/pisnoactive.png);"
#define  PISFAULT "border-image: url(:/images/image/pisfault.png);"
#define  PISTALK "border-image: url(:/images/image/pisdriveractive.png);"
#define  PISWARNING "border-image: url(:/images/image/pispassengeractive.png);"
#define  PISUNKNOW  "border-image: url(:/images/image/doorunknow.png);"

VehiclePISPage::VehiclePISPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehiclePISPage)
{
    ui->setupUi(this);
    ui->lbl_cab1_active->hide();
    ui->lbl_cab2_active->hide();
    ui->lbl_cab1_direction->hide();
    ui->lbl_cab2_direction->hide();
}

VehiclePISPage::~VehiclePISPage()
{
    delete ui;
}

void VehiclePISPage::updatePage()
{
    //司机室激活
    if(database->CTD_MCTActive_B1)
    {
        ui->lbl_cab1_active->show();
    }
    else
    {
        ui->lbl_cab1_active->hide();
    }

    if(database->CTD_MC2Active_B1)
    {
        ui->lbl_cab2_active->show();
    }
    else
    {
        ui->lbl_cab2_active->hide();
    }
    //列车运行方向
    if(database->CTD_Forward_B1)
    {
        ui->lbl_cab1_direction->show();
    }
    else
    {
        ui->lbl_cab1_direction->hide();
    }

    if(database->CTD_Backward_B1)
    {
        ui->lbl_cab2_direction->show();
    }
    else
    {
        ui->lbl_cab2_direction->hide();
    }

    label<<ui->lbl_1_1<<ui->lbl_1_2<<ui->lbl_1_3<<ui->lbl_1_4<<ui->lbl_1_5<<ui->lbl_1_6;
    status<<database->PISiCT_P81_B1<<database->PISiCT_P113_B1<<database->PISiCT_P145_B1
         <<database->PISiCT_P82_B1<<database->PISiCT_P114_B1<<database->PISiCT_P146_B1
        <<database->PISiCT_P83_B1<<database->PISiCT_P115_B1<<database->PISiCT_P147_B1
       <<database->PISiCT_P84_B1<<database->PISiCT_P116_B1<<database->PISiCT_P148_B1
      <<database->PISiCT_P85_B1<<database->PISiCT_P117_B1<<database->PISiCT_P149_B1
     <<database->PISiCT_P86_B1<<database->PISiCT_P118_B1<<database->PISiCT_P150_B1;
  PISStatus(label,status);
  label.clear();
  status.clear();

  label<<ui->lbl_2_1<<ui->lbl_2_2<<ui->lbl_2_3<<ui->lbl_2_4<<ui->lbl_2_5<<ui->lbl_2_6;
  status<<database->PISiCT_P89_B1<<database->PISiCT_P121_B1<<database->PISiCT_P153_B1
       <<database->PISiCT_P90_B1<<database->PISiCT_P122_B1<<database->PISiCT_P154_B1
      <<database->PISiCT_P91_B1<<database->PISiCT_P123_B1<<database->PISiCT_P155_B1
     <<database->PISiCT_P92_B1<<database->PISiCT_P124_B1<<database->PISiCT_P156_B1
    <<database->PISiCT_P93_B1<<database->PISiCT_P125_B1<<database->PISiCT_P157_B1
   <<database->PISiCT_P94_B1<<database->PISiCT_P126_B1<<database->PISiCT_P158_B1;
  PISStatus(label,status);
  label.clear();
  status.clear();


  label<<ui->lbl_3_1<<ui->lbl_3_2<<ui->lbl_3_3<<ui->lbl_3_4<<ui->lbl_3_5<<ui->lbl_3_6;
  status<<database->PISiCT_P97_B1<<database->PISiCT_P129_B1<<database->PISiCT_P161_B1
       <<database->PISiCT_P98_B1<<database->PISiCT_P130_B1<<database->PISiCT_P162_B1
      <<database->PISiCT_P99_B1<<database->PISiCT_P131_B1<<database->PISiCT_P163_B1
     <<database->PISiCT_P100_B1<<database->PISiCT_P132_B1<<database->PISiCT_P164_B1
    <<database->PISiCT_P101_B1<<database->PISiCT_P133_B1<<database->PISiCT_P165_B1
   <<database->PISiCT_P102_B1<<database->PISiCT_P134_B1<<database->PISiCT_P166_B1;
  PISStatus(label,status);
  label.clear();
  status.clear();

  label<<ui->lbl_4_1<<ui->lbl_4_2<<ui->lbl_4_3<<ui->lbl_4_4<<ui->lbl_4_5<<ui->lbl_4_6;
  status<<database->PISiCT_P105_B1<<database->PISiCT_P137_B1<<database->PISiCT_P169_B1
       <<database->PISiCT_P106_B1<<database->PISiCT_P138_B1<<database->PISiCT_P170_B1
      <<database->PISiCT_P107_B1<<database->PISiCT_P139_B1<<database->PISiCT_P171_B1
     <<database->PISiCT_P108_B1<<database->PISiCT_P140_B1<<database->PISiCT_P172_B1
    <<database->PISiCT_P109_B1<<database->PISiCT_P141_B1<<database->PISiCT_P173_B1
   <<database->PISiCT_P110_B1<<database->PISiCT_P142_B1<<database->PISiCT_P174_B1;
  PISStatus(label,status);
  label.clear();
  status.clear();
}

void VehiclePISPage::PISStatus(QList<QLabel *> label, QList<bool> status)
{
    if(label.length()!=6&&status.length()!=18)
    {
        qDebug()<<"length is not right";
        return;
    }

    for(int i =0;i<6;i++)
    {
            if(status.at(0+i*3))
            {
                label.at(i)->setStyleSheet(PISFAULT);
            }
            else if(status.at(1+i*3))
            {
                label.at(i)->setStyleSheet(PISWARNING);
            }
            else if(status.at(2+i*3))
            {
                label.at(i)->setStyleSheet(PISTALK);
            }
            else
            {
                label.at(i)->setStyleSheet(PISNORMAL);
            }
    }

}

