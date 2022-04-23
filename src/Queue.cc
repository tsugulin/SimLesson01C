#include "Queue.h"
Define_Module(Queue);

void Queue::initialize()
{
   queue.setName("queue");              // 待ち行列に名前をつける
   max = par("forkNumber").intValue();  // 分岐数
   for (int i = 0; i < max; i++)  nxt[i] = 0;      // 各医師の診療状況をリセット
   WATCH_MAP(nxt);                                 // 各医師の診療状況を監視
}

void Queue::handleMessage(cMessage *msg)
{
    if (strcmp(msg->getName(), "patient") == 0) {
        // 患者が到着
        msg->setTimestamp(simTime());   // リードタイムの開始時間をセット
        queue.insert(msg);              // 待ち行列にメッセージを保管
        int k = intuniform(0, max-1);   // 乱数にて送信先を決定
        cMessage *reqmsg = new cMessage("request");
        reqmsg->setKind(k);             // ドクター番号をセット
        send(reqmsg, "out", k);         // リクエストをドクターへ
    } else if (strcmp(msg->getName(), "call") == 0) {
        // 医師からの呼び出し
        if (queue.getLength() > 0) {       // もし患者が待っていれば
            cMessage *patient = check_and_cast<cMessage *>(queue.pop());    // 待ち行列からメッセージを取り出す
            waitTime.collect(simTime() - patient->getTimestamp());          // 待ち時間をカウント
            send(patient, "out", msg->getKind());   // 患者をドクターへ
        }
        delete msg;     // 呼び出しメッセージを削除
    }
}

//　ノードの統計情報を表示
void Queue::finish()
{
    EV << "Queue Jobs Count:    " << waitTime.getCount() << endl;
    EV << "Queue Min Leadtime:  " << waitTime.getMin() << endl;
    EV << "Queue Mean Leadtime: " << waitTime.getMean() << endl;
    EV << "Queue Max Leadtime:  " << waitTime.getMax() << endl;
    EV << "Standard deviation:  " << waitTime.getStddev() << endl;

    waitTime.recordAs("queue length");
}
