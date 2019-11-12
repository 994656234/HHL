#include "vehicledoorpage.h"
#include "ui_vehicledoorpage.h"
#include "qdebug.h"

#define  DOOREMGUNLOCK "border-image: url(:/images/image/dooreMergencyRelease.png);"
#define  DOORCUTOFF "border-image: url(:/images/image/doorcutoff.png);"
#define  DOORFAULT "border-image: url(:/images/image/doorfault.png);"
#define  DOOROBS "border-image: url(:/images/image/doorobs.png);"
#define  DOOROPEN "background-color: rgb(255, 255, 127);"
#define  DOORCLOSE "background-color: rgb(34, 177, 76);"
#define  DOORUNKNOW "border-image: url(:/images/image/doorunknow.png);"
#define  DOOREMOPENP "border-image: url(:/images/image/emergencyopen.png);"

VehicleDoorPage::VehicleDoorPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleDoorPage)
{
    ui->setupUi(this);
    ui->lbl_cab1_active->hide();
    ui->lbl_cab1_direction->hide();
    ui->lbl_cab2_active->hide();
    ui->lbl_cab2_direction->hide();
}

VehicleDoorPage::~VehicleDoorPage()
{
    delete ui;
}

void VehicleDoorPage::updatePage()
{

    //车门
    //车门
    //MC1
    DOORstatus.clear();
    DOORstatus<<this->database->EDCU1_2CT_DOOR174_B1<<this->database->EDCU1_2CT_DOOR167_B1<<this->database->EDCU1_2CT_DOOR168_B1
             <<this->database->EDCU1_2CT_DOOR171_B1<<this->database->EDCU1_2CT_DOOR169_B1<<this->database->EDCU1_2CT_DOOR166_B1
            <<this->database->EDCU1_2CT_DOOR165_B1;
    setDoorStatus(ui->lbl_door1_1,DOORstatus);
    DOORstatus.clear();

    DOORstatus<<this->database->EDCU1_2CT_DOOR190_B1<<this->database->EDCU1_2CT_DOOR183_B1<<this->database->EDCU1_2CT_DOOR184_B1
            <<this->database->EDCU1_2CT_DOOR187_B1<<this->database->EDCU1_2CT_DOOR185_B1
            <<this->database->EDCU1_2CT_DOOR182_B1<<this->database->EDCU1_2CT_DOOR181_B1;
    setDoorStatus(ui->lbl_door1_2,DOORstatus);
    DOORstatus.clear();

    DOORstatus<<this->database->EDCU1_2CT_DOOR206_B1<<this->database->EDCU1_2CT_DOOR199_B1<<this->database->EDCU1_2CT_DOOR200_B1
            <<this->database->EDCU1_2CT_DOOR203_B1<<this->database->EDCU1_2CT_DOOR201_B1
            <<this->database->EDCU1_2CT_DOOR198_B1<<this->database->EDCU1_2CT_DOOR197_B1;
    setDoorStatus(ui->lbl_door1_3,DOORstatus);
    DOORstatus.clear();

    DOORstatus<<this->database->EDCU1_2CT_DOOR222_B1<<this->database->EDCU1_2CT_DOOR215_B1<<this->database->EDCU1_2CT_DOOR216_B1
            <<this->database->EDCU1_2CT_DOOR219_B1<<this->database->EDCU1_2CT_DOOR217_B1
            <<this->database->EDCU1_2CT_DOOR214_B1<<this->database->EDCU1_2CT_DOOR213_B1;
    setDoorStatus(ui->lbl_door1_4,DOORstatus);
    DOORstatus.clear();

    DOORstatus<<this->database->EDCU1_2CT_DOOR238_B1<<this->database->EDCU1_2CT_DOOR231_B1<<this->database->EDCU1_2CT_DOOR232_B1
            <<this->database->EDCU1_2CT_DOOR235_B1<<this->database->EDCU1_2CT_DOOR233_B1
            <<this->database->EDCU1_2CT_DOOR230_B1<<this->database->EDCU1_2CT_DOOR229_B1;
    setDoorStatus(ui->lbl_door1_5,DOORstatus);
    DOORstatus.clear();

    DOORstatus<<this->database->EDCU1_2CT_DOOR254_B1<<this->database->EDCU1_2CT_DOOR247_B1<<this->database->EDCU1_2CT_DOOR248_B1
            <<this->database->EDCU1_2CT_DOOR251_B1<<this->database->EDCU1_2CT_DOOR249_B1
            <<this->database->EDCU1_2CT_DOOR246_B1<<this->database->EDCU1_2CT_DOOR245_B1;
    setDoorStatus(ui->lbl_door1_6,DOORstatus);
    DOORstatus.clear();


    //Mp1
    DOORstatus.clear();
    DOORstatus<<this->database->EDCU3_4CT_DOOR174_B1<<this->database->EDCU3_4CT_DOOR167_B1<<this->database->EDCU3_4CT_DOOR168_B1
             <<this->database->EDCU3_4CT_DOOR171_B1<<this->database->EDCU3_4CT_DOOR169_B1<<this->database->EDCU3_4CT_DOOR166_B1
            <<this->database->EDCU3_4CT_DOOR165_B1;
    setDoorStatus(ui->lbl_door1_1,DOORstatus);
    DOORstatus.clear();

    DOORstatus<<this->database->EDCU3_4CT_DOOR190_B1<<this->database->EDCU3_4CT_DOOR183_B1<<this->database->EDCU3_4CT_DOOR184_B1
            <<this->database->EDCU3_4CT_DOOR187_B1<<this->database->EDCU3_4CT_DOOR185_B1
            <<this->database->EDCU3_4CT_DOOR182_B1<<this->database->EDCU3_4CT_DOOR181_B1;
    setDoorStatus(ui->lbl_door1_2,DOORstatus);
    DOORstatus.clear();

    DOORstatus<<this->database->EDCU3_4CT_DOOR206_B1<<this->database->EDCU3_4CT_DOOR199_B1<<this->database->EDCU3_4CT_DOOR200_B1
            <<this->database->EDCU3_4CT_DOOR203_B1<<this->database->EDCU3_4CT_DOOR201_B1
            <<this->database->EDCU3_4CT_DOOR198_B1<<this->database->EDCU3_4CT_DOOR197_B1;
    setDoorStatus(ui->lbl_door1_3,DOORstatus);
    DOORstatus.clear();

    DOORstatus<<this->database->EDCU3_4CT_DOOR222_B1<<this->database->EDCU3_4CT_DOOR215_B1<<this->database->EDCU3_4CT_DOOR216_B1
            <<this->database->EDCU3_4CT_DOOR219_B1<<this->database->EDCU3_4CT_DOOR217_B1
            <<this->database->EDCU3_4CT_DOOR214_B1<<this->database->EDCU3_4CT_DOOR213_B1;
    setDoorStatus(ui->lbl_door1_4,DOORstatus);
    DOORstatus.clear();

    DOORstatus<<this->database->EDCU3_4CT_DOOR238_B1<<this->database->EDCU3_4CT_DOOR231_B1<<this->database->EDCU3_4CT_DOOR232_B1
            <<this->database->EDCU3_4CT_DOOR235_B1<<this->database->EDCU3_4CT_DOOR233_B1
            <<this->database->EDCU3_4CT_DOOR230_B1<<this->database->EDCU3_4CT_DOOR229_B1;
    setDoorStatus(ui->lbl_door1_5,DOORstatus);
    DOORstatus.clear();

    DOORstatus<<this->database->EDCU3_4CT_DOOR254_B1<<this->database->EDCU3_4CT_DOOR247_B1<<this->database->EDCU3_4CT_DOOR248_B1
            <<this->database->EDCU3_4CT_DOOR251_B1<<this->database->EDCU3_4CT_DOOR249_B1
            <<this->database->EDCU3_4CT_DOOR246_B1<<this->database->EDCU3_4CT_DOOR245_B1;
    setDoorStatus(ui->lbl_door1_6,DOORstatus);
    DOORstatus.clear();


    //MP2
    DOORstatus.clear();
    DOORstatus<<this->database->EDCU5_6CT_DOOR174_B1<<this->database->EDCU5_6CT_DOOR167_B1<<this->database->EDCU5_6CT_DOOR168_B1
             <<this->database->EDCU5_6CT_DOOR171_B1<<this->database->EDCU5_6CT_DOOR169_B1<<this->database->EDCU5_6CT_DOOR166_B1
            <<this->database->EDCU5_6CT_DOOR165_B1;
    setDoorStatus(ui->lbl_door1_1,DOORstatus);
    DOORstatus.clear();

    DOORstatus<<this->database->EDCU5_6CT_DOOR190_B1<<this->database->EDCU5_6CT_DOOR183_B1<<this->database->EDCU5_6CT_DOOR184_B1
            <<this->database->EDCU5_6CT_DOOR187_B1<<this->database->EDCU5_6CT_DOOR185_B1
            <<this->database->EDCU5_6CT_DOOR182_B1<<this->database->EDCU5_6CT_DOOR181_B1;
    setDoorStatus(ui->lbl_door1_2,DOORstatus);
    DOORstatus.clear();

    DOORstatus<<this->database->EDCU5_6CT_DOOR206_B1<<this->database->EDCU5_6CT_DOOR199_B1<<this->database->EDCU5_6CT_DOOR200_B1
            <<this->database->EDCU5_6CT_DOOR203_B1<<this->database->EDCU5_6CT_DOOR201_B1
            <<this->database->EDCU5_6CT_DOOR198_B1<<this->database->EDCU5_6CT_DOOR197_B1;
    setDoorStatus(ui->lbl_door1_3,DOORstatus);
    DOORstatus.clear();

    DOORstatus<<this->database->EDCU5_6CT_DOOR222_B1<<this->database->EDCU5_6CT_DOOR215_B1<<this->database->EDCU5_6CT_DOOR216_B1
            <<this->database->EDCU5_6CT_DOOR219_B1<<this->database->EDCU5_6CT_DOOR217_B1
            <<this->database->EDCU5_6CT_DOOR214_B1<<this->database->EDCU5_6CT_DOOR213_B1;
    setDoorStatus(ui->lbl_door1_4,DOORstatus);
    DOORstatus.clear();

    DOORstatus<<this->database->EDCU5_6CT_DOOR238_B1<<this->database->EDCU5_6CT_DOOR231_B1<<this->database->EDCU5_6CT_DOOR232_B1
            <<this->database->EDCU5_6CT_DOOR235_B1<<this->database->EDCU5_6CT_DOOR233_B1
            <<this->database->EDCU5_6CT_DOOR230_B1<<this->database->EDCU5_6CT_DOOR229_B1;
    setDoorStatus(ui->lbl_door1_5,DOORstatus);
    DOORstatus.clear();

    DOORstatus<<this->database->EDCU5_6CT_DOOR254_B1<<this->database->EDCU5_6CT_DOOR247_B1<<this->database->EDCU5_6CT_DOOR248_B1
            <<this->database->EDCU5_6CT_DOOR251_B1<<this->database->EDCU5_6CT_DOOR249_B1
            <<this->database->EDCU5_6CT_DOOR246_B1<<this->database->EDCU5_6CT_DOOR245_B1;
    setDoorStatus(ui->lbl_door1_6,DOORstatus);
    DOORstatus.clear();
    //MC2
    DOORstatus.clear();
    DOORstatus<<this->database->EDCU7_8CT_DOOR174_B1<<this->database->EDCU7_8CT_DOOR167_B1<<this->database->EDCU7_8CT_DOOR168_B1
             <<this->database->EDCU7_8CT_DOOR171_B1<<this->database->EDCU7_8CT_DOOR169_B1<<this->database->EDCU7_8CT_DOOR166_B1
            <<this->database->EDCU7_8CT_DOOR165_B1;
    setDoorStatus(ui->lbl_door1_1,DOORstatus);
    DOORstatus.clear();

    DOORstatus<<this->database->EDCU7_8CT_DOOR190_B1<<this->database->EDCU7_8CT_DOOR183_B1<<this->database->EDCU7_8CT_DOOR184_B1
            <<this->database->EDCU7_8CT_DOOR187_B1<<this->database->EDCU7_8CT_DOOR185_B1
            <<this->database->EDCU7_8CT_DOOR182_B1<<this->database->EDCU7_8CT_DOOR181_B1;
    setDoorStatus(ui->lbl_door1_2,DOORstatus);
    DOORstatus.clear();

    DOORstatus<<this->database->EDCU7_8CT_DOOR206_B1<<this->database->EDCU7_8CT_DOOR199_B1<<this->database->EDCU7_8CT_DOOR200_B1
            <<this->database->EDCU7_8CT_DOOR203_B1<<this->database->EDCU7_8CT_DOOR201_B1
            <<this->database->EDCU7_8CT_DOOR198_B1<<this->database->EDCU7_8CT_DOOR197_B1;
    setDoorStatus(ui->lbl_door1_3,DOORstatus);
    DOORstatus.clear();

    DOORstatus<<this->database->EDCU7_8CT_DOOR222_B1<<this->database->EDCU7_8CT_DOOR215_B1<<this->database->EDCU7_8CT_DOOR216_B1
            <<this->database->EDCU7_8CT_DOOR219_B1<<this->database->EDCU7_8CT_DOOR217_B1
            <<this->database->EDCU7_8CT_DOOR214_B1<<this->database->EDCU7_8CT_DOOR213_B1;
    setDoorStatus(ui->lbl_door1_4,DOORstatus);
    DOORstatus.clear();

    DOORstatus<<this->database->EDCU7_8CT_DOOR238_B1<<this->database->EDCU7_8CT_DOOR231_B1<<this->database->EDCU7_8CT_DOOR232_B1
            <<this->database->EDCU7_8CT_DOOR235_B1<<this->database->EDCU7_8CT_DOOR233_B1
            <<this->database->EDCU7_8CT_DOOR230_B1<<this->database->EDCU7_8CT_DOOR229_B1;
    setDoorStatus(ui->lbl_door1_5,DOORstatus);
    DOORstatus.clear();

    DOORstatus<<this->database->EDCU7_8CT_DOOR254_B1<<this->database->EDCU7_8CT_DOOR247_B1<<this->database->EDCU7_8CT_DOOR248_B1
            <<this->database->EDCU7_8CT_DOOR251_B1<<this->database->EDCU7_8CT_DOOR249_B1
            <<this->database->EDCU7_8CT_DOOR246_B1<<this->database->EDCU7_8CT_DOOR245_B1;
    setDoorStatus(ui->lbl_door1_6,DOORstatus);
    DOORstatus.clear();



}

void VehicleDoorPage::setDoorStatus(QLabel *label, QList<bool> status)
{
    if(status.at(0))
    {
        label->setStyleSheet(DOOREMOPENP);
    }
    else if(status.at(1))
    {
        label->setStyleSheet(DOOREMGUNLOCK);
    }
    else if(status.at(2))
    {
        label->setStyleSheet(DOORCUTOFF);
    }
    else if(status.at(3))
    {
        label->setStyleSheet(DOORFAULT);
    }
    else if(status.at(4))
    {
        label->setStyleSheet(DOOROBS);
    }
    else if(status.at(5))
    {
        label->setStyleSheet(DOOROPEN);
    }
    else if(status.at(6))
    {
        label->setStyleSheet(DOORCLOSE);
    }
    else
    {
        label->setStyleSheet(DOORUNKNOW);
    }
}
