#ifndef SINK_H_
#define SINK_H_

#include <omnetpp.h>
using namespace omnetpp;

class Sink : public cSimpleModule
{
private:
    bool onWorking;
    cLongHistogram leadTime;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};


#endif /* SINK_H_ */
