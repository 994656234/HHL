#ifndef GLOBAL_H
#define GLOBAL_H


//#define WINDOWS_MODE

#include <stdlib.h>

#ifndef WINDOWS_MODE

#endif

//#define USE_DEBUG_MODE

#define DI_LENGTH (24 )
#define DO_LENGTH (16 )
#define AX_LENGTH (8 )


#define NButtonUP    "font: 20px, \"微软雅黑\";color: black;background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 rgba(170,170,170,255),stop:1 rgba(150,150,150,255));"
#define NButtonDOWN  "font: 20px, \"微软雅黑\";color: black;background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 rgba(150,150,150,255),stop:1 rgba(100,100,100,255));"

#define PButtonUP    "font: 20px, \"微软雅黑\";color: white;background-color:rgb(0,0,50);"
#define PButtonDOWN  "font: 20px, \"微软雅黑\";color: white;background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 rgba(150,150,200,255),stop:1 rgba(0,0,50,255));"
#define TMPToken   "border-image: url(:/images/image/tmptoken.png);background-color:transparent;"

enum pagePosition
{
    uTop = 0,           //header h:62
    uStation,           //station bar h:90
    uTrain,             //train bar  h:141
    uStatus,            // status area  h:300
    uInformation,       // Information area  h:130
    uBottom,            // h:85
    uMiddle,
    uHuge,
    uTolopogy,          //for TolopogyPage h:??
    uMainRunstatus,
};
enum pageIndex
{
    uVehicleRunStatePage = 0,
    uVehicleStationBar,
    uVehicleStatusArea,
    uVehicleInformationArea,
    uVehicleTrainArea,
    uVehiclePasswordPage,

    uVehicleAirConditionerPage,
    uVehicleAuxiliaryPage,
    uVehicleLineCircuitBreakerPage,
    uVehicleDoorPage,
    uVehiclePISPage,
    uVehicleBrakePage,
    uVehicleTractPage,
    uVehicleFireWarningPage,
    uVehicleAirCompressorPage,
    uVehicleResetPage,
    uVehicleTopologyPage,
    uVehicleSetPage,
    uVehicleSetStationPage,
    uVehicleSetAirConditionPage,
    uVehicleMaintainPage,
    uVehicleMTHistoryFaultPage,
    uVehicleMTTimeSetPage,
    uVehicleMaintainceAllPortsPage,
    uVehicleMaintainceInitSetPage,
    uVehicleMaintainceRIOMPage,
    uVehicleMaintainceWheelDiameterSetPage,
    uVehicleMaintainceSoftwareVersionPage,
    uVehicleMaintainceDataManagePage,
    uVehicleMaintainceResetExcisionPage,
    uVehicleMaintainceCommunicationStatePage,
    uVehicleSetBrakeParamPage,
    uVehicleSetIntensityControlPage,
    uVehicleSetBrakeTestPage,
    uVehicleMaintainceTractSubsystemPage,
    uVehicleMaintainceBrakeSubsystemPage,
    uVehicleMaintainceAuxiliarySubsystemPage,
    uVehicleMaintainceRunningGearSubsystemPage,
    uVehicleFaultEventPage,
    uVehicleByPassPage,
    uVehicleByPassPage2,
    uMaintainceCurrentFaultPage,
    uMaintainceHistoryFaultPage,
    uMaintainceQueryFaultPage,
    uMaintainceShowQueryFaultPage,
    uVehicleHelpPage,
    uVehicleHelpPage2,
    uVehicleHelpPage3,
    uVehicleHelpPage4,
    uVehicleHelpPage5,
    uMaintaincePISAutoTest,
    uMaintainceAccumulateDataPage,
    uMaintainceAddSubtractTestPage,
    uMaintaincePasswordPage,
    uMaintainceAccumulatorSubsystemPage,
    uVehicleSetSimlateStation,
};

#define _LOG qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << __FILE__ << __LINE__

#endif // GLOBAL_H
