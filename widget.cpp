#include "widget.h"
#include "ui_widget.h"
#include "mybase.h"
#include "header.h"
#include "qtimer.h"
#include "database.h"
#include "navigator.h"
#include "vehiclerunstatepage.h"
#include "crrcricomvb.h"
#include "crrcfault.h"
#include "simulation.h"
#include "qdesktopwidget.h"
#include "avic_imx.h"

#include "vehiclestationbar.h"
#include "vehicletrainarea.h"
#include "vehiclestatusarea.h"
#include "vehicleinformationarea.h"
#include "vehiclepasswordpage.h"

#include "vehicleairconditionerpage.h"
#include "vehicleauxiliarypage.h"
#include "vehiclelinecircuitbreakerpage.h"
#include "vehicledoorpage.h"
#include "vehiclepispage.h"
#include "vehiclebrakepage.h"
#include "vehicletractpage.h"
#include "vehiclefirewarningpage.h"
#include "vehicleaircompressorpage.h"
#include "vehicletopologypage.h"
#include "vehiclesetpage.h"
#include "vehiclesetstationpage.h"
#include "vehiclesetairconditionpage.h"
#include "vehiclemaintainpage.h"
#include "vehiclemthistoryfaultpage.h"
#include "vehiclemttimesetpage.h"
#include "maintainceallportspage.h"
#include "maintainceinitsetpage.h"
#include "maintainceriompage.h"
#include "maintaincewheeldiametersetpage.h"
#include "maintaincesoftwareversionpage.h"
#include "maintaincedatamanagepage.h"
#include "maintainceresetexcisionpage.h"
#include "maintaincecommunicationstatepage.h"
#include "vehiclesetbrakeparampage.h"
#include "vehiclesetintensitycontrolpage.h"
#include "vehiclesetbraketestpage.h"
#include "vehiclemaintaincetractsubsystempage.h"
#include "maintaincebrakesubsystempage.h"
#include "maintainceauxiliarysubsystempage.h"
#include "maintaincerunninggearsubsystempage.h"
#include "faulteventpage.h"
#include "bypasspage.h"
#include "bypasspage2.h"


#include "maintaincecurrentfaultpage.h"
#include "maintaincehistoryfaultpage.h"
#include "maintainceshowqueryfaultpage.h"
#include "maintaincequeryfaultpage.h"

#include "h8.h"
#include "warnningdialog.h"


#include "helppage.h"
#include "helppage2.h"
#include "helppage3.h"
#include "helppage4.h"
#include "helppage5.h"

#include "maintaincepisautotest.h"
#include "maintainceaccumulatedatapage.h"
#include "addsubtracttestpage.h"

