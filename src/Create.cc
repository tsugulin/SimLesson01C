#include "Create.h"
Define_Module(Create);

void Create::initialize()
{
    scheduleAt(simTime() + par("intervalTime"), new cMessage("beat"));   // 平均値10分のポアソン分布に基づき，患者を発生させるメッセージを自身に向けて発信
}

void Create::handleMessage(cMessage *msg)
{
    send(new cMessage("patient"), "out");               // 患者を表すメッセージを待ち行列に向けて発信
    scheduleAt(simTime() + par("intervalTime"), msg);   // 次の患者を発生させるメッセージを自身に向けて発信
}
