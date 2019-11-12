#ifndef EXTERNALDEVICELIB_H
#define EXTERNALDEVICELIB_H

#include <QObject>
#include "blacklightthread.h"

class ExternalDeviceLib : public QObject
{
    Q_OBJECT
public:
    explicit ExternalDeviceLib(QObject *parent = 0);
    ~ExternalDeviceLib();
    int getBlacklightBrightness();
    int setBlacklihtBrightness(int lightVal);
    int setBuzzer(bool onOff);
    int setBlacklightAuto(bool lightAuto);
    bool getBlacklibhtAuto();

private:
    //BlackLightThread *B_Thread = nullptr;

signals:

public slots:
};

#endif // EXTERNALDEVICELIB_H
