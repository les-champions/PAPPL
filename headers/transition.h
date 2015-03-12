#ifndef TRANSITION_H
#define TRANSITION_H

#include "Action.h"
#include "Process.h"
#include <vector>
#include <boost/shared_ptr.hpp>

class Transition
{
public:
    Transition(boost::shared_ptr<Process> esrc, boost::shared_ptr<Process> edst);
    std::vector<ActionPtr> getActions();
    ~Transition();
    boost::shared_ptr<Process> getSource();
    boost::shared_ptr<Process> getTarget();



private:
    boost::shared_ptr<Process> src;
    boost::shared_ptr<Process> dst;
};

#endif // TRANSITION_H
