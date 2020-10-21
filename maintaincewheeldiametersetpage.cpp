#include "maintaincewheeldiametersetpage.h"
#include "ui_maintaincewheeldiametersetpage.h"

#include "qdebug.h"

#define BUTTONPRESS "color: black;font:20px \"微软雅黑\";background-color: rgb(193, 193, 193);border-right:2px solid rgb(170,170,170);border-bottom:2px solid rgb(170,170,170);border-radius:0px;"
#define BUTTONRELEASE  "color: white;font:20px \"微软雅黑\";background-color: rgb(0, 0, 100);border-right:2px solid rgb(170,170,170);border-bottom:2px solid rgb(170,170,170);border-radius:0px;"

#define CONFIRMRELEASE "font: 20px, \"微软雅黑\";color: black;transparent;background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 rgba(170,170,170,255),stop:1 rgba(150,150,150,255));"
#define CONFIRMPRESS "font: 20px, \"微软雅黑\";color: black;background-color: rgb(85, 85, 255);"


MaintainceWheelDiameterSetPage::MaintainceWheelDiameterSetPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceWheelDiameterSetPage)
{

    ui->setupUi(this);
//    ui->lbl2->hide();
//    ui->BTNMetroNumSet->hide();
    m_wheelTextValue<<0<<0<<0<<0;
    QList<QPushButton*> buttons;
    buttons<<ui->BTNNum0<<ui->BTNNum1<<ui->BTNNum2<<ui->BTNNum3<<ui->BTNNum4<<ui->BTNNum5<<ui->BTNNum6<<ui->BTNNum7
            <<ui->BTNNum8<<ui->BTNNum9<<ui->BTNNumC;

    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(NumKeyboardEvent()));
    }

    connect(this, SIGNAL(myKeyPress(QString)), this, SLOT(myKeyPressEvent(QString)));

    warnningDialog = new WarnningDialog(this);
    warnningDialog->setGeometry(300,250,warnningDialog->width(),warnningDialog->height());
    warnningDialog->setDialogstyle("轮径设定错误！\n请重新设定","background-color: black;border:3px solid white;");
    warnningDialog->hide();

    m_WheelBtnIndex = 1;
    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timer2sEvent()));

    //wheel_buttons<<ui->BTNMetroNumSet<<ui->BTNTC1SetValue<<ui->BTNMP1SetValue<<ui->BTNM1SetValue<<ui->BTNM2SetValue<<ui->BTNSelectAll;
    wheel_buttons<<ui->BTNTC1SetValue<<ui->BTNMP1SetValue<<ui->BTNM1SetValue<<ui->BTNM2SetValue<<ui->BTNSelectAll<<ui->BTNMetroNumSet;
    foreach(QPushButton* button,this->wheel_buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(WheelButtonsEvent()));
    }

    m_wheelvalue<<&database->DiCT_WheelDia1_U8<<&database->DiCT_WheelDia2_U8<<&database->DiCT_WheelDia5_U8
            <<&database->DiCT_WheelDia6_U8;

    m_wheelsaveflag<<&database->DiCT_SAVEWheelDig1_B1<<&database->DiCT_SAVEWheelDig2_B1<<&database->DiCT_SAVEWheelDig3_B1
            <<&database->DiCT_SAVEWheelDig4_B1;

}

MaintainceWheelDiameterSetPage::~MaintainceWheelDiameterSetPage()
{
    delete ui;
}
void MaintainceWheelDiameterSetPage::NumKeyboardEvent()
{
    QString key = ((QPushButton *)this->sender())->text();

    emit this->myKeyPress(key);
}

void MaintainceWheelDiameterSetPage::WheelButtonsEvent()
{
    this->m_Inputvalue.clear();
    m_WheelBtnIndex = ((QPushButton*)this->sender())->whatsThis().toInt();
    m_Btnname = ((QPushButton*)this->sender())->objectName();
    for(int i = 0; i< wheel_buttons.size();i++)
    {
        wheel_buttons.at(i)->setStyleSheet(BUTTONRELEASE);
    }


    if(m_Btnname == "BTNSelectAll")
    {
        foreach(QPushButton* button,this->wheel_buttons)
        {
            if((button->objectName() != "BTNMetroNumSet")&&(button->objectName()!="BTNMetroLineSet"))
            {
                button->setStyleSheet(BUTTONPRESS);
            }
        }

    }else
    {
        foreach(QPushButton* button,this->wheel_buttons)
        {
            button->setStyleSheet(BUTTONRELEASE);
        }
        ((QPushButton*)this->sender())->setStyleSheet(BUTTONPRESS);
    }
}


