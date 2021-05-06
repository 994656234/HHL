
#ifndef __AVIC_IMX_H__
#define __AVIC_IMX_H__
#include <sys/types.h>
#ifdef __cplusplus
extern "C" {
#endif

//===============================public===========================================
// fun: init function
// bit [0-7]
// bit0: 0 have no hardware key;  1 have hardware key
// bit1
//
void avic_imx_init(unsigned char fun);
void avic_imx_destory(void);
//val : 30-200
//return : current brightness
unsigned char avic_SetManualBrightness(unsigned char val);
//state:   0 manual;  other val auto;
//return: none
void avic_SetAutoBrightness(unsigned char state);
// return: current backlight value
unsigned char avic_GetBackLight(void);
// return: return environment brightness
unsigned char avic_GetBrightness(void);
// get cur key value
unsigned char avic_GetKey(void);
//set led state, 0 off;   1 on
//bit0 red
//bit1 green
//bit2 yellow
void avic_SetLedState(unsigned char state);
//get led state, 0 off;   1 on
//bit0 red
//bit1 green
//bit2 yellow
unsigned char avic_GetLedState(void);
//return avic lib version
const char * avic_GetLibVersion(void);

//打开/关闭峰鸣器
// 1 打开
// 0 关闭
void avic_beep(unsigned char state);

//设置自动亮度调节时，最小背光亮度(默认是30)
//val = 0 ~ 150
int avic_set_min_autobacklight(unsigned short val);

//设置亮度调节阀值(默认是15)
// val = 10~50建议设置为5的倍数
int avic_set_autobacklight_threshold(unsigned short val);

//================================GZB04 only=====================================================================
#define RS485_422_DEV1  0
#define RS485_422_DEV2  1
#define RS485_SND   0x01
#define RS485_RECV  0x02
#define RS485_FULL  0x03

#define TPA_CHNL_LEFT        0x01
#define TPA_CHNL_RIGHT     0x02
#define TPA_CHNL_ALL          0x03
#define TPA_CHNL_OFF         0x00
//设置RS422方向
//port RS485_422_DEV1代表第一路   RS485_422_DEV2代表第二路
//state RS485_SND 仅发送   RS485_RECV仅接受   RS485_FULL 发送&接收
void avic_rs422(unsigned char port, unsigned char state);
//gps电源控制
//state = 0关闭电源   1打开电源
void avic_gps_pwr(unsigned char state);
//产生 1s 低电平复位
void avic_gps_rst(void);
//音频功放控制
// TPA_CHNL_LEFT 左声道    TPA_CHNL_RIGHT右声道 TPA_CHNL_ALL双声道
void avic_amp_ctrl_chn(unsigned char channel );
//音频功放控制
// vol = 0 - 3
void avic_amp_ctrl_vol(unsigned char vol);



//================================GZB01 only=============================================================================
//设置485方向
// 1 发送
// 0 接收
void avic_485DE(unsigned char state);
//获取主板电压状态
//0获取3.3V
//1获取12V
//2获取5V
//返回 单位是mv
unsigned short avic_GetVolts(unsigned char channel);
/*描述：音量设置  输入：vol(1-100)*/
void avic_audio_SetVol(unsigned int vol);
//mvb  初始化
// 返回值：0成功  其它失败
u_int8_t avic_mvb_init(void);
//mvb  端口初始化
// 返回值：0成功  其它失败
//@ port_dir: 0 sink   1 source
//@port_addr: 0x000-0xfff
//@port_size: 32/16/8/4/2
u_int8_t avic_mvb_port_init(unsigned char port_dir,unsigned short port_addr,unsigned char port_size);
//mvb  开始通讯
// 返回值：0成功  其它失败
//@ devaddr: 0x000-0xfff 设备地址
u_int8_t avic_mvb_start(u_int16_t devaddr);
//mvb  状态
// 返回值：0成功  其它失败
u_int8_t avic_mvb_status(void);
//端口数据发送
//@port_address 端口地址
//@data 发送数据首地址
u_int8_t avic_mvb_putdata(unsigned short port_address, unsigned char * data);
//端口数据接收
//@port_address 端口地址
//@p_port_status 端口状态  :数据从LINA接收    0x80, 数据从LINB接收    0x40
//@p_port_data 接收数据首地址
//@p_port_freshness 数据新鲜度 0-65535
//返回值: 0成功  1失败
u_int8_t avic_mvb_getdata(unsigned short port_address, unsigned char *p_port_status, unsigned char *p_port_data, unsigned short *p_port_freshness);



#ifdef __cplusplus
}
#endif
#endif
