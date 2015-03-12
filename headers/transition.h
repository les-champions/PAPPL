#ifndef TRANSITION_H
#define TRANSITION_H

#include "PH.h"
#include "Action.h"
#include "Process.h"
#include <list>
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<PH> PHPtr;


class Transition
{
public:
    Transition(boost::shared_ptr<Process> esrc, boost::shared_ptr<Process> edst, PHPtr);
    std::list<ActionPtr> getActions();
    ~Transition();
    boost::shared_ptr<Process> getSource();
    boost::shared_ptr<Process> getTarget();
    void setPh();



private:
    boost::shared_ptr<Process> src;
    boost::shared_ptr<Process> dst;
    PHPtr ph;

};

#endif // TRANSITION_H
