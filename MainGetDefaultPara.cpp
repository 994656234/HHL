#include "MainGetDefaultPara.h"


#include <QFile>
#include <QSettings>

MainGetDefaultPara::MainGetDefaultPara()
{
}

QString MainGetDefaultPara::path = QString("./configure.ini");

bool MainGetDefaultPara::configureValid()
{
    if (QFile::exists("./configure.ini"))
    {
        QSettings *configure = new QSettings(path, QSettings::IniFormat, 0);

        if (configure->value("/Check/life").toInt() == 1)
        {
            delete configure;

            return true;
        }
        else
        {
            delete configure;

            return false;
        }
    }
    else
    {
        return false;
    }
}

QString MainGetDefaultPara::getString(QString name)
{
    QSettings *configure = new QSettings(path, QSettings::IniFormat, 0);
    QString value = configure->value(name).toString();

    delete configure;
    return value;
}

int MainGetDefaultPara::getInt(QString name)
{
    QSettings *configure = new QSettings(path, QSettings::IniFormat, 0);
    int value = configure->value(name).toInt();

    delete configure;
    return value;
}

void MainGetDefaultPara::set(QString name, int value)
{
    QSettings *configure = new QSettings(path, QSettings::IniFormat, 0);
    configure->setValue(name, value);

    delete configure;
}

void MainGetDefaultPara::set(QString name, QString value)
{
    QSettings *configure = new QSettings(path, QSettings::IniFormat, 0);
    configure->setValue(name, value);

    delete configure;
}
