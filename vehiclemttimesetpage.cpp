#include "vehiclemttimesetpage.h"
#include "ui_vehiclemttimesetpage.h"
#include "qdebug.h"
#define  BUTTONPRESS "background-color: rgb(255, 255, 255);font: 24px, \"微软雅黑\";color: rgb(0, 0, 0);"
#define  BUTTONRELEASE "background-color: rgb(0, 0, 0);font: 24px, \"微软雅黑\";color: rgb(255, 255, 255);"

#define MAKESUREPRESS "	font: 20px, \"微软雅黑\";color: black;background-color:blue;"
#define MAKESURERELEASE "font: 20px, \"微软雅黑\";color: black;transparent;background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 rgba(170,170,170,255),stop:1 rgba(150,150,150,255));"

VehicleMTTimeSetPage::VehicleMTTimeSetPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleMTTimeSetPage)
{
    ui->setupUi(this);
    QDate current_date=QDate::currentDate();
    QString year=QString::number(current_date.year()%100,10);
    QString month=QString::number(current_date.month(),10);
    QString day=QString::number(current_date.day(),10);
    QTime current_time=QTime::currentTime();
    QString hour=QString::number(current_time.hour(),10);
    QString minute=QString::number(current_time.minute(),10);
    QString second=QString::number(current_time.second(),10);
    ui->BTN_year->setText(year);
    ui->BTN_month->setText(month);
    ui->BTN_day->setText(day);
    ui->BTN_hour->setText(hour);
    ui->BTN_minute->setText(minute);
    ui->BTN_second->setText(second);
    //ui->BTNNumClear->hide();
    ui->BTN9OK22->hide();

    database->DiCT_SetFlagChecker_U8=0x55;

    time2s=new QTimer(this);
    connect(time2s,SIGNAL(timeout()),this,SLOT(setTimeEnd()));
    buttons<<ui->BTN1back<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5<<ui->BTN6<<ui->BTN7<<ui->BTN8<<ui->BTN9OK<<ui->BTNHome
            <<ui->BTNNum0<<ui->BTNNum1<<ui->BTNNum2<<ui->BTNNum3<<ui->BTNNum4<<ui->BTNNum5<<ui->BTNNum6<<ui->BTNNum7<<ui->BTNNum8
            <<ui->BTNNum9<<ui->BTNNumC<<ui->BTNNumClear<<ui->BTN_day<<ui->BTN_hour<<ui->BTN_minute<<ui->BTN_month<<ui->BTN_second
            <<ui->BTN_year;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(NBpressEvent()));
    }
}

VehicleMTTimeSetPage::~VehicleMTTimeSetPage()
{
    delete ui;
}

