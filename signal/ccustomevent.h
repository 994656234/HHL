#ifndef CCUSTOMEVENT_H
#define CCUSTOMEVENT_H

#include <QEvent>
#include <QString>
class CCustomEvent : public QEvent
{
public:
    CCustomEvent();
    ~CCustomEvent();

    void     SetParam(int cmd,QObject* val);
public:
    int      Command;
    QObject* param;
    QString  paramstr;
    QString  RData;
    QByteArray ByteData;
    double   fVal;
    bool     fOk;

    enum     Type{CusType=9393};
};

#endif // CCUSTOMEVENT_H
