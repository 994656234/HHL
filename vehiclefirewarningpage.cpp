#include "vehiclefirewarningpage.h"
#include "ui_vehiclefirewarningpage.h"

#define  FIREOK "border-image: url(:/images/image/firenone.png);"
#define  FIREALARM "border-image: url(:/images/image/firealarm.png);"
#define  FIREFAULT "border-image: url(:/images/image/firefault.png);"
#define  FIREPOLLUTED "border-image: url(:/images/image/firewarn.png);"
#define  FIREUNKNOW "border-image: url(:/images/image/doorunknow.png);"
#define  FIRCUT "border-image: url(:/images/image/bcubypass.png);"

VehicleFireWarningPage::VehicleFireWarningPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleFireWarningPage)
{
    ui->setupUi(this);
    ui->lbl_cab1_active->hide();
    ui->lbl_cab2_active->hide();
    ui->lbl_cab1_direction->hide();
    ui->lbl_cab2_direction->hide();

    label<<ui->lbl_1<<ui->lbl_2<<ui->lbl_3<<ui->lbl_4<<ui->lbl_5<<ui->lbl_6<<ui->lbl_7<<ui->lbl_8<<ui->lbl_9<<ui->lbl_10
        <<ui->lbl_11<<ui->lbl_12<<ui->lbl_13<<ui->lbl_14<<ui->lbl_15<<ui->lbl_16<<ui->lbl_17<<ui->lbl_18<<ui->lbl_19<<ui->lbl_20
       <<ui->lbl_21<<ui->lbl_22;

}

VehicleFireWarningPage::~VehicleFireWarningPage()
{
    delete ui;
}


void VehicleFireWarningPage::updatePage()
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

    status1<<database->FCU1CT_SHD1Alarm1_B1<<database->FCU1CT_SHD2Alarm1_B1<<database->FCU1CT_SHD3Alarm1_B1<<database->FCU1CT_SHD4Alarm1_B1
          <<database->FCU1CT_SHD5Alarm1_B1<<database->FCU1CT_SHD6Alarm1_B1<<database->FCU1CT_SHD7Alarm1_B1<<database->FCU1CT_SHD1Alarm2_B1
         <<database->FCU1CT_SHD2Alarm2_B1<<database->FCU1CT_SHD3Alarm2_B1<<database->FCU1CT_SHD4Alarm2_B1<<database->FCU1CT_SHD1Alarm3_B1
        <<database->FCU1CT_SHD2Alarm3_B1<<database->FCU1CT_SHD3Alarm3_B1<<database->FCU1CT_SHD4Alarm3_B1<<database->FCU1CT_SHD1Alarm4_B1
       <<database->FCU1CT_SHD2Alarm4_B1<<database->FCU1CT_SHD3Alarm4_B1<<database->FCU1CT_SHD4Alarm4_B1<<database->FCU1CT_SHD5Alarm4_B1
      <<database->FCU1CT_SHD6Alarm4_B1<<database->FCU1CT_SHD7Alarm4_B1;

    status2<<database->FCU1CT_SHD1Flt1_B1<<database->FCU1CT_SHD2Flt1_B1<<database->FCU1CT_SHD3Flt1_B1<<database->FCU1CT_SHD4Flt1_B1
          <<database->FCU1CT_SHD5Flt1_B1<<database->FCU1CT_SHD6Flt1_B1<<database->FCU1CT_SHD7Flt1_B1<<database->FCU1CT_SHD1Flt2_B1
         <<database->FCU1CT_SHD2Flt2_B1<<database->FCU1CT_SHD3Flt2_B1<<database->FCU1CT_SHD4Flt2_B1<<database->FCU1CT_SHD1Flt3_B1
        <<database->FCU1CT_SHD2Flt3_B1<<database->FCU1CT_SHD3Flt3_B1<<database->FCU1CT_SHD4Flt3_B1<<database->FCU1CT_SHD1Flt4_B1
       <<database->FCU1CT_SHD2Flt4_B1<<database->FCU1CT_SHD3Flt4_B1<<database->FCU1CT_SHD4Flt4_B1<<database->FCU1CT_SHD5Flt4_B1
      <<database->FCU1CT_SHD6Flt4_B1<<database->FCU1CT_SHD7Flt4_B1;
    setFireWarnstatus(label,status1,status2);

    status1.clear();
    status2.clear();
}

void VehicleFireWarningPage::setFireStatus(QLabel *label, QList<bool> status)
{
    if(status.at(0))
    {
        label->setStyleSheet(FIREALARM);

    }else if(status.at(1))
    {
        label->setStyleSheet(FIREFAULT);

    }else if(status.at(2))
    {
        label->setStyleSheet(FIRCUT);

    }else if(status.at(3))
    {
        label->setStyleSheet(FIREPOLLUTED);

    }else if(status.at(4))
    {
        label->setStyleSheet(FIREOK);

    }else
    {
        label->setStyleSheet(FIREUNKNOW);
    }

}

void VehicleFireWarningPage::setFireWarnstatus(QList<QLabel*> label, QList<bool> status1, QList<bool> status2)
{
    if((status1.length()!=22)||(status2.length()!=22)||(label.length()!=22))
    {
        qDebug()<<"fire warnning status1.length!=status2.length || label.length!=22";
        return;
    }
    for(int i=0;i<status1.length();i++)
    {

        if(status1.at(i))
        {
            label.at(i)->setStyleSheet(FIREALARM);
        }
        else if(status2.at(i))
        {
            label.at(i)->setStyleSheet(FIREFAULT);
        }
        else
        {
            label.at(i)->setStyleSheet(FIREOK);
        }
    }

}
