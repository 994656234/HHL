#ifndef FAULTTYPEBEAN_H
#define FAULTTYPEBEAN_H
#include "QString"

class FaultTypeBean
{
public:
    FaultTypeBean();

    int ID;
    QString FaultName;
    QString FaultPosition;
    QString FaultDevice;
    QString FaultDescription;
    QString FaultTips;
    QString FaultCode;
    unsigned short int PortAddress;
    unsigned short int ByteoffAddress;
    unsigned short int BitoffAddress;
    bool FaultValid;
    unsigned short  FaultLevel;

};

#endif // FAULTTYPEBEAN_H