#include "passwordpage.h"
#include "maintainceaccumulatorsubsystempage.h"
#include "maintaincebatterysubsystempage.h"
#include "vehiclesetsimlatestation.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //avic_imx_init(1);
    QDesktopWidget *desktop = QApplication::desktop();

    ExternalDevice = new AVIC_ExternalDevice(this);

    if (desktop->width() == 800 && desktop->height() == 600)
    {
        this->showFullScreen();
    }
    else
    {
        this->move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);
    }

    this->database = new Database();
    MyBase::database = this->database;

    this->timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePage()));

    if(CrrcFault::initCrrcFault("fault_type_HHL.db","fault_DB_HHL.db"))
    {
        crrcFault = CrrcFault::getCrrcFault();
    }else
    {
        logger()->error("故障文件初始化错误");
    }
    crrcRicoMvb = CrrcRicoMvb::getcrrcRicoMvb();

    this->simulation=new Simulation();
    this->simulation->hide();

    this->header = new Header(this);
    this->header->setMyBase(uTop,QString("标题栏"));
    this->header->show();

    this->navigator = new Navigator(this);
    this->navigator->setMyBase(uBottom,QString("导航栏"));
    this->navigator->show();

    this->vehicleRunStatePage = new VehicleRunStatePage(this);
    this->vehicleRunStatePage->setMyBase(uTrain,QString("一般信息"));
    this->vehicleRunStatePage->hide();;

    this->vehicleStationBar = new VehicleStationBar(this);
    this->vehicleStationBar->setMyBase(uStation,QString("站点信息"));
    this->vehicleStationBar->show();

    this->vehicleTrainArea = new VehicleTrainArea(this);
    this->vehicleTrainArea->setMyBase(uMainRunstatus,QString("主界面"));
    this->vehicleTrainArea->show();

    this->vehicleStatusArea = new VehicleStatusArea(this);
    this->vehicleStatusArea->setMyBase(uStatus,QString("过程信息"));
    this->vehicleStatusArea->show();

    this->vehicleInformationArea = new VehicleInformationArea(this);
    this->vehicleInformationArea->setMyBase(uInformation,QString("提示信息"));
    this->vehicleInformationArea->show();

    this->vehiclePasswordPage = new VehiclePasswordPage(this);
    this->vehiclePasswordPage->setMyBase(uMiddle,QString("密码页面"));
    this->vehiclePasswordPage->hide();

    this->vehicleAirConditionerPage=new VehicleAirConditionerPage(this);
    this->vehicleAirConditionerPage->setMyBase(uTrain,QString("空调界面"));
    this->vehicleAirConditionerPage->hide();

    this->vehicleAuxiliaryPage=new VehicleAuxiliaryPage(this);
    this->vehicleAuxiliaryPage->setMyBase(uTrain,QString("辅助界面"));
    this->vehicleAuxiliaryPage->hide();

    this->vehicleLineCircuitBreakerPage=new VehicleLineCircuitBreakerPage(this);
    this->vehicleLineCircuitBreakerPage->setMyBase(uTrain,QString("复位界面"));
    this->vehicleLineCircuitBreakerPage->hide();

    this->vehicleDoorPage=new VehicleDoorPage(this);
    this->vehicleDoorPage->setMyBase(uTrain,QString("车门界面"));
    this->vehicleDoorPage->hide();

    this->vehiclePISPage=new VehiclePISPage(this);
    this->vehiclePISPage->setMyBase(uTrain,QString("PIS界面"));
    this->vehiclePISPage->hide();

    this->vehicleBrakePage=new VehicleBrakePage(this);
    this->vehicleBrakePage->setMyBase(uTrain,QString("制动界面"));
    this->vehicleBrakePage->hide();

    this->vehicleTractPage=new VehicleTractPage(this);
    this->vehicleTractPage->setMyBase(uTrain,QString("牵引界面"));
    this->vehicleTractPage->hide();

    this->vehicleFireWarningPage=new VehicleFireWarningPage(this);
    this->vehicleFireWarningPage->setMyBase(uTrain,QString("火灾报警"));
    this->vehicleFireWarningPage->hide();

    this->vehicleAirCompressorPage=new VehicleAirCompressorPage(this);
    this->vehicleAirCompressorPage->setMyBase(uTrain,QString("空压机界面"));
    this->vehicleAirCompressorPage->hide();

    this->vehicleTopologyPage=new VehicleTopologyPage(this);
    this->vehicleTopologyPage->setMyBase(uTolopogy,QString("拓扑界面"));
    this->vehicleTopologyPage->hide();

    this->vehicleSetPage=new VehicleSetPage(this);
    this->vehicleSetPage->setMyBase(uMiddle,QString("设置界面"));
    this->vehicleSetPage->hide();

    this->vehicleSetStationPage=new VehicleSetStationPage(this);
    this->vehicleSetStationPage->setMyBase(uTolopogy,QString("紧急广播"));
    this->vehicleSetStationPage->hide();

    this->vehicleSetAirConditionPage=new VehicleSetAirConditionPage(this);
    this->vehicleSetAirConditionPage->setMyBase(uMiddle,QString("空调设置界面"));
    this->vehicleSetAirConditionPage->hide();

    this->vehicleSetBrakeParamPage=new VehicleSetBrakeParamPage(this);
    this->vehicleSetBrakeParamPage->setMyBase(uMiddle,QString("制动参数界面"));
    this->vehicleSetBrakeParamPage->hide();

    this->vehicleSetIntensityControlPage=new VehicleSetIntensityControlPage(this);
    this->vehicleSetIntensityControlPage->setMyBase(uMiddle,QString("亮度调节"));
    this->vehicleSetIntensityControlPage->hide();

    this->vehicleSetBrakeTestPage=new VehicleSetBrakeTestPage(this);
    this->vehicleSetBrakeTestPage->setMyBase(uMiddle,"制动自检");
    this->vehicleSetBrakeTestPage->hide();


    this->vehicleMaintainPage=new VehicleMaintainPage(this);
    this->vehicleMaintainPage->setMyBase(uMiddle,QString("维护界面"));
    this->vehicleMaintainPage->hide();

    this->vehicleMTTimeSetPage=new VehicleMTTimeSetPage(this);
    this->vehicleMTTimeSetPage->setMyBase(uMiddle,QString("时间设定界面"));
    this->vehicleMTTimeSetPage->hide();

    this->vehicleMTHistoryFaultPage=new VehicleMTHistoryFaultPage(this);
    this->vehicleMTHistoryFaultPage->setMyBase(uMiddle,QString("故障履历界面"));
    this->vehicleMTHistoryFaultPage->hide();

    this->vehicleMaintainceAllPortsPage=new MaintainceAllPortsPage(this);
    this->vehicleMaintainceAllPortsPage->setMyBase(uHuge,QString("数据监控界面"));
    this->vehicleMaintainceAllPortsPage->hide();
   // this->vehicleMaintainceAllPortsPage->installMvb(this->crrcRicoMvb);

    this->vehicleMaintainceInitSetPage=new MaintainceInitSetPage(this);
    this->vehicleMaintainceInitSetPage->setMyBase(uMiddle,QString("显示屏设置界面"));
    this->vehicleMaintainceInitSetPage->hide();

    this->vehicleMaintainceRIOMPage=new MaintainceRIOMPage(this);
    this->vehicleMaintainceRIOMPage->setMyBase(uMiddle,QString("RIOM界面"));
    this->vehicleMaintainceRIOMPage->hide();

    this->vehicleMaintainceWheelDiameterSetPage=new MaintainceWheelDiameterSetPage(this);
    this->vehicleMaintainceWheelDiameterSetPage->setMyBase(uMiddle,QString("轮径设置界面"));
    this->vehicleMaintainceWheelDiameterSetPage->hide();

    this->vehicleMaintainceSoftwareVersionPage=new MaintainceSoftwareVersionPage(this);
    this->vehicleMaintainceSoftwareVersionPage->setMyBase(uMiddle,QString("版本信息界面"));
    this->vehicleMaintainceSoftwareVersionPage->hide();

    this->vehicleMaintainceDataManagePage=new MaintainceDataManagePage(this);
    this->vehicleMaintainceDataManagePage->setMyBase(uMiddle,QString("数据管理界面"));
    this->vehicleMaintainceDataManagePage->hide();

    this->vehicleMaintainceResetExcisionPage=new MaintainceResetExcisionPage(this);
    this->vehicleMaintainceResetExcisionPage->setMyBase(uMiddle,QString("切除界面"));
    this->vehicleMaintainceResetExcisionPage->hide();

    this->vehicleMaintainceCommunicationStatePage=new MaintainceCommunicationStatePage(this);
    this->vehicleMaintainceCommunicationStatePage->setMyBase(uMiddle,QString("通信状态界面"));
    this->vehicleMaintainceCommunicationStatePage->hide();

    this->vehicleMaintainceTractSubsystemPage=new VehicleMaintainceTractSubsystemPage(this);
    this->vehicleMaintainceTractSubsystemPage->setMyBase(uMiddle,QString("牵引子系统界面"));
    this->vehicleMaintainceTractSubsystemPage->hide();

    this->vehicleMaintainceBrakeSubsystemPage=new MaintainceBrakeSubsystemPage(this);
    this->vehicleMaintainceBrakeSubsystemPage->setMyBase(uMiddle,QString("制动子系统界面"));
    this->vehicleMaintainceBrakeSubsystemPage->hide();

    this->vehicleMaintainceAuxiliarySubsystemPage=new MaintainceAuxiliarySubsystemPage(this);
    this->vehicleMaintainceAuxiliarySubsystemPage->setMyBase(uMiddle,QString("辅助子系统界面"));
    this->vehicleMaintainceAuxiliarySubsystemPage->hide();

    this->vehicleMaintainceRunningGearSubsystemPage=new MaintainceRunningGearSubsystemPage(this);
    this->vehicleMaintainceRunningGearSubsystemPage->setMyBase(uMiddle,QString("走行部子系统界面"));
    this->vehicleMaintainceRunningGearSubsystemPage->hide();

    this->maintainceAccumulatorSubsystemPage=new MaintainceAccumulatorSubsystemPage(this);
    this->maintainceAccumulatorSubsystemPage->setMyBase(uMiddle,QString("踏面清扫测试界面"));
    this->maintainceAccumulatorSubsystemPage->hide();

    this->maintainceBatterySubsystemPage=new MaintainceBatterySubsystemPage(this);
    this->maintainceBatterySubsystemPage->setMyBase(uMiddle,QString("蓄电池子系统界面"));
    this->maintainceBatterySubsystemPage->hide();

    this->vehicleFaultEventPage=new FaultEventPage(this);
    this->vehicleFaultEventPage->setMyBase(uMiddle,QString("当前故障页面"));
    this->vehicleFaultEventPage->hide();

    this->vehicleByPassPage=new ByPassPage(this);
    this->vehicleByPassPage->setMyBase(uMiddle,QString("旁路界面1"));
    this->vehicleByPassPage->hide();

    this->vehicleByPassPage2 = new ByPassPage2(this);
    this->vehicleByPassPage2->setMyBase(uMiddle,QString("旁路界面2"));
    this->vehicleByPassPage2->hide();

    this->maintainceCurrentFaultPage= new MaintainceCurrentFaultPage(this);
    this->maintainceCurrentFaultPage->setMyBase(uMiddle,QString("当前故障"));
    this->maintainceCurrentFaultPage->hide();

    this->maintainceHistoryFaultPage= new MaintainceHistoryFaultPage(this);
    this->maintainceHistoryFaultPage->setMyBase(uMiddle,QString("历史故障"));
    this->maintainceHistoryFaultPage->hide();

    this->maintainceQueryFaultPage= new MaintainceQueryFaultPage(this);
    this->maintainceQueryFaultPage->setMyBase(uMiddle,QString("故障检索"));
    this->maintainceQueryFaultPage->hide();

    this->maintainceShowQueryFaultPage= new MaintainceShowQueryFaultPage(this);
    this->maintainceShowQueryFaultPage->setMyBase(uMiddle,QString("检索显示"));
    this->maintainceShowQueryFaultPage->hide();

    this->vehicleHelpPage=new HelpPage(this);
    this->vehicleHelpPage->setMyBase(uMiddle,QString("帮助界面1"));
    this->vehicleHelpPage->hide();

    this->vehicleHelpPage2=new HelpPage2(this);
    this->vehicleHelpPage2->setMyBase(uMiddle,QString("帮助界面2"));
    this->vehicleHelpPage2->hide();

    this->vehicleHelpPage3=new HelpPage3(this);
    this->vehicleHelpPage3->setMyBase(uMiddle,QString("帮助界面3"));
    this->vehicleHelpPage3->hide();

    this->vehicleHelpPage4=new HelpPage4(this);
    this->vehicleHelpPage4->setMyBase(uMiddle,QString("帮助界面4"));
    this->vehicleHelpPage4->hide();

    this->vehicleHelpPage5=new HelpPage5(this);
    this->vehicleHelpPage5->setMyBase(uMiddle,QString("帮助界面5"));
    this->vehicleHelpPage5->hide();

    this->maintaincePISAutoTest=new MaintaincePISAutoTest(this);
    this->maintaincePISAutoTest->setMyBase(uMiddle,QString("自动报站测试"));
    this->maintaincePISAutoTest->hide();

    this->maintainceAccumulateDataPage=new MaintainceAccumulateDataPage(this);
    this->maintainceAccumulateDataPage->setMyBase(uMiddle,QString("累计数据"));
    this->maintainceAccumulateDataPage->hide();

    this->addSubtractTestPage=new AddSubtractTestPage(this);
    this->addSubtractTestPage->setMyBase(uMiddle,QString("加减速度测试"));
    this->addSubtractTestPage->hide();

    this->passwordPage=new PasswordPage(this);
    this->passwordPage->setMyBase(uMiddle,QString("密码页面"));
    this->passwordPage->hide();

    this->vehicleSetSimlateStation=new VehicleSetSimlateStation(this);
    this->vehicleSetSimlateStation->setMyBase(uMiddle,QString("半自动报站"));
    this->vehicleSetSimlateStation->hide();

    //init H8 config
    H8::initH8("/dev/ttyUSB_SC");
    H8::getH8()->setBrightness(0);

    this->widgets.insert(uVehicleRunStatePage,this->vehicleRunStatePage);
    this->widgets.insert(uVehicleStationBar,this->vehicleStationBar);
    this->widgets.insert(uVehicleTrainArea,this->vehicleTrainArea);
    this->widgets.insert(uVehicleStatusArea,this->vehicleStatusArea);
    this->widgets.insert(uVehicleInformationArea,this->vehicleInformationArea);
    this->widgets.insert(uVehiclePasswordPage,this->vehiclePasswordPage);
    this->widgets.insert(uVehicleAirConditionerPage,this->vehicleAirConditionerPage);
    this->widgets.insert(uVehicleAuxiliaryPage,this->vehicleAuxiliaryPage);
    this->widgets.insert(uVehicleLineCircuitBreakerPage,this->vehicleLineCircuitBreakerPage);
    this->widgets.insert(uVehicleDoorPage,this->vehicleDoorPage);
    this->widgets.insert(uVehiclePISPage,this->vehiclePISPage);
    this->widgets.insert(uVehicleBrakePage,this->vehicleBrakePage);
    this->widgets.insert(uVehicleTractPage,this->vehicleTractPage);
    this->widgets.insert(uVehicleFireWarningPage,this->vehicleFireWarningPage);
    this->widgets.insert(uVehicleAirCompressorPage,this->vehicleAirCompressorPage);
    this->widgets.insert(uVehicleTopologyPage,this->vehicleTopologyPage);
    this->widgets.insert(uVehicleSetPage,this->vehicleSetPage);
    this->widgets.insert(uVehicleSetStationPage,this->vehicleSetStationPage);
    this->widgets.insert(uVehicleSetAirConditionPage,this->vehicleSetAirConditionPage);
    this->widgets.insert(uVehicleMaintainPage,this->vehicleMaintainPage);
    this->widgets.insert(uVehicleMTHistoryFaultPage,this->vehicleMTHistoryFaultPage);
    this->widgets.insert(uVehicleMTTimeSetPage,this->vehicleMTTimeSetPage);
    this->widgets.insert(uVehicleMaintainceAllPortsPage,this->vehicleMaintainceAllPortsPage);
    this->widgets.insert(uVehicleMaintainceInitSetPage,this->vehicleMaintainceInitSetPage);
    this->widgets.insert(uVehicleMaintainceRIOMPage,this->vehicleMaintainceRIOMPage);
    this->widgets.insert(uVehicleMaintainceWheelDiameterSetPage,this->vehicleMaintainceWheelDiameterSetPage);
    this->widgets.insert(uVehicleMaintainceSoftwareVersionPage,this->vehicleMaintainceSoftwareVersionPage);
    this->widgets.insert(uVehicleMaintainceDataManagePage,this->vehicleMaintainceDataManagePage);
    this->widgets.insert(uVehicleMaintainceResetExcisionPage,this->vehicleMaintainceResetExcisionPage);
    this->widgets.insert(uVehicleMaintainceCommunicationStatePage,this->vehicleMaintainceCommunicationStatePage);
    this->widgets.insert(uVehicleSetBrakeParamPage,this->vehicleSetBrakeParamPage);
    this->widgets.insert(uVehicleSetIntensityControlPage,this->vehicleSetIntensityControlPage);
    this->widgets.insert(uVehicleSetBrakeTestPage,this->vehicleSetBrakeTestPage);
    this->widgets.insert(uVehicleMaintainceTractSubsystemPage,this->vehicleMaintainceTractSubsystemPage);
    this->widgets.insert(uVehicleMaintainceBrakeSubsystemPage,this->vehicleMaintainceBrakeSubsystemPage);
    this->widgets.insert(uVehicleMaintainceAuxiliarySubsystemPage,this->vehicleMaintainceAuxiliarySubsystemPage);
    this->widgets.insert(uVehicleMaintainceRunningGearSubsystemPage,this->vehicleMaintainceRunningGearSubsystemPage);
    this->widgets.insert(uVehicleFaultEventPage,this->vehicleFaultEventPage);
    this->widgets.insert(uVehicleByPassPage,this->vehicleByPassPage);
    this->widgets.insert(uVehicleByPassPage2,this->vehicleByPassPage2);

    this->widgets.insert(uMaintainceCurrentFaultPage ,this->maintainceCurrentFaultPage);
    this->widgets.insert(uMaintainceHistoryFaultPage,this->maintainceHistoryFaultPage);
    this->widgets.insert(uMaintainceQueryFaultPage,this->maintainceQueryFaultPage);
    this->widgets.insert(uMaintainceShowQueryFaultPage,this->maintainceShowQueryFaultPage);


    this->widgets.insert(uVehicleHelpPage,this->vehicleHelpPage);
    this->widgets.insert(uVehicleHelpPage2,this->vehicleHelpPage2);
    this->widgets.insert(uVehicleHelpPage3,this->vehicleHelpPage3);
    this->widgets.insert(uVehicleHelpPage4,this->vehicleHelpPage4);
    this->widgets.insert(uVehicleHelpPage5,this->vehicleHelpPage5);

    this->widgets.insert(uMaintaincePISAutoTest,this->maintaincePISAutoTest);
    this->widgets.insert(uMaintainceAccumulateDataPage,this->maintainceAccumulateDataPage);

    this->widgets.insert(uMaintainceAddSubtractTestPage,this->addSubtractTestPage);
    this->widgets.insert(uMaintaincePasswordPage,this->passwordPage);
    this->widgets.insert(uMaintainceAccumulatorSubsystemPage,this->maintainceAccumulatorSubsystemPage);
    this->widgets.insert(uMaintainceBatterySubsystemPage,this->maintainceBatterySubsystemPage);
    this->widgets.insert(uVehicleSetSimlateStation,this->vehicleSetSimlateStation);

}

