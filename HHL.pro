#-------------------------------------------------
#
# Project created by QtCreator 2017-07-25T15:35:43
#
#-------------------------------------------------
TRANSLATIONS += lang_Portuguese.ts

#DEFINES += USER_DEBUG_MODE
DEFINES += MVB_CX

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT       += core gui
QT += sql
QT += network
TARGET = HHL

TEMPLATE = app


DEPENDPATH += . log4qt log4qt/helpers log4qt/spi log4qt/varia
INCLUDEPATH += . log4qt log4qt/helpers log4qt/spi log4qt/varia

SOURCES += main.cpp\
        widget.cpp \
    mybase.cpp \
    database.cpp \
    header.cpp \
    MainGetDefaultPara.cpp \
    navigator.cpp \
    vehiclerunstatepage.cpp \
    log4qt/writerappender.cpp \
    log4qt/ttcclayout.cpp \
    log4qt/simplelayout.cpp \
    log4qt/rollingfileappender.cpp \
    log4qt/propertyconfigurator.cpp \
    log4qt/patternlayout.cpp \
    log4qt/ndc.cpp \
    log4qt/mdc.cpp \
    log4qt/logmanager.cpp \
    log4qt/loggingevent.cpp \
    log4qt/loggerrepository.cpp \
    log4qt/logger.cpp \
    log4qt/log4qt.cpp \
    log4qt/level.cpp \
    log4qt/layout.cpp \
    log4qt/hierarchy.cpp \
    log4qt/fileappender.cpp \
    log4qt/dailyrollingfileappender.cpp \
    log4qt/consoleappender.cpp \
    log4qt/basicconfigurator.cpp \
    log4qt/appenderskeleton.cpp \
    log4qt/helpers/properties.cpp \
    log4qt/helpers/patternformatter.cpp \
    log4qt/helpers/optionconverter.cpp \
    log4qt/helpers/logobjectptr.cpp \
    log4qt/helpers/logobject.cpp \
    log4qt/helpers/logerror.cpp \
    log4qt/helpers/initialisationhelper.cpp \
    log4qt/helpers/factory.cpp \
    log4qt/helpers/datetime.cpp \
    log4qt/helpers/configuratorhelper.cpp \
    log4qt/helpers/classlogger.cpp \
    log4qt/spi/filter.cpp \
    log4qt/varia/stringmatchfilter.cpp \
    log4qt/varia/nullappender.cpp \
    log4qt/varia/listappender.cpp \
    log4qt/varia/levelrangefilter.cpp \
    log4qt/varia/levelmatchfilter.cpp \
    log4qt/varia/denyallfilter.cpp \
    log4qt/varia/debugappender.cpp \
    crrcfaultmapper.cpp \
    crrcfault.cpp \
    faulttypebean.cpp \
    faultbean.cpp \
    vehiclepasswordpage.cpp \
    vehiclestationbar.cpp \
    vehicletrainarea.cpp \
    vehiclestatusarea.cpp \
    vehicleinformationarea.cpp \
    vehicleairconditionerpage.cpp \
    vehicleauxiliarypage.cpp \
    vehiclelinecircuitbreakerpage.cpp \
    vehicledoorpage.cpp \
    vehiclepispage.cpp \
    vehiclebrakepage.cpp \
    vehicletractpage.cpp \
    vehiclefirewarningpage.cpp \
    vehicleaircompressorpage.cpp \
    vehicletopologypage.cpp \
    vehiclesetpage.cpp \
    vehiclesetstationpage.cpp \
    vehiclesetairconditionpage.cpp \
    vehiclemaintainpage.cpp \
    vehiclemthistoryfaultpage.cpp \
    vehiclemttimesetpage.cpp \
    maintainceallportspage.cpp \
    maintainceinitsetpage.cpp \
    dicontrol.cpp \
    docontrol.cpp \
    maintainceriompage.cpp \
    maintaincewheeldiametersetpage.cpp \
    maintaincesoftwareversionpage.cpp \
    maintaincedatamanagepage.cpp \
    maintainceresetexcisionpage.cpp \
    maintaincecommunicationstatepage.cpp \
    simulation.cpp \
    vehiclesetbrakeparampage.cpp \
    vehiclesetintensitycontrolpage.cpp \
    vehiclesetbraketestpage.cpp \
    vehiclemaintaincetractsubsystempage.cpp \
    maintaincebrakesubsystempage.cpp \
    maintainceauxiliarysubsystempage.cpp \
    maintaincerunninggearsubsystempage.cpp \
    faulteventpage.cpp \
    bypasspage.cpp \
    maintaincecurrentfaultpage.cpp \
    maintaincehistoryfaultpage.cpp \
    maintaincequeryfaultpage.cpp \
    maintainceshowqueryfaultpage.cpp \
    h8.cpp \
    command.c \
    serial.c \
    axcontrol.cpp \
    tcdicontrol.cpp \
    tcdocontrol.cpp \
    doorversioncontrol.cpp \
    riomlcuversioncontrol.cpp \
    warnningdialog.cpp \
    helppage.cpp \
    helppage2.cpp \
    helppage3.cpp \
    helppage4.cpp \
    helppage5.cpp \
    maintaincepisautotest.cpp \
    maintainceaccumulatedatapage.cpp \
    addsubtracttestpage.cpp \
    emdialogpage.cpp \
    passwordpage.cpp \
    drivers/c_io.cpp \
    signal/ccustomevent.cpp \
    crrcricomvb.cpp \
    log4qt/log4qt_init.cpp \
    qextserial/qextserialport.cpp \
    qextserial/qextserialport_unix.cpp \
    cxExtDev/blacklightthread.cpp \
    cxExtDev/externaldevicelib.cpp \
    avic_externaldevice.cpp \
    maintainceaccumulatorsubsystempage.cpp \
    bypasspage2.cpp \
    emdooropen.cpp \
    vehiclesetsimlatestation.cpp \
    stationchoicebox.cpp \
    maintaincebatterysubsystempage.cpp



