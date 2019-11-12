#include "data_tcn.h"
#include "crrcricomvb.h"
Data_TCN::Data_TCN()
{
    m_Ports<<0<<0<<0<<0;
}
void Data_TCN::updateData()
{


    Train1_01HVACMODE = CrrcRicoMvb::getcrrcRicoMvb()->getUnsignedChar(m_Ports.at(0),0);
    Train1_02HVACMODE =	CrrcRicoMvb::getcrrcRicoMvb()->getUnsignedChar(m_Ports.at(0),1);
    Train1_03HVACMODE = CrrcRicoMvb::getcrrcRicoMvb()->getUnsignedChar(m_Ports.at(0),2);
    Train1_04HVACMODE = CrrcRicoMvb::getcrrcRicoMvb()->getUnsignedChar(m_Ports.at(0),3);

}
void Data_TCN::setTrainID(unsigned char TrainID)
{
    if(TrainID == 1)
    {
        if(CrrcRicoMvb::getcrrcRicoMvb()->getUnsignedChar(0xfa0,31) == 1)
        {
            CrrcRicoMvb::getcrrcRicoMvb()->copyPort(0xff10,0xf10);
            CrrcRicoMvb::getcrrcRicoMvb()->copyPort(0xff11,0xf11);
            CrrcRicoMvb::getcrrcRicoMvb()->copyPort(0xff12,0xf12);
            CrrcRicoMvb::getcrrcRicoMvb()->copyPort(0xff13,0xf13);
        }else if(CrrcRicoMvb::getcrrcRicoMvb()->getUnsignedChar(0xea0,31) == 1)
        {
            CrrcRicoMvb::getcrrcRicoMvb()->copyPort(0xff10,0xe10);
            CrrcRicoMvb::getcrrcRicoMvb()->copyPort(0xff11,0xe11);
            CrrcRicoMvb::getcrrcRicoMvb()->copyPort(0xff12,0xe12);
            CrrcRicoMvb::getcrrcRicoMvb()->copyPort(0xff13,0xe13);
        }else
        {
            //todo
        }
        m_Ports[0] = 0xff10;
        m_Ports[1] = 0xff11;
        m_Ports[2] = 0xff12;
        m_Ports[3] = 0xff13;
    }else if(TrainID == 2)
    {
        if(CrrcRicoMvb::getcrrcRicoMvb()->getUnsignedChar(0xfa0,31) == 1)
        {
            CrrcRicoMvb::getcrrcRicoMvb()->copyPort(0xff20,0xf20);
            CrrcRicoMvb::getcrrcRicoMvb()->copyPort(0xff21,0xf21);
            CrrcRicoMvb::getcrrcRicoMvb()->copyPort(0xff22,0xf22);
            CrrcRicoMvb::getcrrcRicoMvb()->copyPort(0xff23,0xf23);
        }else if(CrrcRicoMvb::getcrrcRicoMvb()->getUnsignedChar(0xea0,31) == 1)
        {
            CrrcRicoMvb::getcrrcRicoMvb()->copyPort(0xff20,0xe20);
            CrrcRicoMvb::getcrrcRicoMvb()->copyPort(0xff21,0xe21);
            CrrcRicoMvb::getcrrcRicoMvb()->copyPort(0xff22,0xe22);
            CrrcRicoMvb::getcrrcRicoMvb()->copyPort(0xff23,0xe23);
        }else
        {
            //todo
        }
        m_Ports[0] = 0xff20;
        m_Ports[1] = 0xff21;
        m_Ports[2] = 0xff22;
        m_Ports[3] = 0xff23;

    }else if(TrainID == 3)
    {


    }else
    {

    }

}
