#include "transition.h"

Transition::Transition(boost::shared_ptr<Process> esrc, boost::shared_ptr<Process> edst):
    src(esrc), dst(edst)
{

}

Transition::~Transition()
{

}

std::vector<ActionPtr> Transition::getActions()
{

}

boost::shared_ptr<Process> Transition::getSource()
{
    return src;
}

boost::shared_ptr<Process> Transition::getTarget()
{
    return dst;
}
