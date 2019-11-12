#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/ioctl.h>
#include <unistd.h>
#include <QDebug>

#include "externaldevicelib.h"

ExternalDeviceLib::ExternalDeviceLib(QObject *parent) : QObject(parent)
{
    //B_Thread = new BlackLightThread();
}
ExternalDeviceLib::~ExternalDeviceLib()
{
    //delete B_Thread;
}
int ExternalDeviceLib::getBlacklightBrightness()
{
    int fd = -1;
    int ret = -1;
    int light =0;
    char buff[8] = {0};

    fd = open(BACKLIGHT_GET_DEVICE_FILE, O_RDONLY);
    if(fd < 0)
    {
        qDebug() << "open backlight brightness file failed\n";
        return -1;
    }

    ret = read(fd, buff, 1);
    if(ret < 0)
    {
        qDebug() << "read backlight brightness failed\n";
        close(fd);
        return -1;
    }

    close(fd);

    light = atoi(buff);

    return light;
}

int ExternalDeviceLib::setBlacklihtBrightness(int lightVal)
{
    int fd = -1;
    int ret = -1;
    QString str;

    if(lightVal > 7 || lightVal < 1)
        return 0;

    fd = open(BACKLIGHT_SET_DEVICE_FILE, O_WRONLY);
    if(fd < 0)
    {
        qDebug() << "Open backlight brightness file failed!";
        return -1;
    }

    str.sprintf("%d", lightVal);

    ret = write(fd, str.toLatin1().data(), sizeof(str));
    if(ret < 0)
    {
        qDebug() << "write backlight brightness failed!";
        close(fd);
        return -1;
    }

    close(fd);

    return 0;
}


int ExternalDeviceLib::setBlacklightAuto(bool lightAuto)
{
    int ret = 0;

//    if(true == lightAuto && true == B_Thread->getBacklightAuto())
//        return 0;
//    if(false == lightAuto && false == B_Thread->getBacklightAuto())
//        return 0;

//    if(lightAuto)
//    {
//        B_Thread->setAuto(true);
//        B_Thread->start();
//    }
//    else
//    {
//        if(B_Thread)
//        {
//            if(B_Thread->getBacklightAuto())
//            {
//                B_Thread->setAuto(false);
//            }
//            B_Thread->quit();
//        }
//    }

    return ret;
}

bool ExternalDeviceLib::getBlacklibhtAuto()
{
//    if(B_Thread)
//        return B_Thread->getBacklightAuto();
//    else
        return false;
}

int ExternalDeviceLib::setBuzzer(bool onOff)
{
    if(onOff)
    {
       system("ledapp.exe 0x8 -o > /dev/null 2>&1 &");
    }
    else
    {
        system("ledapp.exe 0x8 -c > /dev/null 2>&1 &");
    }

    return 0;
}