Widget::~Widget()
{
    //avic_imx_destory();
    delete ui;
}
void Widget::updatePage()
{

    static QTime timeStart(QTime::currentTime());

    static int counter = 1;
    this->header->updatePage();
    this->navigator->updatePage();
    if(this->widgets[MyBase::currentPage]->Position == uTrain || this->widgets[MyBase::currentPage]->Position == uMainRunstatus||this->widgets[MyBase::currentPage]->Position == uTolopogy)
    {
        this->vehicleStationBar->updatePage();
        this->vehicleStatusArea->updatePage();
        this->vehicleInformationArea->updatePage();
    }
    this->vehicleTopologyPage->updatePage();
    this->widgets[MyBase::currentPage]->updatePage();

    // update comm data,some base logic
    if(counter%2 == 0)
    {
        crrcRicoMvb->synchronizeMvbData();
        this->database->updateDatabse(crrcRicoMvb);
        this->simulation->installMvb(crrcRicoMvb);
    }


    QDateTime dateTimeLocal;
    if(this->database->CTALL_CCUOnline_B1)
    {
        VCUtime2HMI10s();

        QDate date(this->database->CTALL_SysTimeYear_U8+2000,this->database->CTALL_SysTimeMonth_U8,this->database->CTALL_SysTimeDay_U8);
        QTime time(this->database->CTALL_SysTimeHour_U8,this->database->CTALL_SysTimeMinute_U8,this->database->CTALL_SysTimeSecond_U8);
        this->database->HMI_DateTime_foruse.setDate(date);
        this->database->HMI_DateTime_foruse.setTime(time);

        if(this->database->HMI_DateTime_foruse.isValid())
        {

        }else
        {
            this->database->HMI_DateTime_foruse.setDate(dateTimeLocal.currentDateTime().date());
            this->database->HMI_DateTime_foruse.setTime(dateTimeLocal.currentDateTime().time());
        }
    }else
    {
        this->database->HMI_DateTime_foruse.setDate(dateTimeLocal.currentDateTime().date());
        this->database->HMI_DateTime_foruse.setTime(dateTimeLocal.currentDateTime().time());
    }
    this->crrcFault->getLocalDateTime(database->HMI_DateTime_foruse);

    // start fault scanning thread
    static int faultdelaycnt = 0;
    if ((faultdelaycnt++ > 0) )
    {
        crrcFault->start();
        faultdelaycnt = 60;
    }


    counter >= 100 ? (counter = 1) : (counter ++);


    if (timeStart.msecsTo(QTime::currentTime()) > 500)
    {
        _LOG << "update page time out fault" << timeStart.msecsTo(QTime::currentTime()) << ", please check it";
    }

    timeStart = QTime::currentTime();

//    if(database->CTR1_DOBSOI_B1 || database->CTR4_DOBSOI_B1)
//    {
//        //avic_beep(1);
//    }else
//    {
//        //avic_beep(0);
//    }

    if((database->CTD_TrainSpeed_U16*0.1)>=125)
    {
        AVIC_ExternalDevice::getAVIC_ExternalDevice()->setBuzzerOn();
    }
    else
    {
        AVIC_ExternalDevice::getAVIC_ExternalDevice()->setBuzzeroff();
    }

}
void Widget::changePage(int page)
{

    foreach (int key, this->widgets.keys())
    {

        if (key == page)
        {
            MyBase::currentPage = page;
            this->widgets[page]->show();

            this->header->setPageName(this->widgets[page]->name);

            if(this->widgets[page]->Position == uHuge)
            {
                this->header->hide();
                this->navigator->hide();
                this->vehicleStationBar->hide();
                this->vehicleStatusArea->hide();
                this->vehicleInformationArea->hide();
                this->vehicleTrainArea->hide();
                this->vehicleStatusArea->refreshAllButton();

            }else if(this->widgets[key]->Position == uMiddle)
            {

                this->header->show();
                this->navigator->hide();
                this->vehicleStationBar->hide();
                this->vehicleStatusArea->hide();
                this->vehicleInformationArea->hide();
                this->vehicleTrainArea->hide();
                this->vehicleStatusArea->refreshAllButton();

            }else if(this->widgets[key]->Position == uTrain)
            {

                this->header->show();
                this->navigator->show();
                this->vehicleStationBar->show();
                this->vehicleStatusArea->show();
                this->vehicleInformationArea->show();
                //this->vehicleTrainArea->hide();
            } else if(this->widgets[key]->Position==uTolopogy)
            {
                if(uVehicleSetStationPage == key)
                {
                    this->header->show();
                    this->navigator->show();
                    this->vehicleStationBar->show();
                    this->vehicleInformationArea->show();
                }else
                {
                    //拓扑界面单独设置了一种模式
                    this->header->show();
                    this->navigator->show();
                    this->vehicleStationBar->show();
                    this->vehicleTopologyPage->show();
                    this->vehicleInformationArea->show();
                }
            }
            else if(this->widgets[key]->Position==uMainRunstatus)
            {

                this->header->show();
                this->navigator->show();
                this->vehicleStationBar->show();
                this->vehicleStatusArea->show();
                this->vehicleStatusArea->refreshAllButton();//点击HOME按键的时候刷新按键的状态
                this->vehicleInformationArea->show();
            }
            _LOG << "change page to" << this->widgets[page]->name;
        }
        else
        {
            this->widgets[key]->hide();
        }
    }
}
void Widget::showEvent(QShowEvent *)
{
    this->header->setPageName(this->widgets[uVehicleTrainArea]->name);

    if(MainGetDefaultPara::configureValid())
    {
#ifndef WINDOWS_MODE
        if(database->HMIPosition == 1)//config  sourcePORT and IP
        {
            //HMI-CCU
            system("ifconfig eth0 192.168.2.31");
            if(!crrcRicoMvb->initializeMvb())
            {
                logger()->error("MVB板卡初始化失败");
            }
            //HMI-CCU
            crrcRicoMvb->addSourcePort(0x310,MVB_FCode4,64);
            crrcRicoMvb->addSourcePort(0x311,MVB_FCode4,64);

            crrcRicoMvb->addSinkPort(0x320,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x321,MVB_FCode4,64);

        }else if(database->HMIPosition == 2)
        {
            system("ifconfig eth0 192.168.2.32");
            if(!crrcRicoMvb->initializeMvb())
            {
                logger()->error("MVB板卡初始化失败");
            }
            //HMI-CCU
            crrcRicoMvb->addSinkPort(0x310,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x311,MVB_FCode4,64);

            crrcRicoMvb->addSourcePort(0x320,MVB_FCode4,64);
            crrcRicoMvb->addSourcePort(0x321,MVB_FCode4,64);

        }
        //add ports
        {
            crrcRicoMvb->addSinkPort(0xfff,MVB_FCode4,256);
            //CCU-ALL
            crrcRicoMvb->addSinkPort(0xF,MVB_FCode3,256);

            //CCU-HMI
            crrcRicoMvb->addSinkPort(0x308,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x309,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x30A,MVB_FCode4,64);


            //RIOM-CCU
            crrcRicoMvb->addSinkPort(0x110,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x111,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x112,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x120,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x121,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x130,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x131,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x140,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x141,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x142,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x150,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x151,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x160,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x161,MVB_FCode4,64);


            //ERM-CCU
            crrcRicoMvb->addSinkPort(0x210,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x211,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x212,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x213,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x220,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x221,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x222,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x223,MVB_FCode4,64);

            //TCU-CCU
            crrcRicoMvb->addSinkPort(0x510,MVB_FCode4,32);
            crrcRicoMvb->addSinkPort(0x511,MVB_FCode3,512);
            crrcRicoMvb->addSinkPort(0x512,MVB_FCode3,512);
            crrcRicoMvb->addSinkPort(0x513,MVB_FCode2,64);

            crrcRicoMvb->addSinkPort(0x520,MVB_FCode4,32);
            crrcRicoMvb->addSinkPort(0x521,MVB_FCode3,512);
            crrcRicoMvb->addSinkPort(0x522,MVB_FCode3,512);
            crrcRicoMvb->addSinkPort(0x523,MVB_FCode2,64);

            crrcRicoMvb->addSinkPort(0x530,MVB_FCode4,32);
            crrcRicoMvb->addSinkPort(0x531,MVB_FCode3,512);
            crrcRicoMvb->addSinkPort(0x532,MVB_FCode3,512);
            crrcRicoMvb->addSinkPort(0x533,MVB_FCode2,64);

            crrcRicoMvb->addSinkPort(0x540,MVB_FCode4,32);
            crrcRicoMvb->addSinkPort(0x541,MVB_FCode3,512);
            crrcRicoMvb->addSinkPort(0x542,MVB_FCode3,512);
            crrcRicoMvb->addSinkPort(0x543,MVB_FCode2,64);

            crrcRicoMvb->addSinkPort(0x550,MVB_FCode4,32);
            crrcRicoMvb->addSinkPort(0x551,MVB_FCode3,512);
            crrcRicoMvb->addSinkPort(0x552,MVB_FCode3,512);
            crrcRicoMvb->addSinkPort(0x553,MVB_FCode2,64);

            crrcRicoMvb->addSinkPort(0x560,MVB_FCode4,32);
            crrcRicoMvb->addSinkPort(0x561,MVB_FCode3,512);
            crrcRicoMvb->addSinkPort(0x562,MVB_FCode3,512);
            crrcRicoMvb->addSinkPort(0x563,MVB_FCode2,64);



            //ACU-CCU
            crrcRicoMvb->addSinkPort(0x610,MVB_FCode4,256);
            crrcRicoMvb->addSinkPort(0x620,MVB_FCode4,256);


            //BCU-CCU
            crrcRicoMvb->addSinkPort(0x410,MVB_FCode4,512);
            crrcRicoMvb->addSinkPort(0x411,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x412,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x413,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x414,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x415,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x416,MVB_FCode4,64);

            crrcRicoMvb->addSinkPort(0x420,MVB_FCode4,512);
            crrcRicoMvb->addSinkPort(0x421,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x422,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x423,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x424,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x425,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x426,MVB_FCode4,64);

            //EDCU-CCU
            crrcRicoMvb->addSinkPort(0x710,MVB_FCode4,1024);
            crrcRicoMvb->addSinkPort(0x711,MVB_FCode4,512);
            crrcRicoMvb->addSinkPort(0x712,MVB_FCode4,1024);

            crrcRicoMvb->addSinkPort(0x720,MVB_FCode4,1024);
            crrcRicoMvb->addSinkPort(0x721,MVB_FCode4,512);
            crrcRicoMvb->addSinkPort(0x722,MVB_FCode4,1024);

            crrcRicoMvb->addSinkPort(0x730,MVB_FCode4,1024);
            crrcRicoMvb->addSinkPort(0x731,MVB_FCode4,512);
            crrcRicoMvb->addSinkPort(0x732,MVB_FCode4,1024);

            crrcRicoMvb->addSinkPort(0x740,MVB_FCode4,1024);
            crrcRicoMvb->addSinkPort(0x741,MVB_FCode4,512);
            crrcRicoMvb->addSinkPort(0x742,MVB_FCode4,1024);

            crrcRicoMvb->addSinkPort(0x750,MVB_FCode4,1024);
            crrcRicoMvb->addSinkPort(0x751,MVB_FCode4,512);
            crrcRicoMvb->addSinkPort(0x752,MVB_FCode4,1024);

            crrcRicoMvb->addSinkPort(0x760,MVB_FCode4,1024);
            crrcRicoMvb->addSinkPort(0x761,MVB_FCode4,512);
            crrcRicoMvb->addSinkPort(0x762,MVB_FCode4,1024);

            crrcRicoMvb->addSinkPort(0x770,MVB_FCode4,1024);
            crrcRicoMvb->addSinkPort(0x771,MVB_FCode4,512);
            crrcRicoMvb->addSinkPort(0x772,MVB_FCode4,1024);

            crrcRicoMvb->addSinkPort(0x780,MVB_FCode4,1024);
            crrcRicoMvb->addSinkPort(0x781,MVB_FCode4,512);
            crrcRicoMvb->addSinkPort(0x782,MVB_FCode4,1024);

            crrcRicoMvb->addVirtualPort(0xf910,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf911,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf710,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf711,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf712,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf730,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf731,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf732,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf750,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf751,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf752,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf770,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf771,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf772,MVB_FCode4);

            crrcRicoMvb->addVirtualPort(0xf410,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf411,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf412,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf413,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf414,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf415,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf416,MVB_FCode4);

            crrcRicoMvb->addVirtualPort(0xf810,MVB_FCode4);

            crrcRicoMvb->addVirtualPort(0xf210,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf211,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf212,MVB_FCode4);
            crrcRicoMvb->addVirtualPort(0xf213,MVB_FCode4);


            //HVAC-CCU
            crrcRicoMvb->addSinkPort(0xA10,MVB_FCode4,512);
            crrcRicoMvb->addSinkPort(0xA20,MVB_FCode4,512);
            crrcRicoMvb->addSinkPort(0xA30,MVB_FCode4,512);
            crrcRicoMvb->addSinkPort(0xA40,MVB_FCode4,512);
            //CCU-HVAC
            //crrcRicoMvb->addSinkPort(0xA18,MVB_FCode4,512);
            //crrcRicoMvb->addSinkPort(0xA28,MVB_FCode4,512);
            //crrcRicoMvb->addSinkPort(0xA38,MVB_FCode4,512);
            //crrcRicoMvb->addSinkPort(0xA48,MVB_FCode4,512);

            //ATC-CCU
            crrcRicoMvb->addSinkPort(0xB10,MVB_FCode4,512);
            crrcRicoMvb->addSinkPort(0xB20,MVB_FCode4,512);
            crrcRicoMvb->addVirtualPort(0xfB10,MVB_FCode4);

            //PIS-CCU
            crrcRicoMvb->addSinkPort(0x910,MVB_FCode4,256);
            crrcRicoMvb->addSinkPort(0x911,MVB_FCode2,512);
            crrcRicoMvb->addSinkPort(0x920,MVB_FCode4,256);
            crrcRicoMvb->addSinkPort(0x921,MVB_FCode2,512);


            //FAS-CCU
            crrcRicoMvb->addSinkPort(0x810,MVB_FCode3,512);
            crrcRicoMvb->addSinkPort(0x820,MVB_FCode3,512);

            //PCU-CCU
            crrcRicoMvb->addSinkPort(0xC10,MVB_FCode4,64);


            //CCU-RIOM
            crrcRicoMvb->addSinkPort(0x118,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x128,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x138,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x148,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x158,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0x168,MVB_FCode4,64);

            //CCU-ERM
            crrcRicoMvb->addSinkPort(0x208,MVB_FCode4,128);

            //CCU-TCU
            crrcRicoMvb->addSinkPort(0x518,MVB_FCode4,32);
            crrcRicoMvb->addSinkPort(0x528,MVB_FCode4,32);
            crrcRicoMvb->addSinkPort(0x538,MVB_FCode4,32);
            crrcRicoMvb->addSinkPort(0x548,MVB_FCode4,32);
            crrcRicoMvb->addSinkPort(0x558,MVB_FCode4,32);
            crrcRicoMvb->addSinkPort(0x568,MVB_FCode4,32);


            //CCU-ACU
            crrcRicoMvb->addSinkPort(0x618,MVB_FCode1,64);
            crrcRicoMvb->addSinkPort(0x628,MVB_FCode1,64);


            //CCU-BCU
            crrcRicoMvb->addSinkPort(0x418,MVB_FCode4,32);

            //CCU-EDCU
            crrcRicoMvb->addSinkPort(0x708,MVB_FCode4,512);



//            //CCU-TCU-public
//            crrcRicoMvb->addSinkPort(0x800,MVB_FCode2,512);


            //CCU-HVAC
            crrcRicoMvb->addSinkPort(0xA18,MVB_FCode2,512);
            crrcRicoMvb->addSinkPort(0xA28,MVB_FCode2,512);
            crrcRicoMvb->addSinkPort(0xA38,MVB_FCode2,512);
            crrcRicoMvb->addSinkPort(0xA48,MVB_FCode2,512);

            //CCU-ATC
            crrcRicoMvb->addSinkPort(0xB18,MVB_FCode3,512);

            //CCU-PIS
            crrcRicoMvb->addSinkPort(0x918,MVB_FCode4,256);

            //CCU-TDS
            crrcRicoMvb->addSinkPort(0xC08,MVB_FCode4,1024);
            crrcRicoMvb->addSinkPort(0xC09,MVB_FCode4,1024);

            //CCU-FAS
            crrcRicoMvb->addSinkPort(0x818,MVB_FCode1,512);
            //CCU-PCU
            crrcRicoMvb->addSinkPort(0xC18,MVB_FCode4,64);

            //CCU-PIS
            crrcRicoMvb->addSinkPort(0xC28,MVB_FCode4,64);
            //CCU-BMS
            crrcRicoMvb->addSinkPort(0xD18,MVB_FCode4,64);

            //BMS-CCU
            crrcRicoMvb->addSinkPort(0xD10,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0xD20,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0xD30,MVB_FCode4,64);
            crrcRicoMvb->addSinkPort(0xD40,MVB_FCode4,64);


        }
#endif

        if(crrcRicoMvb->InitReadPortData())
        {
            logger()->error("MVB板卡设置操作模式失败");
        }
        qDebug("step1");

        timer->start(333);
    }else
    {
        logger()->error("configure.ini文件错误");
        _LOG << "fail to read configure file.";
    }

}