void MaintainceWheelDiameterSetPage::myKeyPressEvent(QString key)
{
    if(m_Btnname == "BTNMetroNumSet")
    {
        if(key.trimmed() == "C")
        {
            this->m_Inputvalue = this->m_Inputvalue.left(this->m_Inputvalue.length()-1);
        }
        else
        {
            if(this->m_Inputvalue.length()<2)
            {
                this->m_Inputvalue.append(key);
            }else
            {
                this->m_Inputvalue.clear();
            }
        }
        this->ui->BTNMetroNumSet->setText(m_Inputvalue);
        this->database->DiCT_TrainNum_U8 = m_Inputvalue.toInt();
    }
//    else if(m_Btnname=="BTNMetroLineSet")
//    {
//        if(key.trimmed() == "C")
//        {
//            this->m_Inputvalue = this->m_Inputvalue.left(this->m_Inputvalue.length()-1);
//        }
//        else
//        {
//            if(this->m_Inputvalue.length()<2)
//            {
//                this->m_Inputvalue.append(key);
//            }else
//            {
//                this->m_Inputvalue.clear();
//            }
//        }
//        this->database->DiCT_LineNum_U8 = m_Inputvalue.toInt();
//    }
    else if(m_Btnname=="BTNSelectAll")
    {
        if(key.trimmed() == "C")
        {
            this->m_Inputvalue = this->m_Inputvalue.left(this->m_Inputvalue.length()-1);
        }
        else
        {
            if(this->m_Inputvalue.length()<3)
            {
                this->m_Inputvalue.append(key);
            }
        }
        foreach(QPushButton* button,this->wheel_buttons)
        {
            //if(!(button->objectName()=="BTNMetroNumSet")&&!(button->objectName() == "BTNSelectAll")&&!(button->objectName()=="BTNMetroLineSet"))
            if(!(button->objectName() == "BTNSelectAll")&&!(button->objectName()=="BTNMetroNumSet"))
            {
                    button->setText(m_Inputvalue);

            }
        }
        this->database->DiCT_WheelDia1_U8 = this->database->DiCT_WheelDia2_U8 =
        this->database->DiCT_WheelDia5_U8 = this->database->DiCT_WheelDia6_U8 = m_Inputvalue.toInt()-770;
    }
    else
    {
        if(key.trimmed() == "C")
        {
            this->m_Inputvalue = this->m_Inputvalue.left(this->m_Inputvalue.length()-1);
        }
        else
        {
            if(this->m_Inputvalue.length()<3)
            {
                this->m_Inputvalue.append(key);
            }
        }
        wheel_buttons[m_WheelBtnIndex-1]->setText(m_Inputvalue);
        *m_wheelvalue[m_WheelBtnIndex-1] = m_Inputvalue.toInt()-770;
        qDebug()<<*m_wheelvalue[m_WheelBtnIndex-1];
    }

}


void MaintainceWheelDiameterSetPage::allButtonRelease()
{
    ui->BTNM1SetValue->setStyleSheet(BUTTONRELEASE);
    ui->BTNM2SetValue->setStyleSheet(BUTTONRELEASE);
    ui->BTNTC1SetValue->setStyleSheet(BUTTONRELEASE);
    ui->BTNMP1SetValue->setStyleSheet(BUTTONRELEASE);
    ui->BTNMetroNumSet->setStyleSheet(BUTTONRELEASE);
}

void MaintainceWheelDiameterSetPage::timer2sEvent()
{
    for(int i = 0 ;i<wheel_buttons.size();i++)
    {
        wheel_buttons.at(i)->setStyleSheet(BUTTONRELEASE);
    }
    this->timer->stop();
    this->ui->BTN9->setStyleSheet(CONFIRMRELEASE);
    this->database->DiCT_SetFlagChecker_U8 = 0x55;
    if(m_Btnname == "BTNMetroNumSet")
    {
        this->database->DiCT_SAVETrainNum_B1 = false;
    }
//    else if(m_Btnname=="BTNMetroLineSet")
//    {
//        this->database->DiCT_SAVELineNum_B1=false;
//    }
    else if(m_Btnname == "BTNSelectAll")
    {
        for(int i = 0;i<m_wheelvalue.size();i++)
        {
            *m_wheelsaveflag[i] = false;
        }
    }else
    {
        *m_wheelsaveflag[m_WheelBtnIndex-1] = false;
    }
}


