#include <iostream>
#include <utility>
#include <QBrush>
#include <QColor>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Exceptions.h"
#include "PH.h"
#include "PHScene.h"
#include <map>
#include <QDebug>

PHScene::PHScene(PH* _ph) : ph(_ph) {
    // set background color
    setBackgroundBrush(QBrush(QColor(255, 255, 255)));
}


void PHScene::drawFromSkeleton(void){
	GVSkeletonGraphPtr gSkeleton = ph->createSkeletonGraph();
	
	QList<GVNode> gSkeletonNodes = gSkeleton->nodes();
	for(GVNode &gn : gSkeletonNodes){
		for(SortPtr &s : ph->getSorts()){
			int nbProcess = (s->getProcesses()).size();
			int width = GProcess::sizeDefault+2*GSort::marginDefault;
			int height = nbProcess*(GProcess::sizeDefault+2*GSort::marginDefault);
			if(gn.name == makeSkeletonNodeName(s->getName())){
                sorts.insert(GSortEntry(s->getName(), make_shared<GSort>(s,gn,width,height)));
			}
		}	
	}
	// Clear the scene and add sorts item (containing also processes) to the scene
	clear();
    for (auto &s : sorts){
        addItem(s.second.get());
	}

    createActions();

	for (auto &a : actions){
		addItem(a->getDisplayItem());
	}
}


// retrieve GSort by its related Sort's name
GSortPtr PHScene::getGSort (const string& s) {
    map<string, GSortPtr>::iterator f = sorts.find(s);
    if (f == sorts.end())
        throw sort_not_found() << sort_info(s);
	return sorts[s];
}

// get all the GSort
map<string, GSortPtr> PHScene::getGSorts(){
    return this->sorts;
}

std::vector<GProcessPtr> PHScene::getProcesses(){
    return processes;
}

std::vector<GActionPtr> PHScene::getActions(){
    return actions;
}

void PHScene::updateActions(){
    for(auto &a: actions){
        a->update();
    }
}

void PHScene::createActions() {
    // create GAction items
    for (ActionPtr &a : ph->getActions()) {
    	actions.push_back(make_shared<GAction>(a,this));
    }
}

void PHScene::setSimpleDisplay(bool onOff){
     for(auto &s : sorts){
          s.second->setSimpleDisplay(onOff);
     }
     updateActions();
}

