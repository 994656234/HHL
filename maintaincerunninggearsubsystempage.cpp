#include "maintaincerunninggearsubsystempage.h"
#include "ui_maintaincerunninggearsubsystempage.h"

#define METROPRESS "background-color: rgb(0, 85, 255);border:1px solid black;font:20px \"微软雅黑\";"
#define METRORELEASE "background-color:rgb(170,170,170);border:1px solid black;font:20px \"微软雅黑\";"


MaintainceRunningGearSubsystemPage::MaintainceRunningGearSubsystemPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceRunningGearSubsystemPage)
{
    ui->setupUi(this);
    metroButtons<<ui->btn_metro1<<ui->btn_metro2<<ui->btn_metro3<<ui->btn_metro4;
    foreach(QPushButton *button,metroButtons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(metroBTNPressEvent()));
        button->setStyleSheet(METRORELEASE);
    }
    ui->btn_metro1->setStyleSheet(METROPRESS);
    metroNum = 1;

    line<< ui->line1_1<< ui->line1_2<< ui->line1_4<< ui->line1_7
        << ui->line2_1<< ui->line2_2<< ui->line2_4<< ui->line2_7
        << ui->line3_1<< ui->line3_2<< ui->line3_4<< ui->line3_7
        << ui->line4_1<< ui->line4_2<< ui->line4_4<< ui->line4_7
        << ui->line5_1<< ui->line5_2<< ui->line5_4<< ui->line5_7;

    ui->lbl_cab1_direction->hide();
    ui->lbl_cab2_direction->hide();
    ui->lbl_cab1_active->hide();
    ui->lbl_cab2_active->hide();
}

MaintainceRunningGearSubsystemPage::~MaintainceRunningGearSubsystemPage()
{
    delete ui;
}

void MaintainceRunningGearSubsystemPage::on_BTN1_pressed()
{
    changePage(uVehicleTrainArea);
}

void MaintainceRunningGearSubsystemPage::metroBTNPressEvent()
{
    metroNum= ((QPushButton*)this->sender())->whatsThis().toInt();

    for(int i=0;i<4;i++)
    {
        metroButtons.at(i)->setStyleSheet(METRORELEASE);
    }
    metroButtons.at(metroNum-1)->setStyleSheet(METROPRESS);

}

void MaintainceRunningGearSubsystemPage::on_BTNHome_pressed()
{
    changePage(uVehicleTrainArea);
}

void MaintainceRunningGearSubsystemPage::updatePage()
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

    updateStatus(line,database->BMSiCT_TMPE_U8,metroNum -1);
}

void MaintainceRunningGearSubsystemPage::updateStatus(QList<QLabel *> lbl, int value[4][20], int index)
{
    for (int i =0; i < 20; i++)
    {
//        qDebug()<<"$$$$"<<value[index][i];
        if (-1 == value[index][i])
        {
            lbl.at(i)->setText("--");
        }
        else
        {
            lbl.at(i)->setText(QString::number(value[index][i] - 55));
        }
    }
}

