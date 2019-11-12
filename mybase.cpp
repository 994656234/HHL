#include "mybase.h"

MyBase::MyBase(QWidget *parent) :
    QWidget(parent)
{
    if (parent != NULL)
    {
        connect(this, SIGNAL(changePage(int)), parent, SLOT(changePage(int)));
    }
}

int MyBase::currentPage = uVehicleTrainArea;
Database *MyBase::database = NULL;

//uTop = 0,           //header h:62
//uStation,           //station bar h:90
//uTrain,             //train bar  h:211
//uStatus,            // status area  h:250
//uInformation,       // Information area  h:100
//uBottom,            // h:85

void MyBase::setMyBase(pagePosition position, QString name)
{
    if (position == uTop)
    {
        this->setGeometry(0, 0, this->width(), this->height());
    }
    else if (position == uStation)
    {
        this->setGeometry(0, 62, this->width(), this->height());
    }
    else if (position == uTrain)
    {
        this->setGeometry(0, 152, this->width(), this->height());
    }
    else if (position == uStatus)
    {
        this->setGeometry(0, 363, this->width(), this->height());
    }
    else if (position == uInformation)
    {
        this->setGeometry(0, 613, this->width(), this->height());
    }
    else if (position == uBottom)
    {
        this->setGeometry(0, 684, this->width(), this->height());
    }
    else if (position == uHuge)
    {
        this->setGeometry(0, 0, this->width(), this->height());
    }else if (position == uMiddle)
    {
        this->setGeometry(0, 62, this->width(), this->height());
    }
    else if (position==uTolopogy)
    {
        this->setGeometry(0,152,this->width(),this->height());
    }
    else if(position==uMainRunstatus)
    {
        this->setGeometry(0, 152, this->width(), this->height());
    }

    this->name = name;
    this->Position = position;


    this->hide();
}

void MyBase::updatePage()
{

}
