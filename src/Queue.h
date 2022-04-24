#ifndef QUEUE_H_
#define QUEUE_H_

#include <omnetpp.h>
using namespace omnetpp;

class Queue : public cSimpleModule
{
  private:
    int max;    // 分岐数を表す
    int nxt;    // 医師の待ち状況を表す
    cQueue queue;
    cLongHistogram waitTime;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void forward(int);
    virtual void finish();
};

#endif /* QUEUE_H_ */