void MaintainceWheelDiameterSetPage::updatePage()
{

    ui->lbl_TC1Value->setText(QString::number(database->CTD_WheelDig1FedBk_U8+770));
    ui->lbl_MP1Value->setText(QString::number(database->CTD_WheelDig2FedBk_U8+770));
    ui->lbl_M1Value->setText(QString::number(database->CTD_WheelDig3FedBk_U8+770));
    ui->lbl_M2Value->setText(QString::number(database->CTD_WheelDig4FedBk_U8+770));

//    qDebug()<<database->DiCT_WheelDia1_U8<<" "<<database->DiCT_WheelDia2_U8<<" "
//           <<database->DiCT_WheelDia5_U8<<" "<<database->DiCT_WheelDia6_U8;

//    qDebug()<<database->DiCT_SAVEWheelDig1_B1<<" "<<database->DiCT_SAVEWheelDig2_B1<<" "
//           <<database->DiCT_SAVEWheelDig3_B1<<" "<<database->DiCT_SAVEWheelDig4_B1;

}
void MaintainceWheelDiameterSetPage::on_BTN1_pressed()
{
    this->timer->stop();
    this->database->DiCT_SetFlagChecker_U8 = 0x55;
    changePage(uVehicleMaintainPage);
}

void MaintainceWheelDiameterSetPage::on_BTNHome_pressed()
{
    this->timer->stop();
    this->database->DiCT_SetFlagChecker_U8 = 0x55;
    changePage(uVehicleTrainArea);
}

void MaintainceWheelDiameterSetPage::on_BTN9_pressed()
{

    m_wheelTextValue<<ui->BTNTC1SetValue->text().toInt()<<ui->BTNMP1SetValue->text().toInt()<<ui->BTNM1SetValue->text().toInt()
            <<ui->BTNM2SetValue->text().toInt();

    if(m_Btnname == "BTNMetroNumSet")
    {
        if(this->database->DiCT_TrainNum_U8>0 && this->database->DiCT_TrainNum_U8<99)
        {

            this->database->DiCT_SAVETrainNum_B1 = true;
            this->database->DiCT_SetFlagChecker_U8 = 0xaa;
            this->ui->BTN9->setStyleSheet(CONFIRMPRESS);
            MainGetDefaultPara::set("/TrainCode/Code",this->database->DiCT_TrainNum_U8);
            this->timer->start(5000);
        }else
        {
            this->warnningDialog->show();
        }
    }
    else  if(m_Btnname == "BTNSelectAll")
    {
        if( m_Inputvalue.toInt()>=770&& m_Inputvalue.toInt()<=840)
        {
            for(int i = 0;i< m_wheelvalue.size();i++)
            {
                *m_wheelsaveflag[i] = true;
            }
            this->database->DiCT_SetFlagChecker_U8 = 0xaa;
            this->ui->BTN9->setStyleSheet(CONFIRMPRESS);
            MainGetDefaultPara::set("/Wheel/Wheel",this->database->DiCT_WheelDia1_U8);

            this->timer->start(5000);
        }else
        {
            for(int i = 0;i< m_wheelvalue.size();i++)
            {
                *m_wheelvalue[i] = 0;

            }
            this->warnningDialog->show();

        }
    }
     else
    {

        //if(m_wheelTextValue[m_WheelBtnIndex-1]>=770&&m_wheelTextValue[m_WheelBtnIndex-1]<=840)
        if(*m_wheelvalue[m_WheelBtnIndex-1]>=0&&*m_wheelvalue[m_WheelBtnIndex-1]<=70)
         {
            *m_wheelsaveflag[m_WheelBtnIndex-1] = true;
            this->database->DiCT_SetFlagChecker_U8 = 0xaa;
            this->ui->BTN9->setStyleSheet(CONFIRMPRESS);
            this->timer->start(5000);
        }else
        {
            qDebug()<<m_WheelBtnIndex-1;
            *m_wheelvalue[m_WheelBtnIndex-1] = 0;
            this->warnningDialog->show();

        }

    }
    m_wheelTextValue.clear();
}

void MaintainceWheelDiameterSetPage::hideEvent(QHideEvent *)
{
    for(int i=0;i<m_wheelsaveflag.length();i++){
        *m_wheelsaveflag[i]=false;
    }
    ui->BTN9->setStyleSheet(CONFIRMRELEASE);
    this->timer->stop();
}
