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
#include <QApplication>
#include <QMenu>
#include <QtGui>

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
                sorts.insert(GSortEntry(s->getName(), make_shared<GSort>(s,gn,width,height,this)));
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

// context menu event handler
void PHScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {

    QPointF sorEventPressPoint;
    bool horsSorte=true;

    // if other mouse buttons are pressed, do nothing
    if (QApplication::mouseButtons() == Qt::RightButton) {
        for(auto &s : sorts){
            sorEventPressPoint = s.second.get()->geteventPressPoint();
            if(sorEventPressPoint.x() == event->scenePos().x() && sorEventPressPoint.y() == event->scenePos().y()){
                horsSorte=false;
            }
        }
        if(horsSorte){

    QMenu menu;
    QAction* switchToSimplifiedModel = menu.addAction("switch to simplified model");
    QAction* switchToDetailledModel = menu.addAction("switch to detailled model");
    QAction* switchBackgroundColor = menu.addAction("color background ");
    QAction* switchActionsInBold = menu.addAction("all actions in bold/ not to blod");
    QAction* switchActionColor = menu.addAction("color all actions");

    QAction* selectedAction = menu.exec(QCursor::pos());
    if(selectedAction != 0){
        if(QString::compare(selectedAction->text(),switchBackgroundColor->text())==0){
            BackgroundColor();
        }else if(QString::compare(selectedAction->text(),switchActionsInBold->text())==0){
            ActionsInBold();
        }else if(QString::compare(selectedAction->text(),switchActionColor->text())==0){
            ActionColor();
        }else if(QString::compare(selectedAction->text(),switchToSimplifiedModel->text())==0){
            setSimpleDisplay(true);
        }else if(QString::compare(selectedAction->text(),switchToDetailledModel->text())==0){
            setSimpleDisplay(false);
        }

    }
        }
    }
}

void PHScene::BackgroundColor(){
    // open a color dialog and get the color chosen
    QColor color = QColorDialog::getColor();

    if(!color.isValid()){
       return ;
    } else {
       this->setBackgroundBrush(color);
   }

}

void PHScene::ActionsInBold(){
//    GActionPtr actionToChange;
//    bool test=true;
//    int minx;
//    int miny;
//    int min;
    for(auto &a :this->getActions()){
        a->toBold();
//      QPointF* ptSource = a->getSource()->getCenterPoint();
//       QPointF* ptTarget = a->getTarget()->getCenterPoint();
//       QPointF* ptResult = a->getResult()->getCenterPoint();
//       if(test){
//          actionToChange=a;
//          minx=ptSource->x() - pressPoint.x();
//          miny=ptSource->y() - pressPoint.y();
//          min=minx*minx + miny*miny;
//          std::cout << "Min x=" << ptSource->x()<< "y=" << ptSource->y()<< std::endl;
//          test=false;
//       }else{
//           if(min > (ptSource->x()*ptSource->x() + ptSource->y()*ptSource->y())- (pressPoint.x()*pressPoint.x() + pressPoint.y()*pressPoint.y())){
//               min = (ptSource->x()*ptSource->x() + ptSource->y()*ptSource->y())- (pressPoint.x()*pressPoint.x() + pressPoint.y()*pressPoint.y());
//               actionToChange=a;
//               std::cout << "x=" << ptSource->x()<< "y=" << ptSource->y()<< std::endl;
//           }
//       }
   }
//    actionToChange->toBold();
}

void PHScene::ActionColor(){

    // open a color dialog and get the color chosen
    QColor actionsColor = QColorDialog::getColor();
    if (!actionsColor.isValid()) {
        return ;
    } else {
     for (GActionPtr &a: this->getActions()){
            a->colorAction(actionsColor);
    }
    }
}


