#ifndef C_MVBSOCK_H
#define C_MVBSOCK_H
#include "qdebug.h"

#include "MVB/tcn_def.h"
#include "MVB/mue_def.h"
#include "MVB/mue_osl.h"
#include "MVB/mue_acc.h"
#include "MVB/mue_sv.h"
#include "MVB/mue_pd_full.h"
#include "MVB/mue_ba_config.h"
#include <string.h> /* memset, memcpy */
#include <time.h>   /* time      */
struct M_MVBData
{
    QList<WORD16> RevCom;
    QList<WORD16> SendCom;
    QList<QByteArray> Data;
    bool isMain;
    int No;
    bool MVBisOK;
};
class c_mvbSock:public QObject
{
public:
    c_mvbSock();
private:
    void cdelay (int seconds);
    TCN_DECL_LOCAL MUE_RESULT mue_app_init_device(void *p_bus_ctrl);
    MUE_RESULT mue_app_init_port(void *p_bus_ctrl, BITSET16 pd_port_config);
    MUE_RESULT mue_init_port(void *p_bus_ctrl, BITSET16 port_dir, BITSET16 port_addr, BITSET16 port_size);
    MUE_RESULT mue_start_mvb_communication(void *p_bus_ctrl, BITSET16 device_address);
    MUE_RESULT mue_stop_mvb_communication(void *p_bus_ctrl);
    //
public:
    BITSET16    sv_device_config __attribute__((unused));
    BITSET16    pd_port_config __attribute__((unused));
    BITSET8     pd_port_status;
    UNSIGNED16  pd_port_freshness;
    WORD8       pd_port_data_get[MUE_PD_FULL_PORT_SIZE_MAX];
    WORD8       pd_port_data_put[MUE_PD_FULL_PORT_SIZE_MAX];
    //
    bool        MVBisOpen;//打开状态
    void        *p_bus_ctrl;//接口柄
    UNSIGNED8   bus_id;
    WORD16      pd_get_port_address;//接收端口
    WORD16      pd_put_port_address;//发送端口
    QObject *Owner;     //父对象
    //
    MUE_RESULT MVB_init_port(void *p_bus_ctrl, BITSET16 port_dir, BITSET16 port_addr, BITSET16 port_size);//MVB 端口设定
    MUE_RESULT MVB_Init();//MVB初始化
    MUE_RESULT MVB_Close();
    MUE_RESULT MVB_Start(void *p_bus_ctrl, BITSET16 device_address);
    MUE_RESULT MBV_put_device_config(void *p_bus_ctrl, BITSET16 device_config);
    MUE_RESULT MVB_ba_config(void *p_bus_ctrl);
    MUE_RESULT MVB_Get_Data(WORD16 port_address,BITSET8 *p_port_status,void *p_port_data,UNSIGNED16  *p_port_freshness);
    MUE_RESULT MVB_Stop(void *p_bus_ctrl);
    MUE_RESULT MVB_Put_Data(WORD16 port_address,void *p_port_data);
    void MVB_Set_Rev_Port(WORD16 data);
    void MVB_Set_Put_Port(WORD16 data);
    void Run();
    void ThreadFun();
//    MUE_RESULT mue_app_main();
};

#endif // C_MVBSOCK_H
