#include "c_mvbsock.h"
//#include "mainwindow.h"

/******************************************
 *MVB_Set_Rev_Port 设置接收端口，无实际意义
 *******************************************/
void c_mvbSock::MVB_Set_Rev_Port(WORD16 data)
{
    pd_get_port_address = (WORD16)data;
}

/******************************************
 *MVB_Set_Put_Port 设置发送端口，无实际意义
 *******************************************/
void c_mvbSock::MVB_Set_Put_Port(WORD16 data)
{
    pd_put_port_address = (WORD16)data;
}

TCN_DECL_PUBLIC MUE_RESULT c_mvbSock::MVB_ba_config(void *p_bus_ctrl)
{
    unsigned char *ptr = (unsigned char *) p_bus_ctrl;
    if((MVBisOpen == false)||(*ptr == 0))
        return MUE_RESULT_ERROR;
    else
        return MUE_RESULT_OK;
}

TCN_DECL_PUBLIC MUE_RESULT c_mvbSock::MBV_put_device_config(void *p_bus_ctrl, BITSET16 device_config)
{
    unsigned char *ptr = (unsigned char *) p_bus_ctrl;
    if((MVBisOpen == false)||(*ptr == 0))
        return MUE_RESULT_ERROR;
    else
        return MUE_RESULT_OK;
}
void c_mvbSock::cdelay (int seconds)
{
   UNSIGNED32 cch_time_stop = (UNSIGNED32)time(NULL);
   while(((UNSIGNED32)time(NULL) - cch_time_stop) < seconds);
}


c_mvbSock::c_mvbSock()
{
    this->Owner = NULL;                                 //线程事件
    //m_Thread.Owner = this;
    //m_Thread.OwnerType = C_Thread::MVBSocket;
}


void c_mvbSock::Run()
{
    //m_Thread.start();                                   //开始线程
}

TCN_DECL_PUBLIC MUE_RESULT c_mvbSock::MVB_Put_Data(WORD16 port_address,void *p_port_data)
{
    if(MVBisOpen == false)
        return MUE_RESULT_ERROR;
    //===============================================
    MUE_RESULT  result;
    
    result = BBDC02C_PutData(port_address,(unsigned char *)p_port_data);
    pd_put_port_address = port_address;
    //===============================================
    qDebug("pd_put_port_address == %x",pd_put_port_address);
    return result;
}

TCN_DECL_PUBLIC MUE_RESULT c_mvbSock::MVB_Close()
{
    MUE_RESULT  result;
    
    result = BBDC02C_Uninit();
    return result;
}

TCN_DECL_PUBLIC MUE_RESULT c_mvbSock::MVB_Get_Data(    WORD16      port_address,
                                                       BITSET8     *p_port_status,
                                                       void        *p_port_data,
                                                       UNSIGNED16  *p_port_freshness)
{
    if(MVBisOpen == false)
        return MUE_RESULT_ERROR;
    //===============================================
    MUE_RESULT  result;
    result =BBDC02C_GetData(port_address,p_port_status,(unsigned char *)p_port_data,p_port_freshness);
    //===============================================
    //printf("pd_get_port_address == %x",pd_get_port_address);
    return result;
}


TCN_DECL_PUBLIC MUE_RESULT c_mvbSock::MVB_init_port(void *p_bus_ctrl, BITSET16 port_dir, BITSET16 port_addr, BITSET16 port_size)
{
    E_MVB_PORTDIR TempPortDir=E_MVB_PORTDIR_SNK;
    unsigned short sPortSize=0;
    unsigned char *ptr = (unsigned char *) p_bus_ctrl;
    
    if((MVBisOpen == false)||(*ptr == 0))
        return MUE_RESULT_ERROR;
    //===============================================
    if(port_dir == MUE_PD_FULL_PORT_CONFIG_SRC)
    {
        TempPortDir = E_MVB_PORTDIR_SRC;
    }
    else if(port_dir == MUE_PD_FULL_PORT_CONFIG_SINK)
    {
        TempPortDir = E_MVB_PORTDIR_SNK;
    }
    else
    {
        return MUE_RESULT_ERROR;
    }
    //==================================================
    switch( port_size )
    {
        case MUE_PD_FULL_PORT_CONFIG_FC4:
            sPortSize=E_MVBPORT_SIZE32;
            break;
        case MUE_PD_FULL_PORT_CONFIG_FC3:
            sPortSize=E_MVBPORT_SIZE16;
            break;
        case MUE_PD_FULL_PORT_CONFIG_FC2:
            sPortSize=E_MVBPORT_SIZE8;
            break;
        case MUE_PD_FULL_PORT_CONFIG_FC1:
            sPortSize=E_MVBPORT_SIZE4;
            break;
        case MUE_PD_FULL_PORT_CONFIG_FC0:
            sPortSize=E_MVBPORT_SIZE2;
            break;
        default:
            return MUE_RESULT_ERROR;
            break;       
    }
    //==================================================
    return BBDC02C_RegPort(TempPortDir,port_addr,sPortSize);
    //===============================================
}

TCN_DECL_PUBLIC MUE_RESULT c_mvbSock::MVB_Stop(void *p_bus_ctrl)
{
    unsigned char *ptr = (unsigned char *) p_bus_ctrl;
    if((MVBisOpen == false)||(*ptr == 0))
        return MUE_RESULT_ERROR;
   //=============================================== 
   return MVB_Close(); 
   //===============================================
}


TCN_DECL_PUBLIC MUE_RESULT c_mvbSock::MVB_Init()
{
    MUE_RESULT  result;
    bus_id = 0;
    p_bus_ctrl = (void*)&bus_id;
    result=BBDC02C_Init(); 
    qDebug("BBDC02c_Init result = %d\n",result);
    if (result == MUE_RESULT_OK)
    {
        MVBisOpen = true;
        bus_id = 1;
        p_bus_ctrl = (void*)&bus_id;
    }
    else
    {
        MVBisOpen = false;
    }
    return result;
}

TCN_DECL_PUBLIC MUE_RESULT c_mvbSock::MVB_Start(void *p_bus_ctrl,BITSET16 device_address)
{
    unsigned char *ptr = (unsigned char *) p_bus_ctrl;
    if((MVBisOpen == false)||(*ptr == 0))
        return MUE_RESULT_ERROR;
    
    else    
        return BBDC02C_Start(device_address);   
}


void c_mvbSock::ThreadFun()                             //线程回调函数
{
 

//    if(MVBisOpen == false)                  //检测是否打开
//        return;
    
//    // ===============================================
//    result = MVB_Get_Data(0x300,&pd_port_status,&pd_port_data_get[0],&pd_port_freshness);
    
//    // 检测读取是否成功
//    qDebug("MVB_Get_Data result = %d",result);
//    if(result != MUE_RESULT_OK)
//        return;
//    // ===============================================
    
//    QString str,str1;
//    str.sprintf("pd_port_status = %d",pd_port_status);
//    qDebug()<<str;
//    str.sprintf("freshness = %d",pd_port_freshness);
//    qDebug()<<str;
    
//    // ===============================================
//    str = "Rev Data = ";
//    str1 = "";
//    for(int i = 0; i < 32; i++)
//    {
//        str1.sprintf("%02X",pd_port_data_get[i]);
//        str = str + " " + str1;
//    }
//    MainWindow* pOwner = (MainWindow*)this->Owner;
//    pOwner->OnMVBData(str);
}
