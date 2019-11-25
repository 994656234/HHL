#include "c_mvbsock.h"
c_mvbSock::c_mvbSock()
{
    this->Owner = NULL;
    //线程事件
}

void c_mvbSock::cdelay (int seconds)
{
    UNSIGNED32 cch_time_stop = (UNSIGNED32)time(NULL);
    while(((UNSIGNED32)time(NULL) - cch_time_stop) < seconds);
}

MUE_RESULT c_mvbSock::mue_app_init_device (void *p_bus_ctrl)
{
    MUE_RESULT  result;
    BITSET16    sv_device_config;
    BITSET16    sv_device_config_put __attribute__((unused));
    BITSET16    sv_device_config_get __attribute__((unused));
    WORD16      pd_port_address;
    BITSET16    pd_port_config;


    /* ----------------------------------------------------------------------
     *  Initialise MVB UART Emulation
     * ----------------------------------------------------------------------
     */
#ifdef MUE_APP_PRINT
    MUE_OSL_PRINTF("- mue_acc_init()\n");
#endif /* #ifdef MUE_APP_PRINT */

    result = mue_acc_init(p_bus_ctrl);//打开/dev/locbus设备

#ifdef MUE_APP_PRINT
    MUE_OSL_PRINTF("- mue_acc_init()=%d\n", (unsigned int)result);
#endif /* #ifdef MUE_APP_PRINT */


    /* ----------------------------------------------------------------------
     *  Clean-up MVB UART Emulation
     * ----------------------------------------------------------------------
     */
    if (MUE_RESULT_OK == result)
    {
#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_acc_clean_up()\n");
#endif /* #ifdef MUE_APP_PRINT */

        result = mue_acc_clean_up(p_bus_ctrl);//写入35个0

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_acc_clean_up()=%d\n", (unsigned int)result);
#endif /* #ifdef MUE_APP_PRINT */

    } /* if (MUE_RESULT_OK == result) */


    /* ----------------------------------------------------------------------
     *  Soft reset of MVB Controller (i.e. disconnect from MVB bus)
     * ----------------------------------------------------------------------
     */
    if (MUE_RESULT_OK == result)
    {
        sv_device_config = (BITSET16)0x0000;

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_sv_put_device_config(0x%04X)\n", \
            (unsigned int)sv_device_config);
#endif /* #ifdef MUE_APP_PRINT */
        //soft reset
        result = mue_sv_put_device_config(p_bus_ctrl, sv_device_config);//按要求格式写入配置信息

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_sv_put_device_config(0x%04X)=%d\n", \
            (unsigned int)sv_device_config, (unsigned int)result);
#endif /* #ifdef MUE_APP_PRINT */

    } /* if (MUE_RESULT_OK == result) */


    /* ----------------------------------------------------------------------
     *  Clear configuration of all MVB Process Data Ports
     *  (i.e. configure all ports as SINK)
     * 清空所有mvb端口，将所有端口都配置为接收(SINK)
     * ----------------------------------------------------------------------
     */
    if (MUE_RESULT_OK == result)
    {
#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_pd_full_put_port_config(ALL)\n");
#endif /* #ifdef MUE_APP_PRINT */
        pd_port_address = 0;
        while ((MUE_RESULT_OK == result) && \
               (pd_port_address < mue_pd_full_port_number_max))// mue_pd_full_port_number_max = 4096
        {
            pd_port_config = (BITSET16)(pd_port_address);
            //端口配置
            result =                        \
                mue_pd_full_put_port_config \
                (                           \
                    p_bus_ctrl,             \
                    pd_port_config          \
                );
            if (MUE_RESULT_OK != result)
            {
#ifdef MUE_APP_PRINT
                MUE_OSL_PRINTF                                            \
                    ("- ERROR: mue_pd_full_put_port_config(0x%04X)=%d\n", \
                        (unsigned int)pd_port_config, (unsigned int)result);
#endif /* #ifdef MUE_APP_PRINT */
            } /* if (MUE_RESULT_OK != result) */
            else
            {
                pd_port_address++;
            } /* else */
        } /* while ((MUE_RESULT_OK == result) && (pd_port_address < ...)) */
    } /* if (MUE_RESULT_OK == result) */

    return(result);

}

