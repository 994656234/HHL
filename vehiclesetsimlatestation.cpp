#include "vehiclesetsimlatestation.h"
#include "ui_vehiclesetsimlatestation.h"
#include "qdebug.h"
#define BUTTONPRESSSTYLE "background-color:blue"
#define BUTTONRELEASESTYLE "background-color:white"

VehicleSetSimlateStation::VehicleSetSimlateStation(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleSetSimlateStation)
{
    ui->setupUi(this);
    stationChoiceBox=new StationChoiceBox(this);
    stationChoiceBox->setGeometry(230,200,555,328);
    stationChoiceBox->raise();
    stationChoiceBox->hide();
    mode=0;
    ui->lbl_jumpStation->setWordWrap(true);
    qTimer1=new QTimer(this);
    connect(qTimer1,SIGNAL(timeout()),this,SLOT(timeoutEvent1()));
    qTimer2=new QTimer(this);
    connect(qTimer2,SIGNAL(timeout()),this,SLOT(timeoutEvent2()));
    jumpStatus<<&database->DiCT_JUMP1_B1<<&database->DiCT_JUMP2_B1<<&database->DiCT_JUMP3_B1<<&database->DiCT_JUMP4_B1
             <<&database->DiCT_JUMP5_B1<<&database->DiCT_JUMP6_B1<<&database->DiCT_JUMP7_B1<<&database->DiCT_JUMP8_B1
            <<&database->DiCT_JUMP9_B1<<&database->DiCT_JUMP10_B1<<&database->DiCT_JUMP11_B1<<&database->DiCT_JUMP12_B1;
    btnGroupLine=new QButtonGroup(this);
    btnGroupLine->addButton(ui->RB_Up,0);
    btnGroupLine->addButton(ui->RB_Down,1);
    ui->RB_Up->setChecked(true);
    connect(ui->RB_Up,SIGNAL(clicked()),this,SLOT(radioButtonClick()));
    connect(ui->RB_Down,SIGNAL(clicked()),this,SLOT(radioButtonClick()));
}

VehicleSetSimlateStation::~VehicleSetSimlateStation()
{
    delete ui;
}

void VehicleSetSimlateStation::on_BTN1_pressed()
{
    changePage(uVehicleSetPage);
}

void VehicleSetSimlateStation::on_BTNHome_pressed()
{
    changePage(uVehicleTrainArea);
}

void VehicleSetSimlateStation::radioButtonClick()
{
    switch(btnGroupLine->checkedId())
    {
    case 0:
        database->DiCT_LINENUM_U8=1;
        break;
    case 1:
        database->DiCT_LINENUM_U8=2;
        break;
    }
}

void VehicleSetSimlateStation::updatePage()
{
    switch(mode)
    {
    case 1:
        currentStationName=stationChoiceBox->getName();
        ui->lbl_currentStation->setText(currentStationName);
        currentStationId=stationChoiceBox->getId();
        break;
    case 2:
        nextStationName=stationChoiceBox->getName();
        ui->lbl_nextStation->setText(nextStationName);
        nextStationId=stationChoiceBox->getId();
        break;
    case 3:
        beginStationName=stationChoiceBox->getName();
        ui->lbl_beginStation->setText(beginStationName);
        beginStationId=stationChoiceBox->getId();
        break;
    case 4:
        terminalStationName=stationChoiceBox->getName();
        ui->lbl_terminalStation->setText(terminalStationName);
        terminalStationId=stationChoiceBox->getId();
        break;
    case 5:
        QString jumpStation=stationChoiceBox->getNameList().join("、");
        ui->lbl_jumpStation->setText(jumpStation);
        for(int i=0;i<stationChoiceBox->getIdList().length();i++)
        {
            if(!jumpStationId.contains(stationChoiceBox->getIdList().at(i)))
            {
                jumpStationId.append(stationChoiceBox->getIdList().at(i));
            }
        }
        break;

    }
}

void VehicleSetSimlateStation::on_PB_currentStation_pressed()
{
    stationChoiceBox->show();
    stationChoiceBox->setStates(1);
    stationChoiceBox->clearData();
    allButtonsRelease();
    ui->PB_currentStation->setStyleSheet(BUTTONPRESSSTYLE);
    mode=1;
}

void VehicleSetSimlateStation::on_PB_nextStation_pressed()
{
    mode=2;
    stationChoiceBox->show();
    stationChoiceBox->setStates(1);
    stationChoiceBox->clearData();
    allButtonsRelease();
    ui->PB_nextStation->setStyleSheet(BUTTONPRESSSTYLE);

}

void VehicleSetSimlateStation::on_PB_beginStation_pressed()
{
    mode=3;
    stationChoiceBox->show();
    stationChoiceBox->setStates(1);
    stationChoiceBox->clearData();
    allButtonsRelease();
    ui->PB_beginStation->setStyleSheet(BUTTONPRESSSTYLE);
}

void VehicleSetSimlateStation::on_PB_terminalStation_pressed()
{
    mode=4;
    stationChoiceBox->show();
    stationChoiceBox->setStates(1);
    stationChoiceBox->clearData();
    allButtonsRelease();
    ui->PB_terminalStation->setStyleSheet(BUTTONPRESSSTYLE);

}

void VehicleSetSimlateStation::on_PB_jempStation_pressed()
{
    mode=5;
    stationChoiceBox->show();
    stationChoiceBox->setStates(2);
    stationChoiceBox->clearJumpData();
}

