#include "maintaincecurrentfaultpage.h"
#include "ui_maintaincecurrentfaultpage.h"
#include "crrcfault.h"
#include "qdebug.h"
#define MAXCNTPERPAGE 9
#define COLUMN        5

#define LEVEL1BTNDOWN   "border:1px solid transparent;background-color:red;color:rgb(0,0,50);font:14px \"微软雅黑\";"
#define LEVEL2BTNDOWN   "border:1px solid transparent;background-color:yellow;color:rgb(0,0,50);font:14px \"微软雅黑\";"
#define LEVEL3BTNDOWN   "border:1px solid transparent;background-color:white;color:rgb(0,0,50);font:14px \"微软雅黑\";"

#define LEVEL1BTNUP   "border:1px solid transparent;background-color:rgb(0,0,50);color:red;font:14px \"微软雅黑\";"
#define LEVEL2BTNUP   "border:1px solid transparent;background-color:rgb(0,0,50);color:yellow;font:14px \"微软雅黑\";"
#define LEVEL3BTNUP   "border:1px solid transparent;background-color:rgb(0,0,50);color:white;font:14px \"微软雅黑\";"
#define LEVEL0BTNUP   "border:1px solid transparent;background-color:rgb(0,0,50);font:14px \"微软雅黑\";"

#define TRAINNOFAULT   "color:black;background-color:rgb(170,170,170);"
#define TRAINFAULT   "color:white;background-color:red;"

#define SPARE         "                                    "


MaintainceCurrentFaultPage::MaintainceCurrentFaultPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceCurrentFaultPage)
{
    ui->setupUi(this);

    m_Detail = "";
    m_currentPageIndex  = 1;
    m_totalPageIndex = 1;
    m_currentPageFaultNum = 0;
    m_totalFaultNum = 0;
    m_currentButtonsDown = 0;

    m_buttons<< this->ui->BTN_LINE1<<this->ui->BTN_LINE2<<this->ui->BTN_LINE3<<this->ui->BTN_LINE4<<this->ui->BTN_LINE5<<
              this->ui->BTN_LINE6<<this->ui->BTN_LINE7<<this->ui->BTN_LINE8<<this->ui->BTN_LINE9;

    foreach(QPushButton* btn,m_buttons)
    {
        connect(btn,SIGNAL(pressed()),this,SLOT(ButtonsPressEvent()));
    }
    QList<QLabel*> tmp;
    tmp<<this->ui->LBLStarttime1<<this->ui->LBLCode1<<this->ui->LBLFaultName1<<this->ui->LBLLevel1<<this->ui->LBLSystem1;
    m_labels.push_back(tmp);
    tmp.clear();

    tmp<<this->ui->LBLStarttime1_2<<this->ui->LBLCode1_2<<this->ui->LBLFaultName1_2<<this->ui->LBLLevel1_2<<this->ui->LBLSystem1_2;;
    m_labels.push_back(tmp);
    tmp.clear();

    tmp<<this->ui->LBLStarttime1_3<<this->ui->LBLCode1_3<<this->ui->LBLFaultName1_3<<this->ui->LBLLevel1_3<<this->ui->LBLSystem1_3;;
    m_labels.push_back(tmp);
    tmp.clear();

    tmp<<this->ui->LBLStarttime1_4<<this->ui->LBLCode1_4<<this->ui->LBLFaultName1_4<<this->ui->LBLLevel1_4<<this->ui->LBLSystem1_4;;
    m_labels.push_back(tmp);
    tmp.clear();

    tmp<<this->ui->LBLStarttime1_5<<this->ui->LBLCode1_5<<this->ui->LBLFaultName1_5<<this->ui->LBLLevel1_5<<this->ui->LBLSystem1_5;;
    m_labels.push_back(tmp);
    tmp.clear();

    tmp<<this->ui->LBLStarttime1_6<<this->ui->LBLCode1_6<<this->ui->LBLFaultName1_6<<this->ui->LBLLevel1_6<<this->ui->LBLSystem1_6;;
    m_labels.push_back(tmp);
    tmp.clear();

    tmp<<this->ui->LBLStarttime1_7<<this->ui->LBLCode1_7<<this->ui->LBLFaultName1_7<<this->ui->LBLLevel1_7<<this->ui->LBLSystem1_7;;
    m_labels.push_back(tmp);
    tmp.clear();

    tmp<<this->ui->LBLStarttime1_8<<this->ui->LBLCode1_8<<this->ui->LBLFaultName1_8<<this->ui->LBLLevel1_8<<this->ui->LBLSystem1_8;;
    m_labels.push_back(tmp);
    tmp.clear();

    tmp<<this->ui->LBLStarttime1_9<<this->ui->LBLCode1_9<<this->ui->LBLFaultName1_9<<this->ui->LBLLevel1_9<<this->ui->LBLSystem1_9;;
    m_labels.push_back(tmp);
    tmp.clear();

    ui->lbl_cab1_active->hide();
    ui->lbl_cab2_active->hide();
    ui->lbl_cab1_direction->hide();
    ui->lbl_cab2_direction->hide();
}

