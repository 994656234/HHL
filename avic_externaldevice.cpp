#include "avic_externaldevice.h"
#include "QApplication"
//#include <sys/ioctl.h>
//#include <fcntl.h>
//#include <linux/ioctl.h>


AVIC_ExternalDevice::AVIC_ExternalDevice(QObject *parent) : QObject(parent)
{

}
AVIC_ExternalDevice* AVIC_ExternalDevice::externalDevice = NULL;

AVIC_ExternalDevice* AVIC_ExternalDevice::getAVIC_ExternalDevice()
{
    if (externalDevice == NULL)
    {
        return externalDevice = new AVIC_ExternalDevice();
    }
    else
    {
        return externalDevice;
    }
}
//初始化函数
bool AVIC_ExternalDevice::Init_Key()
{

}
void AVIC_ExternalDevice::customEvent(QEvent *event)
{

}
//打开串口API
void AVIC_ExternalDevice::OpenCom(SetInfo* SetInfo,const char* pf)
{

}
//串口接受函数
void AVIC_ExternalDevice::slot_read_my_com()
{

}
unsigned char AVIC_ExternalDevice::getBrightness()
{
    /*1-7*/
    return ext_Dev.getBlacklightBrightness();
}
void AVIC_ExternalDevice::setBrightness_ManualPlus()
{
    /*1-7*/
    int CurLight = ext_Dev.getBlacklightBrightness();
    ext_Dev.setBlacklihtBrightness(CurLight + 1);

}
void AVIC_ExternalDevice::setBrightness_ManualMinus()
{
    int CurLight = ext_Dev.getBlacklightBrightness();
    ext_Dev.setBlacklihtBrightness(CurLight - 1);

}

void AVIC_ExternalDevice::setBrightness_Manual()
{
    ext_Dev.setBlacklightAuto(false);
}

void AVIC_ExternalDevice::setBrightness_Auto()
{
    ext_Dev.setBlacklightAuto(true);
}

void AVIC_ExternalDevice::setBuzzerOn()
{
    ext_Dev.setBuzzer(true);

}
void AVIC_ExternalDevice::setBuzzeroff()
{
    ext_Dev.setBuzzer(false);
}

void AVIC_ExternalDevice::SendData(QByteArray* data)
{

}
char AVIC_ExternalDevice::ModebustoChar(char High,char Low)
{

}
char AVIC_ExternalDevice::AsciitoHex(char data)
{

}
void AVIC_ExternalDevice::ChartoModebus(QByteArray* data,char p)
{

}
char AVIC_ExternalDevice::Checkdata(char *p,int lenght)
{

}
char AVIC_ExternalDevice::chartoAssicc(char data)
{

}
