#include "maintaincelat_rldpage.h"
#include "ui_maintaincelat_rldpage.h"

MaintainceLAT_RLDPage::MaintainceLAT_RLDPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceLAT_RLDPage)
{
    ui->setupUi(this);
    buttons<<ui->BTN1<<ui->BTNHome;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(NBpressEvent()));
    }
}

MaintainceLAT_RLDPage::~MaintainceLAT_RLDPage()
{
    delete ui;
}

void MaintainceLAT_RLDPage::updatePage()
{
    labels.clear();
    status.clear();
    labels<< ui->line1_1<< ui->line1_2<< ui->line1_3<< ui->line1_4<< ui->line1_5<< ui->line1_6
             << ui->line2_1<< ui->line2_2<< ui->line2_3<< ui->line2_4<< ui->line2_5<< ui->line2_6;
    status<< database->RM1CT_LAT_B1<< database->RM2CT_LAT_B1<< database->RM3CT_LAT_B1<< database->RM6CT_LAT_B1
             << database->RM5CT_LAT_B1<< database->RM5CT_LAT_B1
             << database->RM4CT_RLD_B1<< database->RM2CT_RLD_B1<< database->RM3CT_RLD_B1<< database->RM6CT_RLD_B1
                << database->RM4CT_RLD_B1<< database->RM5CT_RLD_B1;
    SetLabelStatus(labels,status);

}

void MaintainceLAT_RLDPage::SetLabelStatus(QList<QLabel *> lb, QList<bool> status)
{
    if (lb.size() != status.size())
        return;
    for (int i =0; i < lb.size(); i++)
    {
        if (status.at(i) == true)
        {
            lb.at(i)->setText("1");
        }
        else
        {
            lb.at(i)->setText("0");
        }
    }
}

void MaintainceLAT_RLDPage::NBpressEvent()
{
    QString BTNName=((QPushButton*)this->sender())->objectName();
    if(BTNName=="BTN1")
    {
        changePage(uVehicleMaintainPage);
    }
    else if(BTNName=="BTNHome")
    {
        changePage(uVehicleTrainArea);
    }
}
