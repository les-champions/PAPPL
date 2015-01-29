#include <boost/algorithm/string/join.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include "Exceptions.h"
#include "PH.h"
#include "MainWindow.h"
#include <GVSkeletonGraph.h>
#include <QDebug>


#define DEFAULT_INFINITE_DEFAULT_RATE true
#define DEFAULT_RATE 0.
#define DEFAULT_STOCHASTICITY_ABSORPTION 1


PH::PH () {
    scene = boost::shared_ptr<PHScene>();

    // set defaults
    infinite_default_rate 		= DEFAULT_INFINITE_DEFAULT_RATE;
    default_rate 				= DEFAULT_RATE;
    stochasticity_absorption 	= DEFAULT_STOCHASTICITY_ABSORPTION;
}


// trigger the rendering in the Scene
void PH::render () {
    if (scene.use_count() == 0) scene = make_shared<PHScene>(this);
    scene->drawFromSkeleton();
}

// get graphics scene for display
PHScenePtr PH::getGraphicsScene() {
    if (scene.use_count() == 0)	scene = make_shared<PHScene>(this);
    return scene;
}


// control headers
int PH::getStochasticityAbsorption () 			{
    return stochasticity_absorption;
}
void PH::setStochasticityAbsorption (int sa) 	{
    stochasticity_absorption = sa;
    std::cerr << "set " << sa << std::endl;
}
bool PH::getInfiniteDefaultRate () 				{
    return infinite_default_rate;
}
void PH::setInfiniteDefaultRate (bool b) 		{
    infinite_default_rate = b;
}
double PH::getDefaultRate () 		{
    return default_rate;
}
void PH::setDefaultRate (double r) 	{
    default_rate = r;
}


// add data: Sorts and Actions
void PH::addSort (SortPtr s) {
    sorts.insert(SortEntry(s->getName(), s));
}
void PH::addAction (ActionPtr a) {
    actions.push_back(a);
}


// retrieve a Sort by name
SortPtr PH::getSort (const string& s) {
    map<string, SortPtr>::iterator f = sorts.find(s);
    if (f == sorts.end())
        throw sort_not_found() << sort_info(s);
    return sorts[s];
}


// retrieve all Sorts in a std::list
list<SortPtr> PH::getSorts(void) {
    list<SortPtr> res;
    for (auto &s : sorts)
        res.push_back(s.second);
    return res;
}


// retrieve all Processes in a std::list
list<ProcessPtr> PH::getProcesses(void) {
    list<ProcessPtr> res;
    for (auto &s : sorts)
        for (auto &p : s.second->getProcesses())
            res.push_back(p);
    return res;
}


// retrieve the list of Actions
list<ActionPtr> PH::getActions(void) {
    return actions;
}

// build the skeleton graph of the ph model
GVSkeletonGraphPtr PH::createSkeletonGraph(void) {
    GVSkeletonGraphPtr gSkeleton = make_shared<GVSkeletonGraph>(QString("Skeleton Graph"));
    QString sortName;
    vector<ProcessPtr> listProcess;
    int nbProcess;
    for(auto &e : sorts) {
        sortName = makeSkeletonNodeName(e.second->getName());
        listProcess = e.second->getProcesses();
        nbProcess = listProcess.size();
        int height = (nbProcess+1)*(GProcess::sizeDefault+2*GSort::marginDefault);
        int width = height; // modified to get less "vertical" graphs
        gSkeleton->addNode(sortName);
        gSkeleton->setNodeSize(gSkeleton->getNode(sortName),width,height);
        gSkeleton->setGraphObjectAttributes(gSkeleton->getNode(sortName),"fixedsize","true");
    }

    for (ActionPtr &a : actions) {
        QString sourceName = makeSkeletonNodeName(a->getSource()->getSort()->getName());
        QString targetName = makeSkeletonNodeName(a->getTarget()->getSort()->getName());
        if(!gSkeleton->connectionExists(sourceName,targetName)&&(QString::compare(sourceName,targetName)!=0)) {
            gSkeleton->addEdge(sourceName,targetName);
        }
    }
    gSkeleton->applyLayout();


    return gSkeleton;
}

// output for DOT file
string PH::toDotString (void) {

    string res;
    res += "digraph G {\n";
    res += "node [style=filled,color=lightgrey]\n";
    // res += "edge [samehead]\n";

    // output Sorts
    res += "\n\n";
    for (auto &e : sorts)
        res += e.second->toDotString() + "\n";

    // output Actions
    res += "\n\n";
    for (ActionPtr &a : actions)
        res += a->toDotString() + "\n";
    res += "}\n";

    return res;
}


// output for PH file
string PH::toString (void) {

    string res;

    // output headers
    res += "directive default_rate " + (infinite_default_rate ? "Inf" :
                                        (default_rate == (int) default_rate) ?
                                        boost::lexical_cast<string>(default_rate) + "."
                                        :	boost::lexical_cast<string>(default_rate)
                                       ) + "\n";
    res += "directive stochasticity_absorption " + boost::lexical_cast<string>(stochasticity_absorption) + "\n";

    // output Sorts
    for (auto &e : sorts)
        res += e.second->toString();
    res += "\n";

    // output actions
    for (ActionPtr &a : actions)
        res += a->toString();
    res += "\n";

    // output initial state
    if (!sorts.empty()) {
        res += "initial_state ";
        list<string> l;
        for (auto &e : sorts)
            l.push_back(e.second->getName() + " " + boost::lexical_cast<string>(e.second->getActiveProcess()->getNumber()));
        res += boost::algorithm::join(l, ", ");
    }
    res += "\n";

    return res;
}
