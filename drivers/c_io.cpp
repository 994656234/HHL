#include "c_io.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/kd.h>
#include <stdlib.h>
#include <stdio.h>
#include <QDebug>
C_io::C_io()
{
}
void C_io::IO_Init_1709()
{
    IO_Open_Gpio(4,5);
    IO_Open_Gpio(1,4);
    IO_SetDriection(IO_GPS_Reset,OUT);
    IO_SetDriection(IO_Buzzer,OUT);
    IO_Write(IO_Buzzer,false);
    IO_Write(IO_GPS_Reset,true);
}
void C_io::IO_Init_1708()
{
    IO_Open_Gpio(4,5);
    IO_SetDriection(IO_Buzzer,OUT);
    IO_Write(IO_Buzzer,false);
}
void C_io::IO_Init_GZB01()
{
    IO_Open_Gpio(2,5);
    IO_SetDriection(IO_485DE,OUT);
    IO_Write(IO_485DE,false);
}
bool C_io::IO_Open_Gpio(int iGpio,int iNo)
{
    int fd;
    int num;
    fd = open(IO_EXPORT,O_WRONLY);
    if(fd == -1)
    {
        return -1;
    }
    num = (iGpio-1)*32+iNo;
    char *buffer;
    buffer = (char*)malloc(sizeof(int)+1);
    sprintf(buffer,"%d",num);
    write(fd,buffer,sizeof(buffer));
    usleep(200);
    free(buffer);
    close(fd);
    return 0;
}
int C_io::IO_SetDriection(int Type,bool direction)
{
    int fd = -1;
    if(Type == IO_GPS_Reset)
        fd = open(IO_GPSReset_dir,O_WRONLY);
    else if(Type == IO_Buzzer)
        fd = open(IO_Buzzer_dir,O_WRONLY);
    else if(Type == IO_485DE)
        fd = open(IO_485DE_dir,O_WRONLY);
    if(fd == -1)
    {
        printf("IO_SetDriection()=-1\n");
        return -1;
    }
    char *buffer;
    if(direction == IN)
        buffer = "in";
    else
        buffer = "out";
    write(fd,buffer,sizeof(buffer));
    usleep(200);
    close(fd);
    return 0 ;
}
int C_io::IO_Write(int Type,bool value)
{
    int fd = -1;
    if(Type == IO_GPS_Reset)
        fd = open(IO_GPSReset_value,O_WRONLY);
    else if(Type == IO_Buzzer)
        fd = open(IO_Buzzer_value,O_WRONLY);
    else if(Type == IO_485DE)
        fd = open(IO_485DE_value,O_WRONLY);
    if(fd == -1)
    {
        printf("IO_Write()=-1\n");
        return -1;
    }
    char *buffer;
    if(value == true)
        buffer = "1";
    else
        buffer = "0";
    if(write(fd,buffer,sizeof(buffer))== -1)
        printf("IO write error\n");
    usleep(200);
    close(fd);
    return 0 ;
}
int C_io::IO_Read(int Type)
{
    int fd = -1;
    if(Type == IO_GPS_Reset)
        fd = open(IO_GPSReset_value,O_RDWR);
    else if(Type == IO_Buzzer)
        fd = open(IO_Buzzer_value,O_RDWR);
    else if(Type == IO_485DE)
        fd = open(IO_485DE_value,O_RDWR);
    if(fd == -1)
    {
        printf("IO_Read()= -1.\n");
        return -1;
    }
    char readbuffer[1];
    read(fd,readbuffer,1);
    close(fd);
    if((readbuffer[0]&0xff) == 0x30)
        return 0;
    else
        return 1;
}
int C_io::ADC_Read(int Type)
{
    int fd = -1;
    if(Type == ADC_IN0)
        fd = open(ADC_IN0_value,O_RDONLY);
    else if(Type == ADC_IN1)
        fd = open(ADC_IN1_value,O_RDONLY);
    else if(Type == ADC_IN2)
        fd = open(ADC_IN2_value,O_RDONLY);
    if(fd == -1)
    {
        printf("ADC_Read()= -1.\n");
        return -1;
    }
    char data[20];
    read(fd,data,4);
    QString str;
    str.sprintf("%d%d%d%d",AsciitoHex(data[0]),AsciitoHex(data[1]),AsciitoHex(data[2]),AsciitoHex(data[3]));
    close(fd);
    return str.toInt(false,10);
}
char C_io::AsciitoHex(char data)
{
    char pc;
    if(data == 0x30)
        pc = 0x00;
    else if (data == 0x31)
        pc = 0x01;
    else if (data == 0x32)
        pc = 0x02;
    else if (data == 0x33)
        pc = 0x03;
    else if (data == 0x34)
        pc = 0x04;
    else if (data == 0x35)
        pc = 0x05;
    else if (data == 0x36)
        pc = 0x06;
    else if (data == 0x37)
        pc = 0x07;
    else if (data == 0x38)
        pc = 0x08;
    else if (data == 0x39)
        pc = 0x09;
    else if (data == 0x41)
        pc = 0x0A;
    else if (data == 0x42)
        pc = 0x0B;
    else if (data == 0x43)
        pc = 0x0C;
    else if (data == 0x44)
        pc = 0x0D;
    else if (data == 0x45)
        pc = 0x0E;
    else if (data == 0x46)
        pc = 0x0F;
    return pc;
}
