#ifndef C_MVBSOCK_H
#define C_MVBSOCK_H


    #include <string.h>             /* memset, memcpy */
    #include <time.h>               /* time      */
    #include <QList>
    #include <QObject>

    
    #include "MVBC02C/tcn_def.h"
    #include "MVBC02C/BBD_C02C.h"
    #include "MVBC02C/mue_pd_full.h"
    //============================================
    
    
    #define MUE_PD_FULL_PORT_SIZE_MAX           32
    
 
    struct M_MVBData
    {
        QList<WORD16> RevCom;
        QList<WORD16> SendCom;
        QList<QByteArray> Data;
        bool isMain;
        int No;
        bool MVBisOK;
    };    
    //============================================
    

    class c_mvbSock:public QObject
    {
        private:
            void cdelay (int seconds);
            //============================================
            //C_Thread m_Thread;                                                      //内置使用线程类

        public:
            c_mvbSock();
            
            //============================================
            WORD16      pd_get_port_address;                                        //接收端口，无实际意义                
            WORD16      pd_put_port_address;                                        //发送端口，无实际意义   
            BITSET16    sv_device_config    __attribute__((unused));
            BITSET16    pd_port_config      __attribute__((unused));
            UNSIGNED8   bus_id;
            //============================================
            BITSET8     pd_port_status;                                             //读取数据时，返回是否正常
            UNSIGNED16  pd_port_freshness;    
           
            WORD8       pd_port_data_get[MUE_PD_FULL_PORT_SIZE_MAX];                //临时接收数据缓冲区
            WORD8       pd_port_data_put[MUE_PD_FULL_PORT_SIZE_MAX];                //临时发送数据缓冲区
            //=====================
            bool        MVBisOpen;                                                  //打开状态
    
            void        *p_bus_ctrl;                                                //接口柄
            
            QObject     *Owner;                                                     //父对象，用于线程回调
            //============================================    
            MUE_RESULT  MBV_put_device_config(void *p_bus_ctrl, BITSET16 device_config);  //底层操作函数，app无需使用
            MUE_RESULT  MVB_ba_config(void *p_bus_ctrl);                                  //返回MVB状态，app无需使用            
            void        MVB_Set_Rev_Port(WORD16 data);                              //设置接收端口,函数无效
            void        MVB_Set_Put_Port(WORD16 data);                              //设置接收端口,函数无效
            
            MUE_RESULT  MVB_Put_Data(WORD16 port_address,void *p_port_data);
            MUE_RESULT  MVB_Get_Data(WORD16 port_address,BITSET8 *p_port_status,void *p_port_data,UNSIGNED16  *p_port_freshness);                  //读取数据
            MUE_RESULT  MVB_init_port(void *p_bus_ctrl, BITSET16 port_dir, BITSET16 port_addr, BITSET16 port_size);                                //MVB 端口设定
            MUE_RESULT  MVB_Close();                                                //关闭MVB
            MUE_RESULT  MVB_Stop(void *p_bus_ctrl); 
             
            MUE_RESULT  MVB_Init();                                                 //MVB初始化
            MUE_RESULT  MVB_Start(void *p_bus_ctrl,BITSET16 device_address);        //启动MVB
            
            void Run();
            void ThreadFun();
    };

#endif 