void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        this->close();
    }
    else if (event->key() == Qt::Key_S)
    {
        QDesktopWidget *desktop = QApplication::desktop();

        // show a window uesd to manipulate the mvb ports and change page
        simulation->raise();
        simulation->move((desktop->width() - simulation->width()) / 2, (desktop->height() - simulation->height()) / 2);
        simulation->show();

    }
}

void Widget::VCUtime2HMI10s()
{
    static int count10stimer = 0;
    QDateTime dateTimeSystem;
    QDateTime dateTimeCcu;
    QDate date( this->database->CTALL_SysTimeYear_U8+2000, this->database->CTALL_SysTimeMonth_U8, this->database->CTALL_SysTimeDay_U8 );
    QTime time( this->database->CTALL_SysTimeHour_U8, this->database->CTALL_SysTimeMinute_U8, this->database->CTALL_SysTimeSecond_U8);
    dateTimeCcu.setDate(date);
    dateTimeCcu.setTime(time);
//    qDebug()<< "CCU TIME: " <<dateTimeCcu.date().year()<<dateTimeCcu.date().month()<<dateTimeCcu.date().day() << dateTimeCcu.toTime_t()
//            << "IDU TIME: " << dateTimeSystem.currentDateTime().date().year()<<dateTimeSystem.currentDateTime().date().month()<<dateTimeSystem.currentDateTime().date().day()
//            << dateTimeSystem.currentDateTime().toTime_t();

    if((bool(dateTimeCcu.date().year() > 1999) && bool(dateTimeCcu.date().year() < 2038)))
    {
        int timeDiff = ( dateTimeCcu.toTime_t()-dateTimeSystem.currentDateTime().toTime_t());



        if(bool(bool(timeDiff<-6 )||bool(timeDiff>6))  )
        {
            if(count10stimer > 0)
            {
                if(count10stimer++ >30)
                {
                    count10stimer = 0;
                }
            }else
            {
                logger()->info("执行自动校时，与CCU时间差为: "+QString::number(timeDiff)+" s");

                count10stimer = 1;
#ifndef USER_DEBUG_MODE
                systimeset(this->database->CTALL_SysTimeYear_U8+2000,this->database->CTALL_SysTimeMonth_U8,this->database->CTALL_SysTimeDay_U8
                           ,this->database->CTALL_SysTimeHour_U8,this->database->CTALL_SysTimeMinute_U8,this->database->CTALL_SysTimeSecond_U8);
#endif
            }
        }else
        {
            count10stimer = 0;
        }

    }
}


