#include "maintainceshowqueryfaultpage.h"
#include "ui_maintainceshowqueryfaultpage.h"

#include "crrcfault.h"

#define MAXCNTPERPAGE 9

#define LEVEL1BTNDOWN   "text-align:left;border:1px solid transparent;background-color:red;color:rgb(0,0,50);font:14px \"微软雅黑\";"
#define LEVEL2BTNDOWN   "text-align:left;border:1px solid transparent;background-color:yellow;color:rgb(0,0,50);font:14px \"微软雅黑\";"
#define LEVEL3BTNDOWN   "text-align:left;border:1px solid transparent;background-color:white;color:rgb(0,0,50);font:14px \"微软雅黑\";"

#define LEVEL1BTNUP   "text-align:left;border:1px solid transparent;background-color:rgb(0,0,50);color:red;font:14px \"微软雅黑\";"
#define LEVEL2BTNUP   "text-align:left;border:1px solid transparent;background-color:rgb(0,0,50);color:yellow;font:14px \"微软雅黑\";"
#define LEVEL3BTNUP   "text-align:left;border:1px solid transparent;background-color:rgb(0,0,50);color:white;font:14px \"微软雅黑\";"

#define TRAINNOFAULT   "color:black;background-color:rgb(170,170,170);"
#define TRAINFAULT   "color:white;background-color:red;"

#define SPARE         "                                    "

MaintainceShowQueryFaultPage::MaintainceShowQueryFaultPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceShowQueryFaultPage)
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
}

MaintainceShowQueryFaultPage::~MaintainceShowQueryFaultPage()
{
    delete ui;
}
void MaintainceShowQueryFaultPage::ButtonsPressEvent()
{
    m_currentButtonsDown = ((QPushButton*)this->sender())->whatsThis().toInt();
    //((QPushButton*)this->sender())->setStyleSheet(LEVEL1BTNDOWN);
}
void MaintainceShowQueryFaultPage::showEvent(QShowEvent *)
{
    m_Detail = "";
    m_currentPageIndex  = 1;
    m_totalPageIndex = 1;
    m_currentPageFaultNum = 0;
    m_totalFaultNum = 0;
    m_currentButtonsDown = 0;
}
void MaintainceShowQueryFaultPage::updatePage()
{
    m_totalFaultNum = CrrcFault::getCrrcFault()->getQueryFault().size();
    //m_totalFaultNum = m_crrcFault->getQueryFault().size();

    if(m_totalFaultNum < 1)
    {
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
                this->m_buttons.at(i)->setText("");
                this->m_buttons.at(i)->setStyleSheet(LEVEL1BTNUP);

            }
        }

        this->Localareaupdate(m_currentPageFaultNum);

    }
}

