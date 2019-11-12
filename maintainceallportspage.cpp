#include "maintainceallportspage.h"
#include "ui_maintainceallportspage.h"
#include "crrcricomvb.h"
#include "qdebug.h"
#define PButtonUP    "font: 20px, \"微软雅黑\";color: white;background-color: rgb(0, 128, 128);border-top: 2px solid white;border-left: 2px solid white;border-radius:8px;"
#define PButtonDOWN  "font: 20px, \"微软雅黑\";color: white;background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 rgba(150,150,200,255),stop:1 rgba(0,0,50,255));border-top:0xp;border-left:0px; border-bottom: 2px solid white;border-right: 2px solid white;border-radius:8px;"

MaintainceAllPortsPage::MaintainceAllPortsPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceAllPortsPage)
{
    ui->setupUi(this);
    buttons<<ui->BTN_ACE<<ui->BTN_ATC<<ui->BTN_BCE<<ui->BTN_DDU<<ui->BTN_EDCUA<<ui->BTN_ERM
          <<ui->BTN_FAS<<ui->BTN_HVAC<<ui->BTN_PCE<<ui->BTN_PCU<<ui->BTN_PIS<<ui->BTN_RIOM<<ui->BTN_TDS
         <<ui->BTN_VCUA<<ui->BTN_VCUB<<ui->BTN_Return;

    VCUAPort<<0xF<<0x118<<0x128<<0x138<<0x148<<0x158<<0x168<<0x208<<0x308<<0x309<<0x30A<<0x418
           <<0x518<<0x528<<0x538<<0x548<<0x558<<0x568<<0x618<<0x628<<0x708<<0x818<<0x918<<0xA18
          <<0xA28<<0xA38<<0xA48<<0xB18;
    VCUBPort<<0xC18;
    RIOMPort<<0x110<<0x111<<0x112<<0x120<<0x121<<0x130<<0x131<<0x140<<0x141<<0x142<<0x150<<0x151
           <<0x160<<0x161;
    ERMPort<<0x210<<0x211<<0x212<<0x213<<0x220<<0x221<<0x222<<0x223;
    DDUPort<<0x310<<0x311<<0x320<<0x321;
    BCEPort<<0x410<<0x411<<0x412<<0x413<<0x414<<0x415<<0x416<<0x420<<0x421<<0x422<<0x423<<0x424<<0x425<<0x426;
    PCEPort<<0x510<<0x511<<0x512<<0x513<<0x520<<0x521<<0x522<<0x523<<0x530<<0x531<<0x532<<0x533
          <<0x540<<0x541<<0x542<<0x543<<0x550<<0x551<<0x552<<0x553<<0x560<<0x561<<0x562<<0x563;
    ACEPort<<0x610<<0x620;
    EDCUAPort<<0x710<<0x711<<0x712<<0x720<<0x721<<0x722<<0x730<<0x731<<0x732<<0x740<<0x741<<0x742
            <<0x750<<0x751<<0x752<<0x760<<0x761<<0x762<<0x770<<0x771<<0x772<<0x780<<0x781<<0x782;
    FASPort<<0x810<<0x820;
    PISPort<<0x910<<0x911<<0x920<<0x921;
    HVACPort<<0xA10<<0xA20<<0xA30<<0xA40;
    ATCPort<<0xB10<<0xB20;
    PCUPort<<0xC10;




    this->m_PortsList = VCUAPort;
    ui->BTN_VCUA->setStyleSheet(PButtonDOWN);
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(NBpressEvent()));
    }
}

MaintainceAllPortsPage::~MaintainceAllPortsPage()
{
    delete ui;
}

void MaintainceAllPortsPage::NBpressEvent()
{
    QString BTNName = ((QPushButton *)this->sender())->objectName();
    if(BTNName=="BTN_Return")
    {
        changePage(uVehicleMaintainPage);
    }
    else if(BTNName=="BTN_VCUA")
    {
        this->m_PortsList=VCUAPort;
    }
    else if(BTNName=="BTN_VCUB")
    {
        this->m_PortsList=VCUBPort;
    }
    else if(BTNName=="BTN_RIOM")
    {
        this->m_PortsList=RIOMPort;
    }
    else if(BTNName=="BTN_DDU")
    {
        this->m_PortsList=DDUPort;
    }
    else if(BTNName=="BTN_ERM")
    {
        this->m_PortsList=ERMPort;
    }
    else if(BTNName=="BTN_PCE")
    {
        this->m_PortsList=PCEPort;
    }
    else if(BTNName=="BTN_ACE")
    {
        this->m_PortsList=ACEPort;
    }
    else if(BTNName=="BTN_BCE")
    {
        this->m_PortsList=BCEPort;
    }
    else if(BTNName=="BTN_EDCUA")
    {
        this->m_PortsList=EDCUAPort;
    }
    else if(BTNName=="BTN_HVAC")
    {
        this->m_PortsList=HVACPort;
    }
    else if(BTNName=="BTN_ATC")
    {
        this->m_PortsList=ATCPort;
    }
    else if(BTNName=="BTN_PIS")
    {
        this->m_PortsList=PISPort;
    }
    else if(BTNName=="BTN_TDS")
    {
        this->m_PortsList=TDSPort;
    }
    else if(BTNName=="BTN_FAS")
    {
        this->m_PortsList=FASPort;
    }
    else if(BTNName=="BTN_PCU")
    {
        this->m_PortsList=PCUPort;
    }

    if(BTNName=="BTN_Return")
    {
        for(int i = 0; i < buttons.size();i++)
        {
           buttons[i]->setStyleSheet(PButtonUP);
        }
        ui->BTN_VCUA->setStyleSheet(PButtonDOWN);
        this->m_PortsList=VCUAPort;
    }
    else
    {
        for(int i = 0; i < buttons.size();i++)
        {
           buttons[i]->setStyleSheet(PButtonUP);
        }
        ((QPushButton *)this->sender())->setStyleSheet(PButtonDOWN);
    }

}