bool Widget::systimeset(unsigned short int year,unsigned short int month,unsigned short int day,
                             unsigned short int hour,unsigned short int minute,unsigned short int second)
{
#ifndef WINDOWS_MODE

    time_t t;
    struct tm nowtime;
    nowtime.tm_sec = second; // second
    nowtime.tm_min = minute; ///*       Minutes.[0-59]
    nowtime.tm_hour = hour;  ///*       Hours.   [0-23]
    nowtime.tm_mday = day;   ///*       Day.[1-31]
    nowtime.tm_mon = month - 1; ///*       Month.   [0-11]
    nowtime.tm_year = year - 1900; ///*       Year-       1900.
    nowtime.tm_isdst = -1;    ///*       DST.[-1/0/1]
    t = mktime(&nowtime);
    stime(&t);

    QDate date( year, month, day );
    QTime time( hour, minute, second );
    QString dateStr = date.toString( "yyyy-MM-dd" );
    QString timeStr = time.toString( "hh:mm:ss" );
    QString hwclockStr = "hwclock --set --date \"";
    dateStr.replace(QRegExp("-"), "");
    timeStr.replace(QRegExp("-"), ":");
    hwclockStr = hwclockStr + dateStr + " " + timeStr + "\"";
    char *c=hwclockStr.toLatin1().data();
    system(c);
#endif
    return true;
}
