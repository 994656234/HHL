#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/ioctl.h>
#include <unistd.h>
#include <QDebug>
#include "blacklightthread.h"


BlackLightThread::BlackLightThread()
{

}

void BlackLightThread::run()
{
    int current_lux = 0;
    int lightLevel = 7;

    while(1)
    {
        if(_BacklightAuto)
        {
            current_lux = _getSensorLux();
            if(current_lux < 5)
            {
                lightLevel = 0;
            }
            else if(current_lux < 10)
            {
                lightLevel = 1;
            }
            else if(current_lux < 15)
            {
                lightLevel = 2;
            }
            else if(current_lux < 20)
            {
                lightLevel = 3;
            }
            else if(current_lux < 35)
            {
                lightLevel = 4;
            }
            else if(current_lux < 50)
            {
                lightLevel = 5;
            }
            else if(current_lux < 75)
            {
                lightLevel = 6;
            }
            else
            {
                lightLevel = 7;
            }

            _setBlacklight(lightLevel);
        }
        else
        {
            break;
        }
        sleep(1);
    }

    return ;
}

int BlackLightThread::setAuto(bool lightAuto)
{
    int ret = 0;

    if(lightAuto)
    {
        _BacklightAuto = true;
        ret = _setSensorMode(1);

    }
    else
    {
        _BacklightAuto = false;
        ret = _setSensorMode(0);
    }

    return ret;
}

int BlackLightThread::_setBlacklight(int light)
{
    int fd = -1;
    int ret = -1;
    QString str;

    if(light > 7 || light < 1)
        return 0;

    fd = open(BACKLIGHT_SET_DEVICE_FILE, O_WRONLY);
    if(fd < 0)
     {
        qDebug() << "Open backlight brightness file failed!";
        return -1;
    }

    str.sprintf("%d", light);

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

int BlackLightThread::_setSensorMode(int mode)
{
    int fd = -1;
    int ret = -1;
    QString str;

    if(0 == mode)
        mode = 0;
    else
        mode = 5;

    fd = open(SENSOR_MODE,O_WRONLY);
    if(fd < 0)
    {
        qDebug() << "set Sensor Mode Failed!";
        return -1;
    }

    str.sprintf("%d", mode);
    ret = write(fd, str.toLatin1().data(), sizeof(str));
    if(ret < 0)
    {
        qDebug() << "write Mode Failed!";
        close(fd);
        return -1;
    }

    close(fd);

    return 0;
}

int BlackLightThread::_getSensorLux()
{
    int fd = -1;
    int ret = -1;
    int lux =0;
    char buff[8] = {0};

    fd = open(SENSOR_LUX, O_RDONLY);
    if(fd < 0)
    {
        qDebug() << "open Sensor Lux file failed\n";
        return -1;
    }

    ret = read(fd, buff, sizeof(buff));
    if(ret < 0)
    {
        qDebug() << "read Sensor Lux failed\n";
        close(fd);
        return -1;
    }

    close(fd);

    lux = atoi(buff);

    return lux;
}

bool BlackLightThread::getBacklightAuto()
{
    return _BacklightAuto;
}
