#include "maintaincedatamanagepage.h"
#include "ui_maintaincedatamanagepage.h"
#include "qdebug.h"

#define CONFIRMRELEASE "font: 20px, \"微软雅黑\";color: black;transparent;background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 rgba(170,170,170,255),stop:1 rgba(150,150,150,255));"
#define CONFIRMPRESS "font: 20px, \"微软雅黑\";color: black;background-color: rgb(85, 85, 255);"


MaintainceDataManagePage::MaintainceDataManagePage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceDataManagePage)
{
    ui->setupUi(this);
    ui->lbl_10->hide();
    ui->BTNTime->hide();

    QList<QPushButton*> buttons;
    buttons<<ui->BTN1<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5<<ui->BTN6<<ui->BTN7<<ui->BTN8<<ui->BTN9<<ui->BTNHome;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(pushButtonPressedEvent()));
    }

    m_Numbuttons<<ui->BTNNum0<<ui->BTNNum1<<ui->BTNNum2<<ui->BTNNum3<<ui->BTNNum4<<ui->BTNNum5
                <<ui->BTNNum6<<ui->BTNNum7<<ui->BTNNum8<<ui->BTNNum9<<ui->BTNNumC;
    foreach(QPushButton* button,m_Numbuttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(NumbuttonsPressedEvent()));
    }

    m_Selectbuttons<<ui->BTNTCUcomsuption<<ui->BTNACUcomsuption<<ui->BTNBCUcomsuption<<ui->BTNEBcomsuption
            <<ui->BTNACCMile<<ui->BTNACP1runtime<<ui->BTNACP2runtime<<ui->BTNDistance<<ui->BTNTime;
    foreach(QPushButton* button,m_Selectbuttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(SelectbuttonsPressedEvent()));
    }
    timer2s = new QTimer;

    m_button = ui->BTNTCUcomsuption;
    ui->BTNTCUcomsuption->setStyleSheet(PButtonDOWN);

    connect(timer2s,SIGNAL(timeout()),this,SLOT(ConfirmPressEvent()));
}

MaintainceDataManagePage::~MaintainceDataManagePage()
{
    delete ui;
}
void MaintainceDataManagePage::ConfirmPressEvent()
{
    ui->BTN9->setStyleSheet(CONFIRMRELEASE);
//    this->database->HMiCT_RunStatSetData_U32 = 0;
//    this->database->HMiCT_RunStatSetType_U8 = 0;
//    this->database->HMiCT_RunStatSetFlag_B1 = false;
    timer2s->stop();
}
void MaintainceDataManagePage::NumbuttonsPressedEvent()
{
    if(((QPushButton*)this->sender())->text() == "C")
    {
        m_button->setText("");
    }else
    {
        m_button->setText(m_button->text()+((QPushButton*)this->sender())->text());
    }
}
void MaintainceDataManagePage::SelectbuttonsPressedEvent()
{
    for(int i = 0;i<m_Selectbuttons.size();i++)
    {
        m_Selectbuttons.at(i)->setStyleSheet(PButtonUP);
    }
    ((QPushButton*)this->sender())->setStyleSheet(PButtonDOWN);
    m_button = ((QPushButton*)this->sender());
}
void MaintainceDataManagePage::pushButtonPressedEvent()
{
    QString btnName=((QPushButton*)this->sender())->objectName();
    if(btnName=="BTN1")
    {
        changePage(uVehicleMaintainPage);
    }
    else if(btnName=="BTNHome")
    {
        changePage(uVehicleTrainArea);
    }else if(btnName=="BTN9")
    {
//        this->database->HMiCT_RunStatSetData_U32 = m_button->text().toUInt();
//        this->database->HMiCT_RunStatSetType_U8 = m_button->whatsThis().toUInt();
//        this->database->HMiCT_RunStatSetFlag_B1 = true;
        ui->BTN9->setStyleSheet(CONFIRMPRESS);
        timer2s->start(2000);
    }
}
void MaintainceDataManagePage::hideEvent(QHideEvent *)
{
    ui->BTN9->setStyleSheet(CONFIRMRELEASE);
//    this->database->HMiCT_RunStatSetData_U32 = 0;
//    this->database->HMiCT_RunStatSetType_U8 = 0;
//    this->database->HMiCT_RunStatSetFlag_B1 = false;
    timer2s->stop();
}
