#ifndef COMMAND_H
#define COMMAND_H

#include "serial.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum commandReplyType{
	stringType,
	ACK,
	NAK
}commandReplyType;

commandReplyType rcv_1_command_0(int fd, int command, char *arg1);
commandReplyType rcv_2_command_0(int fd, int command, char *arg1, char *arg2);
commandReplyType rcv_1_command_2(int fd, int command, int arg1, int arg2, char *reply);
commandReplyType rcv_0_command_0(int fd ,int command);
commandReplyType rcv_0_command_1(int fd ,int command, int arg1);
commandReplyType rcv_0_command_2(int fd ,int command, int arg1, int arg2);
commandReplyType rcv_0_command_3(int fd ,int command, int arg1, int arg2, int arg3);
commandReplyType rcv_0_command_4(int fd ,int command, int arg1, int arg2, int arg3, int arg4);
commandReplyType rcv_5_command_0(int fd, int command, char *arg1, char *arg2, char *arg3, char *arg4, char *arg5);

#ifdef __cplusplus
}
#endif

#endif
