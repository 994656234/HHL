#include "stationchoicebox.h"
#include "ui_stationchoicebox.h"
#define BUTTONPRESSSTYLE "background-color:blue"
#define BUTTONRELEASESTYLE "background-color:white"

StationChoiceBox::StationChoiceBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StationChoiceBox)
{
    ui->setupUi(this);
    butons<<ui->PB_Station_1<<ui->PB_Station_2<<ui->PB_Station_3<<ui->PB_Station_4<<ui->PB_Station_5
         <<ui->PB_Station_6<<ui->PB_Station_7<<ui->PB_Station_8<<ui->PB_Station_9<<ui->PB_Station_10
        <<ui->PB_Station_11<<ui->PB_Station_12<<ui->PB_Cancel;
    foreach (QPushButton *button, butons) {
        connect(button,SIGNAL(pressed()),this,SLOT(buttonsPressedEvnet()));
    }

}

StationChoiceBox::~StationChoiceBox()
{
    delete ui;
}

void StationChoiceBox::setStates(int states)
{
    this->state=states;
}

void StationChoiceBox::buttonsPressedEvnet()
{
    if(this->state==1)
    {
        allButtonrelease();
    }
    int number=((QPushButton*)this->sender())->whatsThis().toInt();
    ((QPushButton*)this->sender())->setStyleSheet(BUTTONPRESSSTYLE);
    switch(number)
    {
    case 1:
        id=1;
        name="余杭高铁站";
        if(!idList.contains(1))
        {
            idList.append(1);
            nameList.append("余杭高铁站");
        }
        else
        {
            idList.removeAt(idList.indexOf(1));
            nameList.removeAt(nameList.indexOf("余杭高铁站"));
            ((QPushButton*)this->sender())->setStyleSheet(BUTTONRELEASESTYLE);
        }
        break;
    case 2:
        id=2;
        name="许村站";
        if(!idList.contains(2))
        {
            idList.append(2);
            nameList.append("许村站");
        }
        else
        {
            idList.removeAt(idList.indexOf(2));
            nameList.removeAt(nameList.indexOf("许村站"));
            ((QPushButton*)this->sender())->setStyleSheet(BUTTONRELEASESTYLE);
        }
        break;
    case 3:
        id=3;
        name="海宁高铁西站";
        if(!idList.contains(3))
        {
            idList.append(3);
            nameList.append("海宁高铁西站");
        }
        else
        {
            idList.removeAt(idList.indexOf(3));
            nameList.removeAt(nameList.indexOf("海宁高铁西站"));
            ((QPushButton*)this->sender())->setStyleSheet(BUTTONRELEASESTYLE);
        }
        break;
    case 4:
        id=4;
        name="长安站";
        if(!idList.contains(4))
        {
            idList.append(4);
            nameList.append("长安站");
        }
        else
        {
            idList.removeAt(idList.indexOf(4));
            nameList.removeAt(nameList.indexOf("长安站"));
            ((QPushButton*)this->sender())->setStyleSheet(BUTTONRELEASESTYLE);
        }
        break;
    case 5:
        id=5;
        name="长安东站";
        if(!idList.contains(5))
        {
            idList.append(5);
            nameList.append("长安东站");
        }
        else
        {
            idList.removeAt(idList.indexOf(5));
            nameList.removeAt(nameList.indexOf("长安东站"));
            ((QPushButton*)this->sender())->setStyleSheet(BUTTONRELEASESTYLE);
        }
        break;
    case 6:
        id=6;
        name="周王庙站";
        if(!idList.contains(6))
        {
            idList.append(6);
            nameList.append("周王庙站");
        }
        else
        {
            idList.removeAt(idList.indexOf(6));
            nameList.removeAt(nameList.indexOf("周王庙站"));
            ((QPushButton*)this->sender())->setStyleSheet(BUTTONRELEASESTYLE);
        }
        break;
    case 7:
        id=7;
        name="盐官站";
        if(!idList.contains(7))
        {
            idList.append(7);
            nameList.append("盐官站");
        }
        else
        {
            idList.removeAt(idList.indexOf(7));
            nameList.removeAt(nameList.indexOf("盐官站"));
            ((QPushButton*)this->sender())->setStyleSheet(BUTTONRELEASESTYLE);
        }
        break;
    case 8:
        id=8;
        name="桐九公路站";
        if(!idList.contains(8))
        {
            idList.append(8);
            nameList.append("桐九公路站");
        }
        else
        {
            idList.removeAt(idList.indexOf(8));
            nameList.removeAt(nameList.indexOf("桐九公路站"));
            ((QPushButton*)this->sender())->setStyleSheet(BUTTONRELEASESTYLE);
        }
        break;
    case 9:
        id=9;
        name="斜桥站";
        if(!idList.contains(9))
        {
            idList.append(9);
            nameList.append("斜桥站");
        }
        else
        {
            idList.removeAt(idList.indexOf(9));
            nameList.removeAt(nameList.indexOf("斜桥站"));
            ((QPushButton*)this->sender())->setStyleSheet(BUTTONRELEASESTYLE);
        }
        break;
    case 10:
        id=10;
        name="皮革城站";
        if(!idList.contains(10))
        {
            idList.append(10);
            nameList.append("皮革城站");
        }
        else
        {
            idList.removeAt(idList.indexOf(10));
            nameList.removeAt(nameList.indexOf("皮革城站"));
            ((QPushButton*)this->sender())->setStyleSheet(BUTTONRELEASESTYLE);
        }
        break;
    case 11:
        id=11;
        name="海昌路站";
        if(!idList.contains(11))
        {
            idList.append(11);
            nameList.append("海昌路站");
        }
        else
        {
            idList.removeAt(idList.indexOf(11));
            nameList.removeAt(nameList.indexOf("海昌路站"));
            ((QPushButton*)this->sender())->setStyleSheet(BUTTONRELEASESTYLE);
        }
        break;
    case 12:
        id=12;
        name="浙大国际校区站";
        if(!idList.contains(12))
        {
            idList.append(12);
            nameList.append("浙大国际校区站");
        }
        else
        {
            idList.removeAt(idList.indexOf(12));
            nameList.removeAt(nameList.indexOf("浙大国际校区站"));
            ((QPushButton*)this->sender())->setStyleSheet(BUTTONRELEASESTYLE);
        }
        break;
    case 13:
        this->close();
        allButtonrelease();
        break;
    }
}


void StationChoiceBox::allButtonrelease()
{
    foreach (QPushButton* button, this->butons) {
        button->setStyleSheet(BUTTONRELEASESTYLE);
    }
}

int StationChoiceBox::getId()
{
    return this->id;
}

QString StationChoiceBox::getName()
{
    return this->name;
}

QList<int> StationChoiceBox::getIdList()
{
    return this->idList;
}

QList<QString> StationChoiceBox::getNameList()
{
    return this->nameList;
}

void StationChoiceBox::clearData()
{
    id=0;
    name="";
}

void StationChoiceBox::clearJumpData()
{
    idList.clear();
    nameList.clear();
}
