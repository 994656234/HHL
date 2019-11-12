#include "ccustomevent.h"

CCustomEvent::CCustomEvent():QEvent((QEvent::Type)CusType)
{
    param = NULL;
    paramstr = "";
}

CCustomEvent::~CCustomEvent()
{
    if (param != NULL)
        delete param;
}

void CCustomEvent::SetParam(int cmd,QObject* val)
{
    this->Command = cmd;
    this->param = val;
}
