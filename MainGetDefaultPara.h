#ifndef MAINGETDEFAULTPARA_H
#define MAINGETDEFAULTPARA_H

#include <QString>

class MainGetDefaultPara
{
public:
    MainGetDefaultPara();
    static bool configureValid();
    static QString getString(QString name);
    static int getInt(QString name);
    static void set(QString name, QString value);
    static void set(QString name, int value);

private:
    static QString path;
};

#endif // MAINGETDEFAULTPARA_H
