
#ifndef __AVIC_IMX_H__
#define __AVIC_IMX_H__
#include <sys/types.h>
#ifdef __cplusplus
extern "C" {
#endif
#define KEY_FIFO_SIZE	20
/* 按键滤波时间20ms, 单位10ms
 只有连续检测到20ms状态不变才认为有效，包括弹起和按下两种事件
*/
#define BUTTON_FILTER_TIME 	2
#define BUTTON_LONG_TIME 	10		/* 持续1秒，认为长按事件 */

/*
    每个按键对应1个全局的结构体变量。
    其成员变量是实现滤波和多种按键状态所必须的
*/
typedef struct
{
    /* 下面是一个函数指针，指向判断按键手否按下的函数 */
    u_int8_t (*IsKeyDownFunc)(void); /* 按键按下的判断函数,1表示按下 */

    u_int8_t Count;			/* 滤波器计数器 */
    u_int8_t FilterTime;		/* 滤波时间(最大255,表示2550ms) */
    u_int16_t LongCount;		/* 长按计数器 */
    u_int16_t LongTime;		/* 按键按下持续时间, 0表示不检测长按 */
    u_int8_t  State;			/* 按键当前状态（按下还是弹起） */
    u_int8_t KeyCodeUp;		/* 按键弹起的键值代码, 0表示不检测按键弹起 */
    u_int8_t KeyCodeDown;	/* 按键按下的键值代码, 0表示不检测按键按下 */
    u_int8_t KeyCodeLong;	/* 按键长按的键值代码, 0表示不检测长按 */
}BUTTON_T;
typedef struct
{
    u_int8_t Buf[KEY_FIFO_SIZE];		/* 键值缓冲区 */
    u_int8_t Read;	/* 缓冲区读指针 */
    u_int8_t Write;	/* 缓冲区写指针 */
}KEY_FIFO_T;
typedef enum
{
    KEY_NONE = 0,			/* 0 表示按键事件 */
    KEY_U1_DOWN,
    KEY_U1_UP,
    KEY_U2_DOWN,
    KEY_U2_UP,
    KEY_U3_DOWN,
    KEY_U3_UP,
    KEY_U4_DOWN,
    KEY_U4_UP,
    KEY_U5_DOWN,
    KEY_U5_UP,
    KEY_U6_DOWN,
    KEY_U6_UP,
    KEY_U7_DOWN,
    KEY_U7_UP,
    KEY_U8_DOWN,
    KEY_U8_UP,
    KEY_U9_DOWN,
    KEY_U9_UP,
    KEY_U10_DOWN,
    KEY_U10_UP,

    KEY_R1_DOWN,
    KEY_R1_UP,
    KEY_R2_DOWN,
    KEY_R2_UP,
    KEY_R3_DOWN,
    KEY_R3_UP,
    KEY_R4_DOWN,
    KEY_R4_UP,
    KEY_R5_DOWN,
    KEY_R5_UP,
    KEY_R6_DOWN,
    KEY_R6_UP,
    //down
    KEY_D10_DOWN,
    KEY_D10_UP,
    KEY_D9_DOWN,
    KEY_D9_UP,
    KEY_D8_DOWN,
    KEY_D8_UP,
    KEY_D7_DOWN,
    KEY_D7_UP,
    KEY_D6_DOWN,
    KEY_D6_UP,
    KEY_D5_DOWN,
    KEY_D5_UP,
    KEY_D4_DOWN,
    KEY_D4_UP,
    KEY_D3_DOWN,
    KEY_D3_UP,
    KEY_D2_DOWN,
    KEY_D2_UP,
    KEY_D1_DOWN,
    KEY_D1_UP,
    /* */
    KEY_L6_DOWN,//1
    KEY_L6_UP,
    KEY_L5_DOWN,
    KEY_L5_UP,
    KEY_L4_DOWN,
    KEY_L4_UP,
    KEY_L3_DOWN,
    KEY_L3_UP,
    KEY_L2_DOWN,
    KEY_L2_UP,
    KEY_L1_DOWN,
    KEY_L1_UP,
}KEY_ENUM;

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

//获取主板电压状态
//0获取3.3V
//1获取12V
//2获取5V
//返回 单位是mv
unsigned short avic_GetVolts(unsigned char channel);
//设置485方向
// 1 发送
// 0 接收
void avic_485DE(unsigned char state);

//打开/关闭峰鸣器
// 1 打开
// 0 关闭
void avic_beep(unsigned char state);
#ifdef __cplusplus
}
#endif
#endif