void MaintainceAllPortsPage::installMvb(CrrcRicoMvb *crrcRicoMvb)
{
    this->crrcRicoMvb=crrcRicoMvb;
}

void MaintainceAllPortsPage::updatePage()
{
    this->update();
}

void MaintainceAllPortsPage::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QFont font;
    font.setFamily("寰蒋闆呴粦");
    font.setPixelSize(14);
    painter.setFont(font);
    painter.setPen(QPen(Qt::white,2));
    painter.setBrush(QBrush(Qt::transparent));

    // draw title
    for(int i = 0; i < 34 ; i++)
    {

        QString text1;
        QRect rect1;
        if(i == 0)
        {
            text1 = "port";
            rect1 = QRect(1,2,39,25);
            painter.drawRect(rect1);

        }else if(i == 33)
        {
            text1 = "cycle";
            rect1 = QRect(26*32+40,2,50,25);

        }else
        {
            QString tmp;
            tmp.sprintf("%02d",i-1);
            text1 = tmp;
            rect1 = QRect(i*26+14,2,26,25);

        }


        if(i%2==1)
        {
            painter.drawRect(QRect(i*26+14,2,52,25));
        }
        painter.drawText(rect1,Qt::AlignCenter,text1);

    }



    //draw data
    for(int j = 0 ;j < 28 ;j++)
    {
        for(int i = 0; i < 34 ; i++)
        {
            QString text2;
            QRect rect2,rect3;

            if(j%3 == 0)// set pen color
            {
                painter.setPen(QPen(QColor(255,128,0),2));
            }else if(j%3 == 1)
            {
                painter.setPen(QPen(Qt::lightGray,2));
            }else
            {
                painter.setPen(QPen(QColor(0, 255, 255),2));
            }
            //portaddress
            if(i == 0)
            {
                if(j<m_PortsList.size())
                {
                    QString tmp;
                    tmp.sprintf("%03x",m_PortsList[j]);

                    text2 = tmp.toUpper();
                }else
                {
                    text2 = "";
                }
                rect2 = QRect(1,2+(j+1)*24,39,25);
                painter.drawRect(rect2);
                painter.drawText(rect2,Qt::AlignCenter,text2);
            }else if(i == 33)//cycle
            {
                painter.save();
                painter.setPen(QPen(Qt::white,2));

                if(j<m_PortsList.size())
                {
                    QString tmp;
                    tmp.sprintf("%02d",CrrcRicoMvb::getcrrcRicoMvb()->getPortCycle(m_PortsList[j]));


                    if(CrrcRicoMvb::getcrrcRicoMvb()->isPortTimeout(m_PortsList[j]))
                    {
                        painter.setBrush(QBrush(Qt::red));
                    }else
                    {
                        painter.setBrush(QBrush(Qt::transparent));
                    }
                    text2 = tmp.toUpper();
                }else
                {
                    painter.setBrush(QBrush(Qt::transparent));
                    text2 = "";
                }
                rect2 = QRect(32*26+40,2+(j+1)*24,51,25);

                painter.drawRect(rect2);
                painter.drawText(rect2,Qt::AlignCenter,text2);
                painter.restore();

            }else//data
            {
                QString tmp;

                if(j<m_PortsList.size())
                {
                    tmp.sprintf("%02x",CrrcRicoMvb::getcrrcRicoMvb()->getUnsignedChar(m_PortsList[j],i-1));

                    text2 = tmp.toUpper();
                }else
                {
                    text2 = "";
                }
                rect3 = QRect(i*26+14,2+(j+1)*24,26,25);
                painter.drawText(rect3,Qt::AlignCenter,text2);
            }


            if(i%2==1)
            {
                painter.drawRect(QRect(i*26+14,2+(j+1)*24,52,25));
            }

        }
    }

}
