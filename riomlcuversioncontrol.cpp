#include "riomlcuversioncontrol.h"
#include "ui_riomlcuversioncontrol.h"

RIOMLCUVersionControl::RIOMLCUVersionControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RIOMLCUVersionControl)
{
    ui->setupUi(this);
}

RIOMLCUVersionControl::~RIOMLCUVersionControl()
{
    delete ui;
}

void RIOMLCUVersionControl::updateStatus(QList<QString> &status)
{
    QList<QLabel*> lbls;
    lbls<<ui->line1_name<<ui->line1_1<<ui->line1_2<<ui->line1_3<<ui->line1_4
    <<ui->line2_name<<ui->line2_1<<ui->line2_2<<ui->line2_3<<ui->line2_4
    <<ui->line3_name<<ui->line3_1<<ui->line3_2<<ui->line3_3<<ui->line3_4<<ui->line3_5<<ui->line3_6
    <<ui->line4_name<<ui->line4_1<<ui->line4_2<<ui->line4_3<<ui->line4_4<<ui->line4_5<<ui->line4_6
    <<ui->line5_name<<ui->line5_1<<ui->line5_2<<ui->line5_3<<ui->line5_4<<ui->line5_5<<ui->line5_6
    <<ui->line6_name<<ui->line6_1<<ui->line6_2<<ui->line6_3<<ui->line6_4<<ui->line6_5<<ui->line6_6
    <<ui->line7_name<<ui->line7_1<<ui->line7_2<<ui->line7_3<<ui->line7_4<<ui->line7_5<<ui->line7_6
;

    for(int i=0;i<status.length();i++)
    {
        lbls.at(i)->setText(status.at(i));
    }
}