void VehicleMTTimeSetPage::NBpressEvent()
{
    QString BTNName=((QPushButton*)this->sender())->objectName();
    if(BTNName=="BTN1back")
    {
        time2s->stop();
        database->DiCT_SAVETime_B1=false;
        database->DiCT_SetFlagChecker_U8=0x55;
        changePage(uVehicleSetPage);
    }
    else if(BTNName=="BTNHome")
    {
        time2s->stop();
        database->DiCT_SAVETime_B1=false;
        database->DiCT_SetFlagChecker_U8=0x55;
        changePage(uVehicleTrainArea);
    }
    else if(BTNName=="BTN9OK")
    {
        database->DiCT_Year_U8=(unsigned char)ui->BTN_year->text().toInt();
        database->DiCT_Month_U8=(unsigned char)ui->BTN_month->text().toInt();
        database->DiCT_Day_U8=(unsigned char)ui->BTN_day->text().toInt();
        database->DiCT_Hour_U8=(unsigned char)ui->BTN_hour->text().toInt();
        database->DiCT_Minute_U8=(unsigned char)ui->BTN_minute->text().toInt();
        database->DiCT_Second_U8=(unsigned char)ui->BTN_second->text().toInt();

        database->DiCT_SAVETime_B1=true;
        database->DiCT_SetFlagChecker_U8=0xAA;
        ui->BTN9OK->setStyleSheet(MAKESUREPRESS);
        time2s->start(2000);

    }
    else if(BTNName=="BTN_year")
    {
        ui->BTN9OK->setText("确定");
        allButtonRelease();
        ui->BTN_year->setStyleSheet(BUTTONPRESS);
        currentNum=nYear;
        ui->BTN_year->setText("");
    }
    else if(BTNName=="BTN_month")
    {
        allButtonRelease();
        ui->BTN_month->setStyleSheet(BUTTONPRESS);
        currentNum=nMonth;
        ui->BTN_month->setText("");
    }
    else if(BTNName=="BTN_day")
    {
        allButtonRelease();
        ui->BTN_day->setStyleSheet(BUTTONPRESS);
        currentNum=nDay;
        ui->BTN_day->setText("");
    }
    else if(BTNName=="BTN_hour")
    {
        allButtonRelease();
        ui->BTN_hour->setStyleSheet(BUTTONPRESS);
        currentNum=nHour;
        ui->BTN_hour->setText("");
    }
    else if(BTNName=="BTN_minute")
    {
        allButtonRelease();
        ui->BTN_minute->setStyleSheet(BUTTONPRESS);
        currentNum=nMinute;
        ui->BTN_minute->setText("");
    }
    else if(BTNName=="BTN_second")
    {
        allButtonRelease();
        ui->BTN_second->setStyleSheet(BUTTONPRESS);
        currentNum=nSecond;
        ui->BTN_second->setText("");
    }
    else if(BTNName=="BTNNum0")
    {
        switch(currentNum)
        {
            case nYear:
                if(ui->BTN_year->text().length()<2)
                {
                    ui->BTN_year->setText(ui->BTN_year->text()+"0");
                }
                else
                {}
                break;
            case nMonth:
                if(ui->BTN_month->text().length()==0)
                {
                    ui->BTN_month->setText(ui->BTN_month->text()+"0");
                }
                else if(ui->BTN_month->text().length()==1)
                {
                    if(ui->BTN_month->text().toInt()<=1)
                    {
                        ui->BTN_month->setText(ui->BTN_month->text()+"0");
                    }
                    else
                    {}
                }
                else
                {}
                break;
             case nDay:
                if(ui->BTN_day->text().length()==0)
                {
                    ui->BTN_day->setText(ui->BTN_day->text()+"0");
                }
                else if(ui->BTN_day->text().length()==1)
                {
                    if(ui->BTN_day->text().toInt()<=3)
                    {
                        ui->BTN_day->setText(ui->BTN_day->text()+"0");
                    }
                    else
                    {}
                }
                else
                {}
                break;
             case nHour:
                if(ui->BTN_hour->text().length()==0)
                {
                    ui->BTN_hour->setText(ui->BTN_hour->text()+"0");
                }
                else if(ui->BTN_hour->text().length()==1)
                {
                    if(ui->BTN_hour->text().toInt()<=2)
                    {
                        ui->BTN_hour->setText(ui->BTN_hour->text()+"0");
                    }
                    else
                    {}
                }
                else
                {}
                break;
             case nMinute:
                if(ui->BTN_minute->text().length()==0)
                {
                    ui->BTN_minute->setText(ui->BTN_minute->text()+"0");
                }
                else if(ui->BTN_minute->text().length()==1)
                {
                    if(ui->BTN_minute->text().toInt()<=6)
                    {
                        ui->BTN_minute->setText(ui->BTN_minute->text()+"0");
                    }
                    else
                    {}
                }
                else
                {}
                break;
             case nSecond:
                if(ui->BTN_second->text().length()==0)
                {
                    ui->BTN_second->setText(ui->BTN_second->text()+"0");
                }
                else if(ui->BTN_second->text().length()==1)
                {
                    if(ui->BTN_second->text().toInt()<=6)
                    {
                        ui->BTN_second->setText(ui->BTN_second->text()+"0");
                    }
                    else
                    {}
                }
                else
                {}
                break;
        }        
    }
    else if(BTNName=="BTNNum1")
    {
        switch(currentNum)
        {
        case nYear:
            if(ui->BTN_year->text().length()<2)
            {
                ui->BTN_year->setText(ui->BTN_year->text()+"1");
            }
            else
            {}
            break;
        case nMonth:
            if(ui->BTN_month->text().length()==0)
            {
                ui->BTN_month->setText(ui->BTN_month->text()+"1");
            }
            else if(ui->BTN_month->text().length()==1)
            {
                if(ui->BTN_month->text().toInt()<=1)
                {
                    ui->BTN_month->setText(ui->BTN_month->text()+"1");
                }
                else
                {}
            }
            else
            {}
            break;
        case nDay:
            if(ui->BTN_day->text().length()==0)
            {
                ui->BTN_day->setText(ui->BTN_day->text()+"1");
            }
            else if(ui->BTN_day->text().length()==1)
            {
                if(ui->BTN_day->text().toInt()<=3)
                {
                    ui->BTN_day->setText(ui->BTN_day->text()+"1");
                }
                else
                {}
            }
            else
            {}
            break;
        case nHour:
            if(ui->BTN_hour->text().length()==0)
            {
                ui->BTN_hour->setText(ui->BTN_hour->text()+"1");
            }
            else if(ui->BTN_hour->text().length()==1)
            {
                if(ui->BTN_hour->text().toInt()<=2)
                {
                    ui->BTN_hour->setText(ui->BTN_hour->text()+"1");
                }
                else
                {}
            }
            else
            {}
            break;
        case nMinute:
            if(ui->BTN_minute->text().length()==0)
            {
                ui->BTN_minute->setText(ui->BTN_minute->text()+"1");
            }
            else if(ui->BTN_minute->text().length()==1)
            {
                if(ui->BTN_minute->text().toInt()<6)
                {
                    ui->BTN_minute->setText(ui->BTN_minute->text()+"1");
                }
                else
                {}
            }
            else
            {}
            break;
        case nSecond:
            if(ui->BTN_second->text().length()==0)
            {
                ui->BTN_second->setText(ui->BTN_second->text()+"1");
            }
            else if(ui->BTN_second->text().length()==1)
            {
                if(ui->BTN_second->text().toInt()<6)
                {
                    ui->BTN_second->setText(ui->BTN_second->text()+"1");
                }
                else
                {}
            }
            else
            {}
            break;
        }
    }   
    else if(BTNName=="BTNNum2")
        {
            switch(currentNum)
            {
            case nYear:
                if(ui->BTN_year->text().length()<2)
                {
                    ui->BTN_year->setText(ui->BTN_year->text()+"2");
                }
                else
                {}
                break;
            case nMonth:
                if(ui->BTN_month->text().length()==0)
                {
                    ui->BTN_month->setText(ui->BTN_month->text()+"2");
                }
                else if(ui->BTN_month->text().length()==1)
                {
                    if(ui->BTN_month->text().toInt()<2)
                    {
                        ui->BTN_month->setText(ui->BTN_month->text()+"2");
                    }
                    else
                    {}
                }
                break;
             case nDay:
                if(ui->BTN_day->text().length()==0)
                {
                    ui->BTN_day->setText(ui->BTN_day->text()+"2");
                }
                else if(ui->BTN_day->text().length()==1)
                {
                    if(ui->BTN_day->text().toInt()<3)
                    {
                        ui->BTN_day->setText(ui->BTN_day->text()+"2");
                    }
                    else
                    {}
                }
                else
                {}
                break;
             case nHour:
                if(ui->BTN_hour->text().length()==0)
                {
                    ui->BTN_hour->setText(ui->BTN_hour->text()+"2");
                }
                else if(ui->BTN_hour->text().length()==1)
                {
                    if(ui->BTN_hour->text().toInt()<=2)
                    {
                        ui->BTN_hour->setText(ui->BTN_hour->text()+"2");
                    }
                    else
                    {}
                }
                else
                {}
                break;
             case nMinute:
                if(ui->BTN_minute->text().length()==0)
                {
                    ui->BTN_minute->setText(ui->BTN_minute->text()+"2");
                }
                else if(ui->BTN_minute->text().length()==1)
                {
                    if(ui->BTN_minute->text().toInt()<6)
                    {
                        ui->BTN_minute->setText(ui->BTN_minute->text()+"2");
                    }
                    else
                    {}
                }
                else
                {}
                break;
             case nSecond:
                if(ui->BTN_second->text().length()==0)
                {
                    ui->BTN_second->setText(ui->BTN_second->text()+"2");
                }
                else if(ui->BTN_second->text().length()==1)
                {
                    if(ui->BTN_second->text().toInt()<6)
                    {
                        ui->BTN_second->setText(ui->BTN_second->text()+"2");
                    }
                    else
                    {}
                }
                else
                {}
                break;
              }
            }
    else if(BTNName=="BTNNum3")
            {
                switch(currentNum)
                {
                case nYear:
                    if(ui->BTN_year->text().length()<2)
                    {
                        ui->BTN_year->setText(ui->BTN_year->text()+"3");
                    }
                    else
                    {}
                    break;
                 case nMonth:
                    if(ui->BTN_month->text().length()==0)
                    {
                        ui->BTN_month->setText(ui->BTN_month->text()+"3");
                    }
                    else if(ui->BTN_month->text().length()==1)
                    {
                        if(ui->BTN_month->text().toInt()==0)
                        {
                            ui->BTN_month->setText(ui->BTN_month->text()+"3");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nDay:
                    if(ui->BTN_day->text().length()==0)
                    {
                        ui->BTN_day->setText(ui->BTN_day->text()+"3");
                    }
                    else if(ui->BTN_day->text().length()==1)
                    {
                        if(ui->BTN_day->text().toInt()<=2)
                        {
                            ui->BTN_day->setText(ui->BTN_day->text()+"3");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nHour:
                    if(ui->BTN_hour->text().length()==0)
                    {
                        ui->BTN_hour->setText(ui->BTN_hour->text()+"3");
                    }
                    else if(ui->BTN_hour->text().length()==1)
                    {
                        if(ui->BTN_hour->text().toInt()<=2)
                        {
                            ui->BTN_hour->setText(ui->BTN_hour->text()+"3");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nMinute:
                    if(ui->BTN_minute->text().length()==0)
                    {
                        ui->BTN_minute->setText(ui->BTN_minute->text()+"3");
                    }
                    else if(ui->BTN_minute->text().length()==1)
                    {
                        if(ui->BTN_minute->text().toInt()<6)
                        {
                            ui->BTN_minute->setText(ui->BTN_minute->text()+"3");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nSecond:
                    if(ui->BTN_second->text().length()==0)
                    {
                        ui->BTN_second->setText(ui->BTN_second->text()+"3");
                    }
                    else if(ui->BTN_second->text().length()==1)
                    {
                        if(ui->BTN_second->text().toInt()<6)
                        {
                            ui->BTN_second->setText(ui->BTN_second->text()+"3");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                }
             }
    else if(BTNName=="BTNNum4")
            {
                switch(currentNum)
                {
                case nYear:
                    if(ui->BTN_year->text().length()<2)
                    {
                        ui->BTN_year->setText(ui->BTN_year->text()+"4");
                    }
                    else
                    {}
                    break;
                 case nMonth:
                    if(ui->BTN_month->text().length()==0)
                    {
                        ui->BTN_month->setText(ui->BTN_month->text()+"4");
                    }
                    else if(ui->BTN_month->text().length()==1)
                    {
                        if(ui->BTN_month->text().toInt()==0)
                        {
                            ui->BTN_month->setText(ui->BTN_month->text()+"4");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nDay:
                    if(ui->BTN_day->text().length()==0)
                    {
                        ui->BTN_day->setText(ui->BTN_day->text()+"4");
                    }
                    else if(ui->BTN_day->text().length()==1)
                    {
                        if(ui->BTN_day->text().toInt()<=2)
                        {
                            ui->BTN_day->setText(ui->BTN_day->text()+"4");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nHour:
                    if(ui->BTN_hour->text().length()==0)
                    {
                        ui->BTN_hour->setText(ui->BTN_hour->text()+"4");
                    }
                    else if(ui->BTN_hour->text().length()==1)
                    {
                        if(ui->BTN_hour->text().toInt()<=2)
                        {
                            ui->BTN_hour->setText(ui->BTN_hour->text()+"4");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nMinute:
                    if(ui->BTN_minute->text().length()==0)
                    {
                        ui->BTN_minute->setText(ui->BTN_minute->text()+"4");
                    }
                    else if(ui->BTN_minute->text().length()==1)
                    {
                        if(ui->BTN_minute->text().toInt()<6)
                        {
                            ui->BTN_minute->setText(ui->BTN_minute->text()+"4");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nSecond:
                    if(ui->BTN_second->text().length()==0)
                    {
                        ui->BTN_second->setText(ui->BTN_second->text()+"4");
                    }
                    else if(ui->BTN_second->text().length()==1)
                    {
                        if(ui->BTN_second->text().toInt()<6)
                        {
                            ui->BTN_second->setText(ui->BTN_second->text()+"4");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                }
            }
    else if(BTNName=="BTNNum5")
            {
                switch(currentNum)
                {
                case nYear:
                    if(ui->BTN_year->text().length()<2)
                    {
                        ui->BTN_year->setText(ui->BTN_year->text()+"5");
                    }
                    else
                    {}
                    break;
                 case nMonth:
                    if(ui->BTN_month->text().length()==0)
                    {
                        ui->BTN_month->setText(ui->BTN_month->text()+"5");
                    }
                    else if(ui->BTN_month->text().length()==1)
                    {
                        if(ui->BTN_month->text().toInt()==0)
                        {
                            ui->BTN_month->setText(ui->BTN_month->text()+"5");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nDay:
                    if(ui->BTN_day->text().length()==0)
                    {
                        ui->BTN_day->setText(ui->BTN_day->text()+"5");
                    }
                    else if(ui->BTN_day->text().length()==1)
                    {
                        if(ui->BTN_day->text().toInt()<=2)
                        {
                            ui->BTN_day->setText(ui->BTN_day->text()+"5");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nHour:
                    if(ui->BTN_hour->text().length()==0)
                    {
                        ui->BTN_hour->setText(ui->BTN_hour->text()+"5");
                    }
                    else if(ui->BTN_hour->text().length()==1)
                    {
                        if(ui->BTN_hour->text().toInt()<2)
                        {
                            ui->BTN_hour->setText(ui->BTN_hour->text()+"5");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nMinute:
                    if(ui->BTN_minute->text().length()==0)
                    {
                        ui->BTN_minute->setText(ui->BTN_minute->text()+"5");
                    }
                    else if(ui->BTN_minute->text().length()==1)
                    {
                        if(ui->BTN_minute->text().toInt()<6)
                        {
                            ui->BTN_minute->setText(ui->BTN_minute->text()+"5");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nSecond:
                    if(ui->BTN_second->text().length()==0)
                    {
                        ui->BTN_second->setText(ui->BTN_second->text()+"5");
                    }
                    else if(ui->BTN_second->text().length()==1)
                    {
                        if(ui->BTN_second->text().toInt()<6)
                        {
                            ui->BTN_second->setText(ui->BTN_second->text()+"5");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                }
            }
    else if(BTNName=="BTNNum6")
            {
                switch(currentNum)
                {
                case nYear:
                    if(ui->BTN_year->text().length()<2)
                    {
                        ui->BTN_year->setText(ui->BTN_year->text()+"6");
                    }
                    else
                    {}
                    break;
                 case nMonth:
                    if(ui->BTN_month->text().length()==0)
                    {
                        ui->BTN_month->setText(ui->BTN_month->text()+"6");
                    }
                    else if(ui->BTN_month->text().length()==1)
                    {
                        if(ui->BTN_month->text().toInt()==0)
                        {
                            ui->BTN_month->setText(ui->BTN_month->text()+"6");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nDay:
                    if(ui->BTN_day->text().length()==0)
                    {
                        ui->BTN_day->setText(ui->BTN_day->text()+"6");
                    }
                    else if(ui->BTN_day->text().length()==1)
                    {
                        if(ui->BTN_day->text().toInt()<=2)
                        {
                            ui->BTN_day->setText(ui->BTN_day->text()+"6");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nHour:
                    if(ui->BTN_hour->text().length()==0)
                    {
                        ui->BTN_hour->setText(ui->BTN_hour->text()+"6");
                    }
                    else if(ui->BTN_hour->text().length()==1)
                    {
                        if(ui->BTN_hour->text().toInt()<2)
                        {
                            ui->BTN_hour->setText(ui->BTN_hour->text()+"6");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nMinute:
                    if(ui->BTN_minute->text().length()==0)
                    {
                        ui->BTN_minute->setText(ui->BTN_minute->text()+"6");
                    }
                    else if(ui->BTN_minute->text().length()==1)
                    {
                        if(ui->BTN_minute->text().toInt()<6)
                        {
                            ui->BTN_minute->setText(ui->BTN_minute->text()+"6");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nSecond:
                    if(ui->BTN_second->text().length()==0)
                    {
                        ui->BTN_second->setText(ui->BTN_second->text()+"6");
                    }
                    else if(ui->BTN_second->text().length()==1)
                    {
                        if(ui->BTN_second->text().toInt()<6)
                        {
                            ui->BTN_second->setText(ui->BTN_second->text()+"6");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                }
            }
    else if(BTNName=="BTNNum7")
            {
                switch(currentNum)
                {
                case nYear:
                    if(ui->BTN_year->text().length()<2)
                    {
                        ui->BTN_year->setText(ui->BTN_year->text()+"7");
                    }
                    else
                    {}
                    break;
                 case nMonth:
                    if(ui->BTN_month->text().length()==0)
                    {
                        ui->BTN_month->setText(ui->BTN_month->text()+"7");
                    }
                    else if(ui->BTN_month->text().length()==1)
                    {
                        if(ui->BTN_month->text().toInt()==0)
                        {
                            ui->BTN_month->setText(ui->BTN_month->text()+"7");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nDay:
                    if(ui->BTN_day->text().length()==0)
                    {
                        ui->BTN_day->setText(ui->BTN_day->text()+"7");
                    }
                    else if(ui->BTN_day->text().length()==1)
                    {
                        if(ui->BTN_day->text().toInt()<=2)
                        {
                            ui->BTN_day->setText(ui->BTN_day->text()+"7");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nHour:
                    if(ui->BTN_hour->text().length()==0)
                    {
                        ui->BTN_hour->setText(ui->BTN_hour->text()+"7");
                    }
                    else if(ui->BTN_hour->text().length()==1)
                    {
                        if(ui->BTN_hour->text().toInt()<2)
                        {
                            ui->BTN_hour->setText(ui->BTN_hour->text()+"7");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nMinute:
                    if(ui->BTN_minute->text().length()==0)
                    {
                        ui->BTN_minute->setText(ui->BTN_minute->text()+"7");
                    }
                    else if(ui->BTN_minute->text().length()==1)
                    {
                        if(ui->BTN_minute->text().toInt()<6)
                        {
                            ui->BTN_minute->setText(ui->BTN_minute->text()+"7");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nSecond:
                    if(ui->BTN_second->text().length()==0)
                    {
                        ui->BTN_second->setText(ui->BTN_second->text()+"7");
                    }
                    else if(ui->BTN_second->text().length()==1)
                    {
                        if(ui->BTN_second->text().toInt()<6)
                        {
                            ui->BTN_second->setText(ui->BTN_second->text()+"7");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                }
            }
    else if(BTNName=="BTNNum8")
            {
                switch(currentNum)
                {
                case nYear:
                    if(ui->BTN_year->text().length()<2)
                    {
                        ui->BTN_year->setText(ui->BTN_year->text()+"8");
                    }
                    else
                    {}
                    break;
                 case nMonth:
                    if(ui->BTN_month->text().length()==0)
                    {
                        ui->BTN_month->setText(ui->BTN_month->text()+"8");
                    }
                    else if(ui->BTN_month->text().length()==1)
                    {
                        if(ui->BTN_month->text().toInt()==0)
                        {
                            ui->BTN_month->setText(ui->BTN_month->text()+"8");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nDay:
                    if(ui->BTN_day->text().length()==0)
                    {
                        ui->BTN_day->setText(ui->BTN_day->text()+"8");
                    }
                    else if(ui->BTN_day->text().length()==1)
                    {
                        if(ui->BTN_day->text().toInt()<=2)
                        {
                            ui->BTN_day->setText(ui->BTN_day->text()+"8");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nHour:
                    if(ui->BTN_hour->text().length()==0)
                    {
                        ui->BTN_hour->setText(ui->BTN_hour->text()+"8");
                    }
                    else if(ui->BTN_hour->text().length()==1)
                    {
                        if(ui->BTN_hour->text().toInt()<2)
                        {
                            ui->BTN_hour->setText(ui->BTN_hour->text()+"8");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nMinute:
                    if(ui->BTN_minute->text().length()==0)
                    {
                        ui->BTN_minute->setText(ui->BTN_minute->text()+"8");
                    }
                    else if(ui->BTN_minute->text().length()==1)
                    {
                        if(ui->BTN_minute->text().toInt()<6)
                        {
                            ui->BTN_minute->setText(ui->BTN_minute->text()+"8");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nSecond:
                    if(ui->BTN_second->text().length()==0)
                    {
                        ui->BTN_second->setText(ui->BTN_second->text()+"8");
                    }
                    else if(ui->BTN_second->text().length()==1)
                    {
                        if(ui->BTN_second->text().toInt()<6)
                        {
                            ui->BTN_second->setText(ui->BTN_second->text()+"8");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                }
            }
    else if(BTNName=="BTNNum9")
            {
                switch(currentNum)
                {
                case nYear:
                    if(ui->BTN_year->text().length()<2)
                    {
                        ui->BTN_year->setText(ui->BTN_year->text()+"9");
                    }
                    else
                    {}
                    break;
                 case nMonth:
                    if(ui->BTN_month->text().length()==0)
                    {
                        ui->BTN_month->setText(ui->BTN_month->text()+"9");
                    }
                    else if(ui->BTN_month->text().length()==1)
                    {
                        if(ui->BTN_month->text().toInt()==0)
                        {
                            ui->BTN_month->setText(ui->BTN_month->text()+"9");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nDay:
                    if(ui->BTN_day->text().length()==0)
                    {
                        ui->BTN_day->setText(ui->BTN_day->text()+"9");
                    }
                    else if(ui->BTN_day->text().length()==1)
                    {
                        if(ui->BTN_day->text().toInt()<=2)
                        {
                            ui->BTN_day->setText(ui->BTN_day->text()+"9");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nHour:
                    if(ui->BTN_hour->text().length()==0)
                    {
                        ui->BTN_hour->setText(ui->BTN_hour->text()+"9");
                    }
                    else if(ui->BTN_hour->text().length()==1)
                    {
                        if(ui->BTN_hour->text().toInt()<2)
                        {
                            ui->BTN_hour->setText(ui->BTN_hour->text()+"9");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nMinute:
                    if(ui->BTN_minute->text().length()==0)
                    {
                        ui->BTN_minute->setText(ui->BTN_minute->text()+"9");
                    }
                    else if(ui->BTN_minute->text().length()==1)
                    {
                        if(ui->BTN_minute->text().toInt()<6)
                        {
                            ui->BTN_minute->setText(ui->BTN_minute->text()+"9");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                 case nSecond:
                    if(ui->BTN_second->text().length()==0)
                    {
                        ui->BTN_second->setText(ui->BTN_second->text()+"9");
                    }
                    else if(ui->BTN_second->text().length()==1)
                    {
                        if(ui->BTN_second->text().toInt()<6)
                        {
                            ui->BTN_second->setText(ui->BTN_second->text()+"9");
                        }
                        else
                        {}
                    }
                    else
                    {}
                    break;
                }
            }
    else if(BTNName=="BTNNumClear")
            {
                switch(currentNum)
                {
                case nYear:
                    ui->BTN_year->setText("");
                    break;
                case nMonth:
                    ui->BTN_month->setText("");
                    break;
                case nDay:
                    ui->BTN_day->setText("");
                    break;
                case nHour:
                    ui->BTN_hour->setText("");
                    break;
                case nMinute:
                    ui->BTN_minute->setText("");
                    break;
                case nSecond:
                    ui->BTN_second->setText("");
                    break;
                }
            }
    else if(BTNName=="BTNNumC")
            {
                switch(currentNum)
                {
                case nYear:
                    ui->BTN_year->setText(ui->BTN_year->text().left(ui->BTN_year->text().length()-1));
                    break;
                case nMonth:
                    ui->BTN_month->setText(ui->BTN_month->text().left(ui->BTN_month->text().length()-1));
                    break;
                case nDay:
                    ui->BTN_day->setText(ui->BTN_day->text().left(ui->BTN_day->text().length()-1));
                    break;
                case nHour:
                    ui->BTN_hour->setText(ui->BTN_hour->text().left(ui->BTN_day->text().length()-1));
                    break;
                case nMinute:
                    ui->BTN_minute->setText(ui->BTN_minute->text().left(ui->BTN_minute->text().length()-1));
                    break;
                case nSecond:
                    ui->BTN_second->setText(ui->BTN_second->text().left(ui->BTN_second->text().length()-1));
                    break;
                }
            }

            else
            {

            }

}

void VehicleMTTimeSetPage::allButtonRelease()
{
    ui->BTN_day->setStyleSheet(BUTTONRELEASE);
    ui->BTN_hour->setStyleSheet(BUTTONRELEASE);
    ui->BTN_minute->setStyleSheet(BUTTONRELEASE);
    ui->BTN_month->setStyleSheet(BUTTONRELEASE);
    ui->BTN_second->setStyleSheet(BUTTONRELEASE);
    ui->BTN_year->setStyleSheet(BUTTONRELEASE);
}

void VehicleMTTimeSetPage::setTimeEnd()
{
    database->DiCT_SAVETime_B1=false;
    database->DiCT_SetFlagChecker_U8=0x55;
    ui->BTN9OK->setStyleSheet(MAKESURERELEASE);

}
