#ifndef FAULTBEAN_H
#define FAULTBEAN_H

#include "QString"

class FaultBean
{
public:
    FaultBean();
public:
    int ID;
    QString StartTime;
    QString EndTime;
    int HistoryID;
    bool IsConfirm;

};

#endif // FAULTBEAN_H