void MaintainceShowQueryFaultPage::Localareaupdate(int index)
{
    // detial label &&  fault position
    if(m_currentButtonsDown<index)
    {
        this->ui->LBL_Datail->setText("代码: "+CrrcFault::getCrrcFault()->getHistoryFaultCode(CrrcFault::getCrrcFault()->getQueryFault()[m_currentButtonsDown+(m_currentPageIndex-1)*MAXCNTPERPAGE])+"\n"
                                      +CrrcFault::getCrrcFault()->getHistoryFaultDescription(CrrcFault::getCrrcFault()->getQueryFault()[m_currentButtonsDown+(m_currentPageIndex-1)*MAXCNTPERPAGE]));
        QString tmp = CrrcFault::getCrrcFault()->getHistoryFaultPosition(CrrcFault::getCrrcFault()->getQueryFault()[m_currentButtonsDown+(m_currentPageIndex-1)*MAXCNTPERPAGE]);
        this->ui->LBLTC1->setStyleSheet(TRAINNOFAULT);
        this->ui->LBLTC2->setStyleSheet(TRAINNOFAULT);
        this->ui->LBLMP1->setStyleSheet(TRAINNOFAULT);
        this->ui->LBLMP2->setStyleSheet(TRAINNOFAULT);
        this->ui->LBLM1->setStyleSheet(TRAINNOFAULT);
        this->ui->LBLM2->setStyleSheet(TRAINNOFAULT);
        if(tmp == "TC1")
            this->ui->LBLTC1->setStyleSheet(TRAINFAULT);
        else if(tmp == "TC2")
            this->ui->LBLTC2->setStyleSheet(TRAINFAULT);
        else if(tmp == "MP2")
            this->ui->LBLMP2->setStyleSheet(TRAINFAULT);
        else if(tmp == "MP1")
            this->ui->LBLMP1->setStyleSheet(TRAINFAULT);
        else if(tmp == "M2")
            this->ui->LBLM2->setStyleSheet(TRAINFAULT);
        else if(tmp == "M1")
            this->ui->LBLM1->setStyleSheet(TRAINFAULT);

    }

}
void MaintainceShowQueryFaultPage::DrawFaults(int i)
{
    if(i == m_currentButtonsDown)//draw down button style
    {
        if(CrrcFault::getCrrcFault()->getHistoryFaultLevel(CrrcFault::getCrrcFault()->getQueryFault()[i+(m_currentPageIndex-1)*MAXCNTPERPAGE]) == "1")
        {
            this->m_buttons.at(i)->setStyleSheet(LEVEL1BTNDOWN);
        }else if(CrrcFault::getCrrcFault()->getHistoryFaultLevel(CrrcFault::getCrrcFault()->getQueryFault()[i+(m_currentPageIndex-1)*MAXCNTPERPAGE]) == "2")
        {
            this->m_buttons.at(i)->setStyleSheet(LEVEL2BTNDOWN);

        }else if(CrrcFault::getCrrcFault()->getHistoryFaultLevel(CrrcFault::getCrrcFault()->getQueryFault()[i+(m_currentPageIndex-1)*MAXCNTPERPAGE]) == "3")
        {
            this->m_buttons.at(i)->setStyleSheet(LEVEL3BTNDOWN);

        }
    }else//draw up button style
    {
        if(CrrcFault::getCrrcFault()->getHistoryFaultLevel(CrrcFault::getCrrcFault()->getQueryFault()[i+(m_currentPageIndex-1)*MAXCNTPERPAGE]) == "1")
        {
            this->m_buttons.at(i)->setStyleSheet(LEVEL1BTNUP);
        }else if(CrrcFault::getCrrcFault()->getHistoryFaultLevel(CrrcFault::getCrrcFault()->getQueryFault()[i+(m_currentPageIndex-1)*MAXCNTPERPAGE]) == "2")
        {
            this->m_buttons.at(i)->setStyleSheet(LEVEL2BTNUP);

        }else if(CrrcFault::getCrrcFault()->getHistoryFaultLevel(CrrcFault::getCrrcFault()->getQueryFault()[i+(m_currentPageIndex-1)*MAXCNTPERPAGE]) == "3")
        {
            this->m_buttons.at(i)->setStyleSheet(LEVEL3BTNUP);

        }
    }


    QString tmp = CrrcFault::getCrrcFault()->getHistoryFaultEndDate(CrrcFault::getCrrcFault()->getQueryFault()[i+(m_currentPageIndex-1)*MAXCNTPERPAGE]);
    bool tmp_confirm = CrrcFault::getCrrcFault()->getHistoryFaultConfirm(CrrcFault::getCrrcFault()->getQueryFault()[i+(m_currentPageIndex-1)*MAXCNTPERPAGE]);

    if(tmp == "")
        tmp = SPARE;
    else

        tmp = CrrcFault::getCrrcFault()->getHistoryFaultEndDate(CrrcFault::getCrrcFault()->getQueryFault()[i+(m_currentPageIndex-1)*MAXCNTPERPAGE])+" "+
              CrrcFault::getCrrcFault()->getHistoryFaultEndTime(CrrcFault::getCrrcFault()->getQueryFault()[i+(m_currentPageIndex-1)*MAXCNTPERPAGE])+"    ";

    QString tmp_text = (tmp_confirm==true?" ":"*")+CrrcFault::getCrrcFault()->getHistoryFaultStartDate(CrrcFault::getCrrcFault()->getQueryFault()[i+(m_currentPageIndex-1)*MAXCNTPERPAGE])+" "+
                       CrrcFault::getCrrcFault()->getHistoryFaultStartTime(CrrcFault::getCrrcFault()->getQueryFault()[i+(m_currentPageIndex-1)*MAXCNTPERPAGE])+"    "+
                       tmp+
                       CrrcFault::getCrrcFault()->getHistoryFaultName(CrrcFault::getCrrcFault()->getQueryFault()[i+(m_currentPageIndex-1)*MAXCNTPERPAGE]);
    this->m_buttons.at(i)->setText(tmp_text);
}


void MaintainceShowQueryFaultPage::on_BTN7_Pre_pressed()
{
    if(m_currentPageIndex>1)
        m_currentPageIndex--;
}

void MaintainceShowQueryFaultPage::on_BTN8_Next_pressed()
{
    if(m_currentPageIndex<m_totalPageIndex)
        m_currentPageIndex++;
}

void MaintainceShowQueryFaultPage::on_BTNHome_pressed()
{
    changePage(uVehicleTrainArea);
}
void MaintainceShowQueryFaultPage::on_returnBtn_pressed()
{
    changePage(uMaintainceQueryFaultPage);
}