MaintainceCurrentFaultPage::~MaintainceCurrentFaultPage()
{
    delete ui;
}

void MaintainceCurrentFaultPage::ButtonsPressEvent()
{

    m_currentButtonsDown = ((QPushButton*)this->sender())->whatsThis().toInt();
    //((QPushButton*)this->sender())->setStyleSheet(LEVEL1BTNDOWN);
}
void MaintainceCurrentFaultPage::updatePage()
{



    m_totalFaultNum = CrrcFault::getCrrcFault()->getCurrentFaultListSize();

    if(m_totalFaultNum < 1)
    {
        this->ui->LBL_Page->setText("0 / 0\n共0条");
        this->ui->LBLTC1->setStyleSheet(TRAINNOFAULT);
        this->ui->LBLMP1->setStyleSheet(TRAINNOFAULT);
        this->ui->LBLM1->setStyleSheet(TRAINNOFAULT);
        this->ui->LBLM2->setStyleSheet(TRAINNOFAULT);
        this->ui->LBL_Datail->setText("");
//        for(int i = 0;i<this->m_buttons.size();i++)
//           {
//              this->m_buttons.at(i)->setText("");
//              this->m_buttons.at(i)->setStyleSheet(LEVEL0BTNUP);
//           }
        return ;
    }

    if(m_totalFaultNum%MAXCNTPERPAGE == 0)
    {
        m_totalPageIndex = m_totalFaultNum/MAXCNTPERPAGE;
        m_currentPageFaultNum = MAXCNTPERPAGE;
    }
    else
    {
        m_totalPageIndex = m_totalFaultNum/MAXCNTPERPAGE+1;
        m_currentPageFaultNum = m_totalFaultNum%MAXCNTPERPAGE;
    }

    if(m_currentPageIndex > m_totalPageIndex)
        m_currentPageIndex = m_totalPageIndex;

    this->ui->LBL_Page->setText(QString::number(m_currentPageIndex)+" / "+QString::number(m_totalPageIndex)+"\n共" + QString::number(m_totalFaultNum)+"条");

    if(m_currentPageIndex<m_totalPageIndex)//not last page
    {
        for(int i = 0; i< MAXCNTPERPAGE;i++)
        {
            this->DrawFaults(i);
        }

        this->Localareaupdate(MAXCNTPERPAGE);

    }else//last page
    {
        for(int i = 0; i< MAXCNTPERPAGE;i++)
        {
            if(i < m_currentPageFaultNum)//draw fault
            {
                this->DrawFaults(i);
            }else//draw block
            {
                for(int j = 0;j<COLUMN;j++)
                {
                    m_labels.at(i).at(j)->setText("");
                    m_labels.at(i).at(j)->setStyleSheet(LEVEL1BTNUP);
                }
            }
        }
        this->Localareaupdate(m_currentPageFaultNum);
    }
}


