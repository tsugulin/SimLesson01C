#ifndef QUEUE_H_
#define QUEUE_H_

#include <omnetpp.h>
using namespace omnetpp;

class Queue : public cSimpleModule
{
  private:
    int max;    // 次ノード分岐数
    cQueue queue;
    cLongHistogram waitTime;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif /* QUEUE_H_ */
