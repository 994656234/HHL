#ifndef CRRCRICOMVB_H
#define CRRCRICOMVB_H
#ifdef MVB_CX
#include "mvbcx/c_mvbsock.h"
#else
#include "mvb/c_mvbsock.h"
#endif

#define _CRRC_MVB_VERSION 1
#define _CRRC_MVB_SUPERVISION_TIME 1
#include "QMap"
#include "qdebug.h"
typedef uint16_t RICO_DATA[16];

enum PortType
{
    MVB_Sink,//接收
    MVB_Source,//发送
    MVB_Virtual
};
enum FCode
{
    MVB_FCode0,//2byte
    MVB_FCode1,//4byte
    MVB_FCode2,//8byte
    MVB_FCode3,//16byte
    MVB_FCode4//32byte
};

//******************MVB 数据type结构体
//data: 数据
//cycle: 端口大小
//crrc_port_type: 端口类型
//cycle:特征周期
//**********************
struct crrc_port
{
    unsigned short int port;
    int size;
    enum PortType type;
    unsigned short int cycle;

    crrc_port(unsigned short int port, int size, enum PortType type, unsigned short int cycle)
    {
        this->port = port;
        this->size = size;
        this->type = type;
        this->cycle = cycle;
    }
};
//******************MVB 数据结构体
//data: 数据
//cycle: 端口实际刷新周期
//**********************
struct crrc_port_data
{
    //RICO_DATA data;
    WORD8 data[32];
    UNSIGNED8 status;
    UNSIGNED16 cycle;

    crrc_port_data(unsigned short int cycle)
    {
        this->cycle = cycle;
        this->status = 0;
        memset(data, 0, sizeof data);
    }
};
class CrrcRicoMvb
{
public:

    //**********************单例模式
    static CrrcRicoMvb *getcrrcRicoMvb();

    //**********************初始化MVB配置initializeMvb
    bool initializeMvb();

    //**********************暂停MVB通信setMvbStop
    bool setMvbStop();

    //**********************配置MVB端口addPort
    //port: 端口号
    //size: 端口大小
    //type：端口类型(源 宿）
    //cycle：特征周期
    //**********************
    bool addPort(unsigned short int port, enum FCode size, enum PortType type, unsigned short int cycle);

    //**********************直接调用addport（），只配置一次
    bool addSourcePort(unsigned short int port, enum FCode size, unsigned short int cycle);
    bool addSinkPort(unsigned short int port, enum FCode size, unsigned short int cycle);
    bool addVirtualPort(unsigned short int port, enum FCode size);
    //**********************

    //**********************MVB通信同步，在主程序循环中调用，完成数据接受、发送功能。
    ////目前做法，接受到的、要发送的数据均放入portData数据结构中
    void synchronizeMvbData();

    //**********************获取MVB接受数据，被外部调用
    bool getBool(unsigned short int port, unsigned short int byteOffset, unsigned short int bitOffset);
    unsigned char getUnsignedChar(unsigned short int port, unsigned short int byteOffset);
    signed char getSignedChar(unsigned short int port, unsigned short int byteOffset);
    unsigned short int getUnsignedInt(unsigned short int port, unsigned short int byteOffset);
    signed short int getSignedInt(unsigned short int port, unsigned short int byteOffset);
    qint32 getSignedInt32(unsigned short int port, unsigned short int byteOffset);
    quint32 getUnsignedInt32(unsigned short int port, unsigned short int byteOffset);
    void setBool(unsigned short int port, unsigned short int byteOffset, unsigned short int bitOffset, bool signal);
    //**********************

    //**********************设置MVB发送数据，被外部调用
    void setUnsignedChar(unsigned short int port, unsigned short int byteOffset, unsigned char signal);
    void setSignedChar(unsigned short int port, unsigned short int byteOffset, signed char signal);
    void setUnsignedInt(unsigned short int port, unsigned short int byteOffset, unsigned short int signal);
    void setSignedInt(unsigned short int port, unsigned short int byteOffset, signed short int signal);
    void setUnsignedInt32(unsigned short int port, unsigned short int byteOffset, quint32 signal);
    void setSignedInt32(unsigned short int port, unsigned short int byteOffset, qint32 signal);
    //**********************

    //**********************获取总端口数
    unsigned short int getPortSum();

    //**********************获取指定端口实际刷新周期
    unsigned short int getPortCycle(unsigned short int port);

    //*********************判断指定端口是否超时
    bool isPortTimeout(unsigned short int port);
    QString getVersion();

    //*********************判断指定端口是否存在
    bool getportexist(unsigned short int port);

    //*********************获取所有已经配置的端口
    QList<unsigned short int> getAllPorts();
    //add b20180521 initmvb
    //*********************初始化读写区，在配置完端口后调用，只调用一次（源屏幕特殊定制）
    bool InitReadPortData();


    //*********************复制sink端口数据道source端口
    void copyPort(unsigned short int sink, unsigned short int source);



private:
    CrrcRicoMvb();
    static CrrcRicoMvb *crrcRicoMvb;

    QList<struct crrc_port *> portConfigure;
    QMap<int, struct crrc_port_data *> portData;

    c_mvbSock M_MVB;
    MUE_RESULT  result;
    M_MVBData Msg;

//    uint16_t Regtabreg[16];
//    uint16_t SRegtabreg[16];
};

#endif // CRRCRICOMVB_H
