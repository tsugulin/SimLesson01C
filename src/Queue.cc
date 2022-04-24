#include "Queue.h"
Define_Module(Queue);

void Queue::initialize()
{
   queue.setName("queue");              // 待ち行列に名前をつける
   max = par("forkNumber").intValue();  // 分岐数
   nxt = 0;                             // 医師の待ち状況を初期化
   WATCH(nxt);                          // 各医師の診療状況を監視
}

void Queue::handleMessage(cMessage *msg)
{
    if (strcmp(msg->getName(), "patient") == 0) {
        // 患者が到着
        msg->setTimestamp(simTime());   // リードタイムの開始時間をセット
        queue.insert(msg);              // 待ち行列にメッセージを保管
        int j = 0;
        if (nxt < 3) {
            if (nxt == 0)  j = intuniform(0, max-1);    // どらかも空いている場合は乱数にて送信先を決定
            else           j = (nxt == 1) ? 1: 0;       // 医師1が診療中ならば医師2、医師2が診療中ならば医師1をアサイン、
            forward(j);     // 患者を医師に送る
        }
    } else if (strcmp(msg->getName(), "call") == 0) {
        // 医師からの呼び出し
        int j = (strcmp(msg->getArrivalGate()->getFullName(), "in[1]") == 0) ? 0: 1;   // in[1]は医師0、in[2]は医師1
        nxt ^= j + 1;   // 医師の待ち状況を更新
        forward(j);     // 医師を呼び出し
        delete msg;     // 呼び出しメッセージを削除
    }
}

//　患者を待合室から医師へ
void Queue::forward(int doctor)
{
    if (queue.getLength() > 0) {        // もし患者が待っていれば
        cMessage *patient = check_and_cast<cMessage *>(queue.pop());    // 待ち行列からメッセージを取り出す
        waitTime.collect(simTime() - patient->getTimestamp());          // 待ち時間をカウント
        send(patient, "out", doctor);   // 患者をドクターへ
        nxt ^= doctor + 1;              // 医師の待ち状況を更新
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
