#ifndef BLACKLIGHTTHREAD_H
#define BLACKLIGHTTHREAD_H
#include <QThread>

#define SENSOR_LUX          "/sys/class/i2c-dev/i2c-1/device/1-0044/lux"
#define SENSOR_MODE         "/sys/class/i2c-dev/i2c-1/device/1-0044/mode"
#define BACKLIGHT_SET_DEVICE_FILE   "/sys/class/backlight/backlight/brightness"
#define BACKLIGHT_GET_DEVICE_FILE   "/sys/class/backlight/backlight/actual_brightness"

class BlackLightThread : public QThread
{
public:
    BlackLightThread();
    void run();
    int setAuto(bool lightAuto);
    bool getBacklightAuto();
private:
    bool _BacklightAuto;
    int _setSensorMode(int mode);
    int _getSensorLux();
    int _setBlacklight(int light);
};

#endif // BLACKLIGHTTHREAD_H