void VehicleSetSimlateStation::on_pushButton_pressed()
{
    database->DiCT_NOWLINENUM_U8=currentStationId;
    database->DiCT_NEXTLINENUM_U8=nextStationId;
    database->DiCT_STARTLINENUM_U8=beginStationId;
    database->DiCT_ENDLINENUM_U8=terminalStationId;
    database->DiCT_HALFATOSTART_B1=true;
    ui->pushButton->setStyleSheet(BUTTONPRESSSTYLE);
    allButtonsUnable();
    qTimer1->start(2000);
}

void VehicleSetSimlateStation::on_pushButton_2_pressed()
{
    database->DiCT_NOWLINENUM_U8=0;
    database->DiCT_NEXTLINENUM_U8=0;
    database->DiCT_STARTLINENUM_U8=0;
    database->DiCT_ENDLINENUM_U8=0;
    database->DiCT_HALFATOEND_B1=true;
    allButtonsUnable();
    qTimer1->start(2000);
    ui->pushButton_2->setStyleSheet(BUTTONPRESSSTYLE);
}

void VehicleSetSimlateStation::on_pushButton_15_pressed()
{
    for(int i=0;i<jumpStationId.length();i++)
    {
        int number=jumpStationId.at(i);
        switch(number)
        {
        case 1:
            database->DiCT_JUMP1_B1=true;
            break;
        case 2:
            database->DiCT_JUMP2_B1=true;
            break;
        case 3:
            database->DiCT_JUMP3_B1=true;
            break;
        case 4:
            database->DiCT_JUMP4_B1=true;
            break;
        case 5:
            database->DiCT_JUMP5_B1=true;
            break;
        case 6:
            database->DiCT_JUMP6_B1=true;
            break;
        case 7:
            database->DiCT_JUMP7_B1=true;
            break;
        case 8:
            database->DiCT_JUMP8_B1=true;
            break;
        case 9:
            database->DiCT_JUMP9_B1=true;
            break;
        case 10:
            database->DiCT_JUMP10_B1=true;
            break;
        case 11:
            database->DiCT_JUMP11_B1=true;
            break;
        case 12:
            database->DiCT_JUMP12_B1=true;
            break;
        }
    }
    database->DiCT_JUMPSET_B1=true;
    ui->pushButton_15->setStyleSheet(BUTTONPRESSSTYLE);
    allButtonsUnable();
    qTimer2->start(2000);
}

void VehicleSetSimlateStation::on_pushButton_16_pressed()
{
    for(int i=0;i<jumpStationId.length();i++){
        int number=jumpStationId.at(i);
        switch(number)
        {
        case 1:
            database->DiCT_JUMP1_B1=false;
            break;
        case 2:
            database->DiCT_JUMP2_B1=false;
            break;
        case 3:
            database->DiCT_JUMP3_B1=false;
            break;
        case 4:
            database->DiCT_JUMP4_B1=false;
            break;
        case 5:
            database->DiCT_JUMP5_B1=false;
            break;
        case 6:
            database->DiCT_JUMP6_B1=false;
            break;
        case 7:
            database->DiCT_JUMP7_B1=false;
            break;
        case 8:
            database->DiCT_JUMP8_B1=false;
            break;
        case 9:
            database->DiCT_JUMP9_B1=false;
            break;
        case 10:
            database->DiCT_JUMP10_B1=false;
            break;
        case 11:
            database->DiCT_JUMP11_B1=false;
            break;
        case 12:
            database->DiCT_JUMP12_B1=false;
            break;
        }
    }

    database->DiCT_JUMPCANCEL_B1=true;
    ui->lbl_jumpStation->setText("");
    jumpStationId.clear();
    stationChoiceBox->clearJumpData();
    ui->pushButton_16->setStyleSheet(BUTTONPRESSSTYLE);
    allButtonsUnable();
    qTimer2->start(2000);
}

void VehicleSetSimlateStation::timeoutEvent1()
{
    database->DiCT_HALFATOSTART_B1=false;
    database->DiCT_HALFATOEND_B1=false;
    ui->pushButton->setStyleSheet(BUTTONRELEASESTYLE);
    ui->pushButton_2->setStyleSheet(BUTTONRELEASESTYLE);
    allButtonsEnable();
}

void VehicleSetSimlateStation::timeoutEvent2()
{
    database->DiCT_JUMPSET_B1=false;
    database->DiCT_JUMPCANCEL_B1=false;
    ui->pushButton_15->setStyleSheet(BUTTONRELEASESTYLE);
    ui->pushButton_16->setStyleSheet(BUTTONRELEASESTYLE);
    allButtonsEnable();
}

void VehicleSetSimlateStation::allButtonsRelease()
{
    ui->PB_beginStation->setStyleSheet(BUTTONRELEASESTYLE);
    ui->PB_currentStation->setStyleSheet(BUTTONRELEASESTYLE);
    ui->PB_nextStation->setStyleSheet(BUTTONRELEASESTYLE);
    ui->PB_terminalStation->setStyleSheet(BUTTONRELEASESTYLE);
}

void VehicleSetSimlateStation::allButtonsUnable()
{
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_15->setEnabled(false);
    ui->pushButton_16->setEnabled(false);
}

void VehicleSetSimlateStation::allButtonsEnable()
{
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_15->setEnabled(true);
    ui->pushButton_16->setEnabled(true);
}