//
TCN_DECL_PUBLIC
MUE_RESULT c_mvbSock::mue_app_init_port(void *p_bus_ctrl,BITSET16 pd_port_config)
{
    MUE_RESULT  result;
    WORD16      pd_port_address;
    WORD8       pd_port_data[MUE_PD_FULL_PORT_SIZE_MAX];
    qDebug("mue_app_init_port pd_port_config==%x",pd_port_config);
                /* ----------------------------------------------------------
                 *  NOTE:
                 *  "pd_port_data" is a buffer of 32 bytes, which
                 *  is the max. size of a MVB Process Data port.
                 * ----------------------------------------------------------
                 */


    /* ----------------------------------------------------------------------
     *  Configure MVB Process Data Port
     * ----------------------------------------------------------------------
     */
#ifdef MUE_APP_PRINT
    MUE_OSL_PRINTF("- mue_pd_full_put_port_config(0x%04X)\n", \
        (unsigned int)pd_port_config);
#endif /* #ifdef MUE_APP_PRINT */
    //配置端口  pd_port_config包含端口地址/大小/方向
    result =                        \
        mue_pd_full_put_port_config \
        (                           \
            p_bus_ctrl,             \
            pd_port_config          \
        );

#ifdef MUE_APP_PRINT
    MUE_OSL_PRINTF("- mue_pd_full_put_port_config(0x%04X)=%d\n", \
        (unsigned int)pd_port_config, (unsigned int)result);
#endif /* #ifdef MUE_APP_PRINT */


    /* ----------------------------------------------------------------------
     *  Set all bytes of port data to 0x00
     * ----------------------------------------------------------------------
     */
    if (MUE_RESULT_OK == result)
    {
        pd_port_address = \
            (WORD16)(pd_port_config & mue_pd_full_port_config_la_mask);//获取端口地址
        memset((void*)pd_port_data, 0, mue_pd_full_port_size_max);//将端口数据设置为0

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_pd_full_put_port_data(0x%03X)\n", \
            (unsigned int)pd_port_address);
#endif /* #ifdef MUE_APP_PRINT */
        //向端口写入数据,此处全部写0
        result =                            \
            mue_pd_full_put_port_data       \
            (                               \
                p_bus_ctrl,                 \
                pd_port_address,            \
                mue_pd_full_port_size_max,  \
                pd_port_data                \
            );

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_pd_full_put_port_data(0x%03X)=%d\n", \
            (unsigned int)pd_port_address, (unsigned int)result);
#endif /* #ifdef MUE_APP_PRINT */

    } /* if (MUE_RESULT_OK == result) */


    return(result);

}

//
TCN_DECL_PUBLIC
MUE_RESULT c_mvbSock::mue_init_port(void *p_bus_ctrl,BITSET16 port_dir,BITSET16 port_addr,BITSET16	port_size)
{
    BITSET16	pd_port_config = port_dir | (port_addr & MUE_PD_FULL_PORT_CONFIG_LA_MASK) | port_size;
    qDebug("pd_port_config == %X",pd_port_config);
    return mue_app_init_port (p_bus_ctrl, pd_port_config);
}

//
TCN_DECL_PUBLIC
MUE_RESULT c_mvbSock::mue_start_mvb_communication(void *p_bus_ctrl,BITSET16 device_address)
{
    device_address &= MUE_SV_DEVICE_CONFIG_DA_MASK;
    qDebug("device_address == %x",device_address);
    return mue_sv_put_device_config(p_bus_ctrl, device_address | MUE_SV_DEVICE_CONFIG_LINE_A | MUE_SV_DEVICE_CONFIG_LINE_B |
                                    MUE_SV_DEVICE_CONFIG_LED_DNR); //mue_sv.h
}

//
TCN_DECL_PUBLIC
MUE_RESULT c_mvbSock::mue_stop_mvb_communication(void  *p_bus_ctrl)
{
    return mue_sv_put_device_config(p_bus_ctrl, 0x0000);
}

/******************************************
 *MVB_Init MVB初始化
 * 所有端口设置为sink 端口号从1-4096
 *返回 MUE_RESULT 状态
******************************************/
TCN_DECL_PUBLIC MUE_RESULT c_mvbSock::MVB_Init()
{
    MUE_RESULT  result;
    bus_id = 0;
    p_bus_ctrl = (void*)&bus_id;
    MVB_Close();
    result = mue_app_init_device(p_bus_ctrl);
    if (MUE_RESULT_OK == result)
        MVBisOpen = true;
    else
        MVBisOpen = false;
    return result;
}


TCN_DECL_PUBLIC MUE_RESULT c_mvbSock::MVB_Close()
{
    MUE_RESULT  result;
    result = mue_acc_close(p_bus_ctrl);

    MVBisOpen = false;
    return result;
}

/******************************************
 *MVB_init_port MVB 端口设定
 *返回 MUE_RESULT 状态
******************************************/
TCN_DECL_PUBLIC MUE_RESULT c_mvbSock::MVB_init_port(void *p_bus_ctrl,BITSET16 port_dir,BITSET16 port_addr,BITSET16 port_size)
{
    if(MVBisOpen == false)
        return MUE_RESULT_ERROR;
    MUE_RESULT  result;
    result = mue_init_port(p_bus_ctrl, port_dir, port_addr, port_size);
    return result;
}

