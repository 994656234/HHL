#ifndef AVIC_EXTERNALDEVICE_H
#define AVIC_EXTERNALDEVICE_H

#include <QObject>
#include "qtimer.h"

#include "cxExtDev/externaldevicelib.h"

#define G1712A   0
#define G1708   1

#define bit0 0x01
#define bit1 0x02
#define bit2 0x04
#define bit3 0x08
#define bit4 0x10
#define bit5 0x20
#define bit6 0x40
#define bit7 0x80

struct SetInfo
{
    QString Com_Name;
    QString Baudrate;            //波特率 9600
    QString Parity;              //数据位 7 8 9
    QString Wordlen;             //校验 0无  1奇 2偶
    QString Stopbit;             //停止位 1=1 2=2 3=0.5 4=1.5
    bool m_ComisOpen;
    //QextSerialPort *gp_my_com; // 串口的选择和串口的初始化
    QByteArray ReadMessage;
    QByteArray WriteMessage;
};
struct ConSet
{
    char BlackLightCon;
    char BeepCon;
    char LEDCon;
    char KeyType[4];
    char Temp[2];
    unsigned char Light;
    char OldKeyType[4];
};
class AVIC_ExternalDevice : public QObject
{
    Q_OBJECT
public:
    static AVIC_ExternalDevice* getAVIC_ExternalDevice();
    static AVIC_ExternalDevice* externalDevice;

    unsigned char getBrightness();
    void setBrightness_ManualPlus();
    void setBrightness_ManualMinus();
    void setBrightness_Auto();
    void setBrightness_Manual();
    void setBuzzerOn();
    void setBuzzeroff();
private:

    explicit AVIC_ExternalDevice(QObject *parent = 0);

    SetInfo M_SetInfoKey;//结构体 按键
    ConSet M_ConSet;//数据对象
    bool OncustomEvent;
    char ComData[6];//发送数据对象
    char KeyData;//亮度控制字节
    //C_io m_ioadc;
    ExternalDeviceLib ext_Dev;

   // keyboardIndex m_keyboardIndex;

    QTimer testtimer;

    void customEvent(QEvent *event);
    void SendData(QByteArray* data);
    char chartoAssicc(char data);
    char Checkdata(char *p, int lenght);
    void ChartoModebus(QByteArray *data, char p);
    char ModebustoChar(char High, char Low);
    char AsciitoHex(char data);
    void OpenCom(SetInfo *SetInfo, const char *pf);
    bool Init_Key();


signals:
    //keyboard pressed signal
    //void pressKeyBoardIndex(keyboardIndex);

public slots:
    void slot_read_my_com();

};

#endif // AVIC_EXTERNALDEVICE_H
