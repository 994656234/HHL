#ifndef CRRCFAULT_H
#define CRRCFAULT_H

#include <QString>

#include <QList>
#include <QMap>

#include "qdatetime.h"
#include "qtimer.h"
#include "qthread.h"
#include "qmutex.h"
#include "logger.h"
#include "MainGetDefaultPara.h"


#include "crrcfaultmapper.h"

class CrrcRicoMvb;

struct fault_type
{
    unsigned short int port;
    unsigned char byte, bit;
    bool virtualValue;
    QString code, name, device, position, description;
};

struct current_fault_type
{
    unsigned short int key;
    QString start, code, name, position, device, description;
};
//struct step_fault_type
//{
//    struct current_fault_type currentfaulttype;
//    bool status;
//};

struct history_fault_type
{
    QString start, end, code, name, position, device, description;
};

class CrrcFault : public QThread
{
    Q_OBJECT
    LOG4QT_DECLARE_QCLASS_LOGGER

private :
    CrrcFault(QString faultListPath, QString historyFilePath);
    static CrrcFault* crrcFault;
    MainGetDefaultPara *getParam;

public:
    static CrrcFault* getCrrcFault();

    static bool initCrrcFault(QString faultListPath, QString historyFilePath);

    void synchronize(CrrcRicoMvb *crrcRicoMvb);
    QString getCurrentFaultDate(unsigned short int index) ;
    QString getCurrentFaultTime(unsigned short int index) ;
    QString getCurrentFaultCode(unsigned short int index) ;
    QString getCurrentFaultName(unsigned short int index) ;
    QString getCurrentFaultDevice(unsigned short int index) ;
    QString getCurrentFaultPosition(unsigned short int index) ;
    QString getCurrentFaultDescription(unsigned short int index) ;
    unsigned short int getCurrentFaultListSize() ;
    QString getHistoryFaultStartDate(unsigned short int index) ;
    QString getHistoryFaultStartTime(unsigned short int index) ;
    QString getHistoryFaultEndDate(unsigned short int index) ;
    QString getHistoryFaultEndTime(unsigned short int index) ;
    QString getHistoryFaultCode(unsigned short int index) ;
    QString getHistoryFaultName(unsigned short int index) ;
    QString getHistoryFaultDevice(unsigned short int index) ;
    QString getHistoryFaultPosition(unsigned short int index) ;
    QString getHistoryFaultDescription(unsigned short int index) ;
    unsigned short int getHistoryFaultListSize() ;
    // add confirmfault list
    void deleteAllconfirmFault();
    void deleteConfirmFault(unsigned short int index);
    void deleteConfirmFaultByCurrentFaultList(unsigned short int index);
    QString getConfirmFaultLevel(unsigned short int index);
    QString getConfirmFaultDate(unsigned short int index) ;
    QString getConfirmFaultTime(unsigned short int index) ;
    QString getConfirmFaultCode(unsigned short int index) ;
    QString getConfirmFaultName(unsigned short int index) ;
    QString getConfirmFaultDevice(unsigned short int index) ;
    QString getConfirmFaultPosition(unsigned short int index) ;
    QString getConfirmFaultDescription(unsigned short int index) ;
    unsigned short int getConfirmFaultListSize() ;

    // add new fault occur func
    bool NewFaultOccur;
    bool NewFaultDetect;
    QString getCurrentFaultLevel(unsigned short int index) ;
    QString getHistoryFaultLevel(unsigned short int index) ;

    // add get fault confirm func
    bool getCurrentFaultConfirm(unsigned short int index) ;
    bool getHistoryFaultConfirm(unsigned short int index) ;



    // add fault query cnt
    unsigned int getFaultCntOfEachSystem(QString str);
    unsigned int getFaultCntOfEachVehicle(QString str);
    void getQueryFaultOfEachSystem(QString str);
    void getQueryFaultOfEachVehicle(QString str);
    bool getQueryFaultOfEachCode(QString str);
    QList<unsigned int> QueryList;
    QList<unsigned int> getQueryFault();

    //add current fault query cnt
    bool queryCurrentFaultCnt(QString system,int level,QString pos);


    QString getFaultListFileVersion();
    QString getCrrcFaultVersion();
    void getLocalDateTime(QDateTime datetime);
    QString getFaultTypeVersion();



    //add close DB
    void closeDB();
private:

    const QString databaseFaultTypeName, databaseHistoryFaultName;
    QString faultListFileVersion;
    void readFaultTypeListFile();
    void readHistoryFaultFile();

    QDateTime m_Localdatetime;
    QList<FaultBean> historyFaultList;
    QList<FaultBean> currentFaultList;
    QList<FaultBean> unconfirmFaultList;

    //void removeConfirmItem(unsigned short int key);

    QTimer *timer;
    QTimer *HVACtimer;

    CrrcFaultMapper* crrcFaultMapper;
    QHash<quint32,FaultTypeBean> FaultTypeHash;
    QHash<quint32,FaultBean> InsertHistoryFaultHash,UpdateHistoryFaultHash;
    QHash<quint32,quint32> IDHash;//<Fault_ID -> History_ID>

    QHash<quint32,quint32> CurrentFaultIDHash; //< current_ID -> fault_ID >
    QHash<quint32,FaultBean> CurrentFaultHash; //< fault_ID -> faultBean >

    // change fault to faultthread
private:

    QMutex m_lock;
    void run();

private slots:


};

#endif // CRRCFAULT_H
