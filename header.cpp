#include "header.h"
#include "ui_header.h"
#include "qdatetime.h"
Header::Header(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::Header)
{
    ui->setupUi(this);
}

Header::~Header()
{
    delete ui;
}
void Header::updatePage()
{
    this->ui->LBLDateTime->setText(this->database->HMI_DateTime_foruse.date().toString("yyyy-MM-dd")+"    "+this->database->HMI_DateTime_foruse.time().toString("hh:mm:ss"));
    QString t_code;
    t_code.sprintf("%02d",database->CTD_TrainNum_U8);
    this->ui->LBLServiceNum->setText("车号: HH"+QString::number(database->CTD_LineNum_U8)+t_code);
}
void Header::setPageName(QString name)
{
    this->ui->LBLPageName->setText(name);
}


