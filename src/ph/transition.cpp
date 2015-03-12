#include "transition.h"

Transition::Transition(boost::shared_ptr<Process> esrc, boost::shared_ptr<Process> edst, PHPtr phptr):
    src(esrc), dst(edst), ph(phptr)
{
    //phptr->getActions()

}

Transition::~Transition()
{

}

std::vector<ActionPtr> Transition::getActions()
{
    auto act = ph->getActions();
    return [&]()->std::vector<ActionPtr>
    {
        vector<ActionPtr> tAct();
        for(auto &r : act)
        {
            if(r->getSource() == this->getSource() && r->getTarget() == this->getTarget())
                tAct.push_back(r);
            return tAct;
        }
    };
}

boost::shared_ptr<Process> Transition::getSource()
{
    return src;
}

boost::shared_ptr<Process> Transition::getTarget()
{
    return dst;
}

void Transition::setPh()
{

}
