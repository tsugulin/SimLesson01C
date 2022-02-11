#ifndef CREATE_H_
#define CREATE_H_

#include <omnetpp.h>
using namespace omnetpp;

class Create : public cSimpleModule {
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif /* CREATE_H_ */
