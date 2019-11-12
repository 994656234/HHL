#ifndef DATA_TCN_H
#define DATA_TCN_H
#include "qlist.h"

class Data_TCN
{
public:
    Data_TCN();

    void updateData();
    void setTrainID(unsigned char TrainID);

private:
    QList<unsigned short int>   m_Ports;
    unsigned char		Train1_01HVACMODE;
    unsigned char		Train1_02HVACMODE;
    unsigned char		Train1_03HVACMODE;
    unsigned char		Train1_04HVACMODE;
};

#endif // DATA_TCN_H