void MaintainceCurrentFaultPage::Localareaupdate(int index)
{
    // detial label &&  fault position
    if(m_currentButtonsDown<index)
    {
        this->ui->LBL_Datail->setWordWrap(true);
        this->ui->LBL_Datail->setText(CrrcFault::getCrrcFault()->getCurrentFaultDescription(m_currentButtonsDown+(m_currentPageIndex-1)*MAXCNTPERPAGE));
        QString tmp = CrrcFault::getCrrcFault()->getCurrentFaultPosition(m_currentButtonsDown+(m_currentPageIndex-1)*MAXCNTPERPAGE);
        this->ui->LBLTC1->setStyleSheet(TRAINNOFAULT);
        this->ui->LBLMP1->setStyleSheet(TRAINNOFAULT);
        this->ui->LBLM1->setStyleSheet(TRAINNOFAULT);
        this->ui->LBLM2->setStyleSheet(TRAINNOFAULT);
        if(tmp == "1")
            this->ui->LBLTC1->setStyleSheet(TRAINFAULT);
        else if(tmp == "2")
            this->ui->LBLMP1->setStyleSheet(TRAINFAULT);
        else if(tmp == "4")
            this->ui->LBLM2->setStyleSheet(TRAINFAULT);
        else if(tmp == "3")
            this->ui->LBLM1->setStyleSheet(TRAINFAULT);

    }

}
void MaintainceCurrentFaultPage::DrawFaults(int i)
{
    for(int j = 0;j<COLUMN;j++)
    {
        if(i == m_currentButtonsDown)//draw down button style
        {
            if(CrrcFault::getCrrcFault()->getCurrentFaultLevel(i+(m_currentPageIndex-1)*MAXCNTPERPAGE) == "1")
            {
                this->m_labels.at(i).at(j)->setStyleSheet(LEVEL1BTNDOWN);
            }else if(CrrcFault::getCrrcFault()->getCurrentFaultLevel(i+(m_currentPageIndex-1)*MAXCNTPERPAGE) == "2")
            {
                this->m_labels.at(i).at(j)->setStyleSheet(LEVEL2BTNDOWN);

            }else if(CrrcFault::getCrrcFault()->getCurrentFaultLevel(i+(m_currentPageIndex-1)*MAXCNTPERPAGE) == "3")
            {
                this->m_labels.at(i).at(j)->setStyleSheet(LEVEL3BTNDOWN);
            }
        }else//draw up button style
        {
            if(CrrcFault::getCrrcFault()->getCurrentFaultLevel(i+(m_currentPageIndex-1)*MAXCNTPERPAGE) == "1")
            {
                this->m_labels.at(i).at(j)->setStyleSheet(LEVEL1BTNUP);
            }else if(CrrcFault::getCrrcFault()->getCurrentFaultLevel(i+(m_currentPageIndex-1)*MAXCNTPERPAGE) == "2")
            {
                this->m_labels.at(i).at(j)->setStyleSheet(LEVEL2BTNUP);

            }else if(CrrcFault::getCrrcFault()->getCurrentFaultLevel(i+(m_currentPageIndex-1)*MAXCNTPERPAGE) == "3")
            {
                this->m_labels.at(i).at(j)->setStyleSheet(LEVEL3BTNUP);
            }
        }
    }



    bool tmp_confirm = CrrcFault::getCrrcFault()->getCurrentFaultConfirm(i+(m_currentPageIndex-1)*MAXCNTPERPAGE);
    this->m_labels.at(i).at(0)->setText((tmp_confirm==true?" ":"*")+
                                        CrrcFault::getCrrcFault()->getCurrentFaultDate(i+(m_currentPageIndex-1)*MAXCNTPERPAGE)+" "+
                                        CrrcFault::getCrrcFault()->getCurrentFaultTime(i+(m_currentPageIndex-1)*MAXCNTPERPAGE));
    this->m_labels.at(i).at(1)->setText(CrrcFault::getCrrcFault()->getCurrentFaultCode(i+(m_currentPageIndex-1)*MAXCNTPERPAGE));
    this->m_labels.at(i).at(2)->setText(CrrcFault::getCrrcFault()->getCurrentFaultName(i+(m_currentPageIndex-1)*MAXCNTPERPAGE));
    this->m_labels.at(i).at(2)->setWordWrap(true);
    this->m_labels.at(i).at(3)->setText(CrrcFault::getCrrcFault()->getCurrentFaultLevel(i+(m_currentPageIndex-1)*MAXCNTPERPAGE));
    this->m_labels.at(i).at(4)->setText(CrrcFault::getCrrcFault()->getCurrentFaultDevice(i+(m_currentPageIndex-1)*MAXCNTPERPAGE));

}

void MaintainceCurrentFaultPage::on_confirmBtn_pressed()
{
    CrrcFault::getCrrcFault()->deleteConfirmFaultByCurrentFaultList(m_currentButtonsDown+(m_currentPageIndex-1)*MAXCNTPERPAGE);
}

void MaintainceCurrentFaultPage::on_BTNHome_pressed()
{
    changePage(uVehicleTrainArea);
}

void MaintainceCurrentFaultPage::on_BTN8_Next_pressed()
{
    if(m_currentPageIndex<m_totalPageIndex)
        m_currentPageIndex++;
}

void MaintainceCurrentFaultPage::on_BTN7_Pre_pressed()
{
    if(m_currentPageIndex>1)
        m_currentPageIndex--;
}

void MaintainceCurrentFaultPage::on_returnBtn_pressed()
{
    changePage(uVehicleTrainArea);
}