if(contains(DEFINES,MVB_CX)){
LIBS += -lsqlite3
SOURCES += mvbcx/c_mvbsock.cpp \
    mvbcx/MVBC02C/BBD_C02C.c \
    mvbcx/MVBC02C/bus_opt.c \
    mvbcx/MVBC02C/os_hal.c

HEADERS += mvbcx/c_mvbsock.h \
    mvbcx/MVBC02C/BBD_C02C.h \
    mvbcx/MVBC02C/bus_opt.h \
    mvbcx/MVBC02C/C02C_Def.h \
    mvbcx/MVBC02C/mue_pd_full.h \
    mvbcx/MVBC02C/os_hal.h \
    mvbcx/MVBC02C/tcn_def.h
}else{

LIBS += -L$$PWD/lib/ -lmodbus
#LIBS += -L$$PWD/../../../lib/ -lsqlite3
LIBS += -lsqlite3

#LIBS += -lavic_imx

SOURCES +=  mvb/MVB/ax99100_lb.c \
    mvb/MVB/mue_acc.c \
    mvb/MVB/mue_app.c \
    mvb/MVB/mue_ba_config.c \
    mvb/MVB/mue_cch.c \
    mvb/MVB/mue_pd_full.c \
    mvb/MVB/mue_sv.c\
    mvb/c_mvbsock.cpp

HEADERS +=  mvb/c_mvbsock.h \
    mvb/MVB/ax99100_lb.h \
    mvb/MVB/ioctl.h \
    mvb/MVB/mue_acc.h \
    mvb/MVB/mue_ba_config.h \
    mvb/MVB/mue_cch.h \
    mvb/MVB/mue_def.h \
    mvb/MVB/mue_osl.h \
    mvb/MVB/mue_pd_full.h \
    mvb/MVB/mue_sv.h \
    mvb/MVB/tcn_def.h
}



