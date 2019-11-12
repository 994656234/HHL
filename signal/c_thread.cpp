#include "c_thread.h"
//#include "../can/c_cansocket.h"
#include "../mvb/c_mvbsock.h"
//#include "../Modbus/modbus_rev.h"
//#include "../NFC/c_pn5180.h"
//#include "../net/net.h"
C_Thread::C_Thread()
{
    OwnerType = C_Thread::CanSocket;
    iswait = false;
    this->Owner = NULL;
    WaitTime = 10;
}

void C_Thread::Sleep(int stime)
{
   QThread::msleep(stime);
}

bool C_Thread::Wait(int stime)
{
    bool res =false;

     iswait = true;
    res = wait.wait(&mutex,stime);
     iswait = false;

     return res;
}

void C_Thread::Set()
{
     wait.wakeAll();
     iswait = false;
}

bool C_Thread::IsWaiting()   //等待中
{
    return iswait;
}

void C_Thread::run()
{
    stop = false;
    while(true)
    {
        if (stop)
            break;
        if (this->Owner == NULL)
        {
            break;
        }
        if (this->OwnerType == C_Thread::CanSocket)
        {
            C_Cansocket *can =(C_Cansocket*)this->Owner;
            can->ThreadFun();
        }
        if (this->OwnerType == C_Thread::MVBSocket)
        {
            c_mvbSock *mvb =(c_mvbSock*)this->Owner;
            mvb->ThreadFun();
            QThread::msleep(40);
        }
        if(this->OwnerType == C_Thread::ModbusRev)
        {
            Modbus_Rev *Modbus =(Modbus_Rev*)this->Owner;
            Modbus->_Thread_Run_Function();
        }
//        if(this->OwnerType == C_Thread::NFCThread)
//        {
//            C_PN5180 *PN5180 =(C_PN5180*)this->Owner;
//            PN5180->ThreadFun();
//        }
        if(this->OwnerType == C_Thread::NETThread)
        {
            net *pnet = (net*)this->Owner;
            pnet->ThreadFun();
        }
        QThread::msleep(WaitTime);
    }
}
