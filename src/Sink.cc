#include "Sink.h"
Define_Module(Sink);

void Sink::initialize()
{
    onWorking = false;  // 現在は空いている
}

void Sink::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        onWorking = false;
        send(new cMessage("call"), "out");                      // 患者の処置が終わったので，次の患者を呼び出す
        leadTime.collect(simTime() - msg->getCreationTime());   // リードタイムを記録
        delete msg;                                             // 患者メッセージを削除
    } else {
        if (strcmp(msg->getName(), "patient") == 0) {
            onWorking = true;                                   // 診察中
            scheduleAt(simTime() + par("intervalTime"), msg);   // 診療時間は平均値8分のポアソン分布に従う
        } else if (strcmp(msg->getName(), "request") == 0) {
            cMessage *callmsg = new cMessage("call");   // 呼び出しメッセージを作成
            callmsg->setKind(msg->getKind());           // ドクター番号をセット
            delete msg;
            if (!onWorking) send(callmsg, "out");   // 空いていれば次の患者を呼び出す
        }
    }
}

void Sink::finish()
{
    EV << "Total jobs Count:              " << leadTime.getCount() << endl;
    EV << "Total jobs Min leadtime:       " << leadTime.getMin() << endl;
    EV << "Total jobs Mean leadtime:      " << leadTime.getMean() << endl;
    EV << "Total jobs Max leadtime:       " << leadTime.getMax() << endl;
    EV << "Total jobs Standard deviation: " << leadTime.getStddev() << endl;

    leadTime.recordAs("lead time");
}
