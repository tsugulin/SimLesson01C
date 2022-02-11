#ifndef SINK_H_
#define SINK_H_

#include <omnetpp.h>
using namespace omnetpp;

class Sink : public cSimpleModule
{
private:
    bool onWorking;
    bool docNumber;     // ドクター番号
    cLongHistogram leadTime;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void forwardMessage();
    virtual void finish();
};


#endif /* SINK_H_ */