HEADERS  += widget.h \
    mybase.h \
    database.h \
    global.h \
    header.h \
    MainGetDefaultPara.h \
    navigator.h \
    vehiclerunstatepage.h \
    log4qt/writerappender.h \
    log4qt/ttcclayout.h \
    log4qt/simplelayout.h \
    log4qt/rollingfileappender.h \
    log4qt/propertyconfigurator.h \
    log4qt/patternlayout.h \
    log4qt/ndc.h \
    log4qt/mdc.h \
    log4qt/logmanager.h \
    log4qt/loggingevent.h \
    log4qt/loggerrepository.h \
    log4qt/logger.h \
    log4qt/log4qt.h \
    log4qt/level.h \
    log4qt/layout.h \
    log4qt/hierarchy.h \
    log4qt/fileappender.h \
    log4qt/dailyrollingfileappender.h \
    log4qt/consoleappender.h \
    log4qt/basicconfigurator.h \
    log4qt/appenderskeleton.h \
    log4qt/appender.h \
    log4qt/helpers/properties.h \
    log4qt/helpers/patternformatter.h \
    log4qt/helpers/optionconverter.h \
    log4qt/helpers/logobjectptr.h \
    log4qt/helpers/logobject.h \
    log4qt/helpers/logerror.h \
    log4qt/helpers/initialisationhelper.h \
    log4qt/helpers/factory.h \
    log4qt/helpers/datetime.h \
    log4qt/helpers/configuratorhelper.h \
    log4qt/helpers/classlogger.h \
    log4qt/spi/filter.h \
    log4qt/varia/stringmatchfilter.h \
    log4qt/varia/nullappender.h \
    log4qt/varia/listappender.h \
    log4qt/varia/levelrangefilter.h \
    log4qt/varia/levelmatchfilter.h \
    log4qt/varia/denyallfilter.h \
    log4qt/varia/debugappender.h \
    crrcfaultmapper.h \
    crrcfault.h \
    faulttypebean.h \
    faultbean.h \
    vehiclepasswordpage.h \
    vehiclestationbar.h \
    vehicletrainarea.h \
    vehiclestatusarea.h \
    vehicleinformationarea.h \
    vehicleairconditionerpage.h \
    vehicleauxiliarypage.h \
    vehiclelinecircuitbreakerpage.h \
    vehicledoorpage.h \
    vehiclepispage.h \
    vehiclebrakepage.h \
    vehicletractpage.h \
    vehiclefirewarningpage.h \
    vehicleaircompressorpage.h \
    vehicletopologypage.h \
    vehiclesetpage.h \
    vehiclesetstationpage.h \
    vehiclesetairconditionpage.h \
    vehiclemaintainpage.h \
    vehiclemthistoryfaultpage.h \
    vehiclemttimesetpage.h \
    maintainceallportspage.h \
    maintainceinitsetpage.h \
    dicontrol.h \
    docontrol.h \
    maintainceriompage.h \
    maintaincewheeldiametersetpage.h \
    maintaincesoftwareversionpage.h \
    maintaincedatamanagepage.h \
    maintainceresetexcisionpage.h \
    maintaincecommunicationstatepage.h \
    simulation.h \
    vehiclesetbrakeparampage.h \
    vehiclesetintensitycontrolpage.h \
    vehiclesetbraketestpage.h \
    vehiclemaintaincetractsubsystempage.h \
    maintaincebrakesubsystempage.h \
    maintainceauxiliarysubsystempage.h \
    maintaincerunninggearsubsystempage.h \
    faulteventpage.h \
    bypasspage.h \
    maintaincecurrentfaultpage.h \
    maintaincehistoryfaultpage.h \
    maintaincequeryfaultpage.h \
    maintainceshowqueryfaultpage.h \
    h8.h \
    command.h \
    serial.h \
    axcontrol.h \
    tcdicontrol.h \
    tcdocontrol.h \
    doorversioncontrol.h \
    riomlcuversioncontrol.h \
    warnningdialog.h \
    helppage.h \
    helppage2.h \
    helppage3.h \
    helppage4.h \
    helppage5.h \
    maintaincepisautotest.h \
    maintainceaccumulatedatapage.h \
    addsubtracttestpage.h \
    emdialogpage.h \
    passwordpage.h \
    drivers/c_io.h \
    log4qt/custom.h \
    qextserial/qextserialport.h \
    qextserial/qextserialport_global.h \
    qextserial/qextserialport_p.h \
    signal/ccustomevent.h \
    sqlite3.h \
    crrcricomvb.h \
    cxExtDev/blacklightthread.h \
    cxExtDev/externaldevicelib.h \
    avic_externaldevice.h \
    maintainceaccumulatorsubsystempage.h \
    bypasspage2.h \
    avic_imx.h \
    emdooropen.h \
    vehiclesetsimlatestation.h \
    stationchoicebox.h \
    maintaincebatterysubsystempage.h