/******************************************
 *MVB_Start MVB 启动运行
 *返回 MUE_RESULT 状态
******************************************/
TCN_DECL_PUBLIC MUE_RESULT c_mvbSock::MVB_Start(void *p_bus_ctrl,BITSET16 device_address)
{
    if(MVBisOpen == false)
        return MUE_RESULT_ERROR;
    MUE_RESULT  result;
    result =  mue_start_mvb_communication (p_bus_ctrl, device_address);
    return result;
}

/******************************************
 *MVB_Stop MVB 停止运行
 *返回 MUE_RESULT 状态
******************************************/
TCN_DECL_PUBLIC MUE_RESULT c_mvbSock::MVB_Stop(void *p_bus_ctrl)
{
    if(MVBisOpen == false)
        return MUE_RESULT_ERROR;
    MUE_RESULT  result;
    result =  mue_stop_mvb_communication (p_bus_ctrl);
    return result;
}

/******************************************
 *MBV_put_device_config MVB device related configuration to a MVB controlle
 *返回 MUE_RESULT 状态
******************************************/
TCN_DECL_PUBLIC MUE_RESULT c_mvbSock::MBV_put_device_config(void *p_bus_ctrl,BITSET16 device_config)
{
    if(MVBisOpen == false)
        return MUE_RESULT_ERROR;
    MUE_RESULT  result;
    result = mue_sv_put_device_config(p_bus_ctrl, device_config);
    return result;
}

/******************************************
 *MVB_ba_config BA Set
 *返回 MUE_RESULT 状态
******************************************/
TCN_DECL_PUBLIC MUE_RESULT c_mvbSock::MVB_ba_config(void *p_bus_ctrl)
{
    if(MVBisOpen == false)
        return MUE_RESULT_ERROR;
    MUE_RESULT  result;
    result = mue_ba_config(p_bus_ctrl);
    return result;
}

/******************************************
 *MVB_Get_Data 接受数据
 *返回 MUE_RESULT 状态
******************************************/
TCN_DECL_PUBLIC MUE_RESULT c_mvbSock::MVB_Get_Data(    WORD16      port_address,
                                                       BITSET8     *p_port_status,
                                                       void        *p_port_data,
                                                       UNSIGNED16  *p_port_freshness)
{
    if(MVBisOpen == false)
        return MUE_RESULT_ERROR;
    MUE_RESULT  result;
    result =                            \
            mue_pd_full_get_port_data       \
            (                               \
                p_bus_ctrl,                 \
                port_address,\
                (BOOLEAN1)FALSE,            \
                mue_pd_full_port_size_max,  \
                p_port_status,\
                p_port_data,\
                p_port_freshness\
            );
    //qDebug("pd_get_port_address == %x",pd_get_port_address);
    return result;
}

/******************************************
 *MVB_Put_Data 发送数据
 *返回 MUE_RESULT 状态
 *******************************************/
TCN_DECL_PUBLIC MUE_RESULT c_mvbSock::MVB_Put_Data(    WORD16      port_address,
                                                       void        *p_port_data)
{
    if(MVBisOpen == false)
        return MUE_RESULT_ERROR;
    MUE_RESULT  result;
    result =                            \
        mue_pd_full_put_port_data       \
        (                               \
            p_bus_ctrl,                 \
            port_address,\
            mue_pd_full_port_size_max,  \
            p_port_data\
        );
    qDebug("pd_put_port_address == %x",pd_put_port_address);
    return result;
}

/******************************************
 *MVB_Set_Rev_Port 设置接收端口
 *返回 无
 *******************************************/
void c_mvbSock::MVB_Set_Rev_Port(WORD16 data)
{
    pd_get_port_address = (WORD16)data;
}

/******************************************
 *MVB_Set_Put_Port 设置发送端口
 *返回 无
 *******************************************/
void c_mvbSock::MVB_Set_Put_Port(WORD16 data)
{
    pd_put_port_address = (WORD16)data;
}

void c_mvbSock::Run()
{
    //开始
    //m_Thread.start();
}

//线程回调函数
void c_mvbSock::ThreadFun()
{
    //检测是否打开
    //
    if(MVBisOpen == false)
        return;
    MUE_RESULT  result;
    result = MVB_Get_Data(0x300,&pd_port_status,&pd_port_data_get[0],&pd_port_freshness);
    qDebug("MVB_Get_Data result = %d",result);
    //检测读取是否成功
    if(result != MUE_RESULT_OK)
        return;
    QString str,str1;
    str.sprintf("pd_port_status = %d",pd_port_status);
    qDebug()<<str;
    str.sprintf("freshness = %d",pd_port_freshness);
    qDebug()<<str;
    str = "Rev Data = ";
    str1 = "";
    for(int i = 0; i < 32; i++)
    {
        str1.sprintf("%02X",pd_port_data_get[i]);
        str = str + " " + str1;
    }
//    MainWindow* pOwner = (MainWindow*)this->Owner;
//    pOwner->OnMVBData(str);
    //====================================================================

}