FORMS    += widget.ui \
    header.ui \
    navigator.ui \
    vehiclerunstatepage.ui \
    vehiclepasswordpage.ui \
    vehiclestationbar.ui \
    vehicletrainarea.ui \
    vehiclestatusarea.ui \
    vehicleinformationarea.ui \
    vehicleairconditionerpage.ui \
    vehicleauxiliarypage.ui \
    vehiclelinecircuitbreakerpage.ui \
    vehicledoorpage.ui \
    vehiclepispage.ui \
    vehiclebrakepage.ui \
    vehicletractpage.ui \
    vehiclefirewarningpage.ui \
    vehicleaircompressorpage.ui \
    vehicletopologypage.ui \
    vehiclesetpage.ui \
    vehiclesetstationpage.ui \
    vehiclesetairconditionpage.ui \
    vehiclemaintainpage.ui \
    vehiclemthistoryfaultpage.ui \
    vehiclemttimesetpage.ui \
    maintainceallportspage.ui \
    maintainceinitsetpage.ui \
    dicontrol.ui \
    docontrol.ui \
    maintainceriompage.ui \
    maintaincewheeldiametersetpage.ui \
    maintaincesoftwareversionpage.ui \
    maintaincedatamanagepage.ui \
    maintainceresetexcisionpage.ui \
    maintaincecommunicationstatepage.ui \
    simulation.ui \
    vehiclesetbrakeparampage.ui \
    vehiclesetintensitycontrolpage.ui \
    vehiclesetbraketestpage.ui \
    vehiclemaintaincetractsubsystempage.ui \
    maintaincebrakesubsystempage.ui \
    maintainceauxiliarysubsystempage.ui \
    maintaincerunninggearsubsystempage.ui \
    faulteventpage.ui \
    bypasspage.ui \
    maintaincecurrentfaultpage.ui \
    maintaincehistoryfaultpage.ui \
    maintaincequeryfaultpage.ui \
    maintainceshowqueryfaultpage.ui \
    axcontrol.ui \
    tcdicontrol.ui \
    tcdocontrol.ui \
    doorversioncontrol.ui \
    riomlcuversioncontrol.ui \
    warnningdialog.ui \
    helppage.ui \
    helppage2.ui \
    helppage3.ui \
    helppage4.ui \
    helppage5.ui \
    maintaincepisautotest.ui \
    maintainceaccumulatedatapage.ui \
    addsubtracttestpage.ui \
    emdialogpage.ui \
    passwordpage.ui \
    maintainceaccumulatorsubsystempage.ui \
    bypasspage2.ui \
    emdooropen.ui \
    vehiclesetsimlatestation.ui \
    stationchoicebox.ui \
    maintaincebatterysubsystempage.ui

RESOURCES += \
    Resource.qrc

OTHER_FILES +=

DISTFILES += \
    mvb/MVB/licence.txt \
    mvb/MVB/Makefile \
    mvb/MVB/licence.txt \
    mvb/MVB/Makefile \
    libavic_imx.so


QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
#unix:!macx: LIBS += -L$$PWD/./ -lavic_imx

#INCLUDEPATH += $$PWD/.
#DEPENDPATH += $$PWD/.
