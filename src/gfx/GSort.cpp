#include <iostream>
#include <QPen>
#include <QColor>
#include <QBrush>
#include <QTextDocument>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QDebug>
#include <QApplication>
#include <QMenu>
#include <QPoint>
#include <QSize>
#include <cmath>
#include <QtGui>
#include "GSort.h"


const int GSort::marginDefault = 10;
const int GSort::defaultDistance = 25;

GSort::GSort(SortPtr s, GVNode n, qreal width, qreal height, PHScene* sc) : QGraphicsRectItem(n.centerPos.x()-width/2, n.centerPos.y()-height/2, width, height),sort(s), node(n),scene(sc) {

	initInnerAttributes();

	initGeometricAttributes(QSize(width, height));

	initRectItem();

	initTextItem();

    	setCursor(QCursor(Qt::OpenHandCursor));
    	setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);

	initGProcessChildren();

}

GSort::~GSort() {
	gProcesses.clear();
	delete _rect;
	delete leftTopCorner;
	delete sizeRect;
	delete text;   
}

void GSort::initInnerAttributes(){
	color = makeColor();
	vertical = true;
    simpleDisplay = false;
	isRightButtonPressed = false;
}

void GSort::initGeometricAttributes(QSize size){
	sizeRect = new QSize(size.width(), size.height());
	leftTopCorner = new QPointF(node.centerPos.x()-sizeRect->width()/2,node.centerPos.y()-sizeRect->height()/2);
}

void GSort::initRectItem(){
	_rect = new QGraphicsRectItem(QRectF(*leftTopCorner, *sizeRect),this);
    _rect->setPen(QPen(QColor(0,0,0)));
    _rect->setBrush(QBrush(QColor(255,255,255)));
    bold=false;
}

void GSort::initTextItem(){
	text = new QGraphicsTextItem (QString(), this);
	text->setHtml(QString::fromStdString("<u><b><h1> " + sort->getName() + "</h1></b></u>"));
	text->setDefaultTextColor(*color);
	text->setPos(leftTopCorner->x()+sizeRect->width()/2, leftTopCorner->y());
	QSizeF textSize = text->document()->size();
	text->setPos(text->x() - textSize.width()/2, text->y() - textSize.height());
}

void GSort::initGProcessChildren(){
    vector<ProcessPtr> processes = sort->getProcesses();
    int currPosYProcess = marginDefault+GProcess::sizeDefault/2;

    for(ProcessPtr &p : processes){
	gProcesses.push_back(make_shared<GProcess>(p,leftTopCorner->x() + GProcess::sizeDefault/2+ marginDefault, leftTopCorner->y()+ currPosYProcess));
	currPosYProcess+= 2*marginDefault + GProcess::sizeDefault;
    }

    for(GProcessPtr &gp: gProcesses){
	gp->getDisplayItem()->setParentItem(this);
	ProcessPtr* p = gp->getProcess();
	(*p)->setGProcess(gp);
    }
}

// mouse press event handler: start "drag"
void GSort::mousePressEvent(QGraphicsSceneMouseEvent *event) {

    QPen pen;
    pen.setWidth(5);
    pen.setBrush(Qt::yellow);
    _rect->setPen(pen);

    bool test=true;
    // change orientation on right click
    if (event->button() == Qt::RightButton) {
        QMenu menu;

         QMenu* editSort = menu.addMenu("Edit sort");
         QAction* switchOrientation = editSort->addAction("Switch horizontal/vertical");
         QAction* switchDisplay = editSort->addAction("Switch to detailled/simple display");
         QAction* switchSortBold=editSort->addAction("Switch sort to bold/not bold ");
         QAction* switchSortColor=editSort->addAction("Switch sort color ");
         QAction* hideSort=editSort->addAction("Hide sort ");

         QMenu* editAction = menu.addMenu("Edit action");
         QMenu* switchActionsIn=editAction->addMenu("Switch in actions ");
         QMenu* switchActionsOut=editAction->addMenu("Switch out actions ");
         QAction* switchActionsInBold=switchActionsIn->addAction("Switch Actions in to bold/not bold ");
         QAction* switchActionsInColor=switchActionsIn->addAction("Switch Action in color ");
         QAction* switchActionsOutBold=switchActionsOut->addAction("Switch Action out to bold/not bold ");
         QAction* switchActionsOutColor=switchActionsOut->addAction("Switch Action out color ");

         QMenu* editProcess=menu.addMenu("Edit process");
         QAction* switchProcessBold=editProcess->addAction("Switch Process to bold/not bold ");
         QAction* switchProcessColor=editProcess->addAction("Switch Process color ");
         QAction* switchProcesBordersColor=editProcess->addAction("Switch Process border color ");

         QAction* selectedAction = menu.exec(QCursor::pos());

         if(selectedAction != 0){
             if(QString::compare(selectedAction->text(),switchOrientation->text())==0){
                 changeOrientation();
                 event->accept();
             }else if(QString::compare(selectedAction->text(),switchDisplay->text())==0){
                 changeDisplayState();
                 event->accept();
             }else if(QString::compare(selectedAction->text(),switchSortColor->text())==0){
                 changeColor();
                 event->accept();
             }
             else if(QString::compare(selectedAction->text(),switchSortBold->text())==0){
                 toBold();
                 test=false;
                 event->accept();
             }
             else if(QString::compare(selectedAction->text(),switchActionsInBold->text())==0){
                 ActionsInToBold();
                 event->accept();
             }
             else if(QString::compare(selectedAction->text(),switchActionsInColor->text())==0){
                 ActionsInChangeColor();
                 event->accept();
             }
             else if(QString::compare(selectedAction->text(),switchActionsOutBold->text())==0){
                 ActionsOutToBold();
                 event->accept();
             }
             else if(QString::compare(selectedAction->text(),switchActionsOutColor->text())==0){
                 ActionsOutChangeColor();
                 event->accept();
             }
             else if(QString::compare(selectedAction->text(),switchProcessBold->text())==0){
                 processChangeBold();
                 event->accept();
             }
         else if(QString::compare(selectedAction->text(),switchProcessColor->text())==0){
                 processChangeColor();
                 event->accept();
             }
         else if(QString::compare(selectedAction->text(),hideSort->text())==0){
                 this->actionsHide();
                 event->accept();
             }
         else if(QString::compare(selectedAction->text(),switchProcesBordersColor->text())==0){
                 processChangeBorderColor();
                 event->accept();
             }
             if(test){
                 QPen pen;
                 pen.setWidth(1);
                 pen.setBrush(Qt::black);
                 _rect->setPen(pen);
             }
         }
    }else if (event->button() == Qt::LeftButton) {
    setCursor(QCursor(Qt::ClosedHandCursor));
    // record coordinates for drawing item when mouse is moved/released
        initPosPoint.setX(pos().x());
        initPosPoint.setY(pos().y());
        eventPressPoint.setX(event->scenePos().x());
        eventPressPoint.setY(event->scenePos().y());
        event->accept();
    }
}

// mouse move event handler: process "drag"
void GSort::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

    QPen pen;
    pen.setWidth(5);
    pen.setBrush(Qt::yellow);
    _rect->setPen(pen);
    QPointF eventScenePos(event->scenePos());

    if (isRightButtonPressed) {
        event->ignore();
        return;
    }

    // update item position
    
    QPointF shiftPoint = eventScenePos-eventPressPoint;
    shiftPosition(shiftPoint);

    eventPressPoint.setX(event->scenePos().x());
    eventPressPoint.setY(event->scenePos().y());

    event->accept();

}

void GSort::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {

    if (event->button() == Qt::RightButton) {
        isRightButtonPressed=false;
    }

    setCursor(QCursor(Qt::OpenHandCursor));

    if(isOverAnotherGSort()){
	cancelShift();
    }

    event->accept();
    QPen pen;
    if(bold)
        pen.setWidth(5);
    else
        pen.setWidth(1);
    pen.setBrush(Qt::black);
    _rect->setPen(pen);
}

void GSort::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    changeDisplayState();
    event->accept();
}

// getters
vector <GProcessPtr> GSort:: getGProcesses(){ return this->gProcesses;}

QGraphicsRectItem* GSort::getRect() { return this->_rect; }

SortPtr GSort::getSort() { return this->sort; }

GVNode GSort::getNode() { return this->node; }

QGraphicsTextItem* GSort::getText() { return this->text; }

QPoint GSort::geteventPressPoint() { return this->eventPressPoint; }

QPointF* GSort::getLeftTopCornerPoint() {return this->leftTopCorner;}

QPointF GSort::getCenterPoint() {
	return QPoint(leftTopCorner->x()+sizeRect->width()/2.0,leftTopCorner->y()+sizeRect->height()/2.0);
}

QSize* GSort::getSizeRect() { return this->sizeRect;}

bool GSort::getSimpleDisplay(){ return this->simpleDisplay; }


void GSort::setSimpleDisplay(bool isSimpleDisplay){
    if(this->simpleDisplay != isSimpleDisplay){
        this->changeDisplayState();
    }
}

void GSort::changeDisplayState(){

    if(simpleDisplay){
    	simpleDisplay = false;
        _rect->setBrush(QBrush(QColor(255,255,255)));
    }else{
	simpleDisplay = true;
    _rect->setBrush(QBrush(QColor(255,190,190)));
    }
    scene->updateActions();
}

void GSort::shiftPosition(QPointF shiftVector) {

    for(GProcessPtr &p: gProcesses){
	    qreal prevPosX = p->getCenterPoint()->x();
	    qreal prevPosY = p->getCenterPoint()->y();
	    p->getCenterPoint()->setX(prevPosX + shiftVector.x());
	    p->getCenterPoint()->setY(prevPosY + shiftVector.y());
    }

    leftTopCorner->setX(leftTopCorner->x() + shiftVector.x());
    leftTopCorner->setY(leftTopCorner->y() + shiftVector.y());

    setPos(x() + shiftVector.x(), y() + shiftVector.y() );

    scene->updateActions();
}

void GSort::cancelShift(){
    shiftPosition(initPosPoint - pos());
}

bool GSort::isOverAnotherGSort(){
    map<string, GSortPtr> listGSorts =scene->getGSorts();
    bool resetPosition = false;

    for(auto &s : listGSorts){
       if(s.second.get()->getSort()->getName()!=sort->getName()){
	   if(isOver(s.second.get())){
		resetPosition = true;
	   }
        }
    }

    return resetPosition;
}

bool GSort::isOver(GSort* otherGSort){
	QPointF centerSortMoving(getCenterPoint());
	QPointF centerSortAround(otherGSort->getCenterPoint());
	qreal distanceWidthMin = getSizeRect()->width()/2 + otherGSort->getSizeRect()->width()/2 +defaultDistance;
	qreal distanceHeightMin = getSizeRect()->height()/2 + otherGSort->getSizeRect()->height()/2 +defaultDistance;

	bool xCond = abs(centerSortMoving.x()-centerSortAround.x())<distanceWidthMin;
	bool yCond = abs(centerSortMoving.y()-centerSortAround.y())<distanceHeightMin;

	return xCond && yCond;
}

void GSort::changeOrientation(){
	changeOrientationRect();
	changeOrientationGProcess();
    scene->updateActions();
}

void GSort::changeColor(){
    // open a color dialog and get the color chosen
    QColor color = QColorDialog::getColor();

    if (!color.isValid()) {
        return ;
    } else {
            // for all the current GSort set the brush
            this->getRect()->setBrush(QBrush(QColor(color)));
    }

}

void GSort::changeOrientationRect(){
    qreal topLeftX=0;
    qreal topLeftY=0;
    qreal bottomRightX=0;
    qreal bottomRightY=0;
    _rect->rect().getCoords(&topLeftX,&topLeftY,&bottomRightX,&bottomRightY);
  
    //Swap Height and Width

    QSizeF oldSize(*sizeRect);
    sizeRect->transpose();


    leftTopCorner->setX(leftTopCorner->x() + (oldSize.width() - sizeRect->width())/2.0);
    leftTopCorner->setY(leftTopCorner->y() + (oldSize.height() - sizeRect->height())/2.0);

    QPoint sceneLeftTopCorner(topLeftX + (oldSize.width() - sizeRect->width())/2.0, topLeftY + (oldSize.height() - sizeRect->height())/2.0);

    _rect->setRect(QRectF(sceneLeftTopCorner, *sizeRect));
    setRect(_rect->rect());

    _rect->rect().getCoords(&topLeftX,&topLeftY,&bottomRightX,&bottomRightY);


    text->setPos(topLeftX+sizeRect->width()/2, topLeftY);
    QSizeF textSize = text->document()->size();
    text->setPos(text->x() - textSize.width()/2, text->y() - textSize.height());

}

void GSort::changeOrientationGProcess(){
    qreal topLeftX=0;
    qreal topLeftY=0;
    qreal bottomRightX=0;
    qreal bottomRightY=0;
    _rect->rect().getCoords(&topLeftX,&topLeftY,&bottomRightX,&bottomRightY);

    if(vertical){
        vertical = false;

        int currPosXProcess = marginDefault+GProcess::sizeDefault/2;
        int currCenterX = 0;
        int currCenterY = 0;

        for(GProcessPtr &p: gProcesses){
            p->getCenterPoint()->setX(leftTopCorner->x() + currPosXProcess);
            p->getCenterPoint()->setY(leftTopCorner->y()+ GProcess::sizeDefault/2+ marginDefault);

            currCenterX = topLeftX +  currPosXProcess;
            currCenterY = topLeftY + GProcess::sizeDefault/2 + marginDefault;

            p->getMarginRect()->setPos(currCenterX -p->getSizeEllipse()->width()/2,currCenterY-p->getSizeEllipse()->height()/2);

            p->getEllipseItem()->setRect(currCenterX -p->getSizeEllipse()->width()/2,currCenterY -p->getSizeEllipse()->height()/2, p->getSizeEllipse()->width(), p->getSizeEllipse()->height());
            QSizeF textSize = p->getText()->document()->size();
            p->getText()->setPos(currCenterX - textSize.width()/2,currCenterY- textSize.height()/2);

            currPosXProcess+= 2*marginDefault + GProcess::sizeDefault;
        }

    }
    else{
        vertical=true;
        int currPosYProcess = marginDefault+GProcess::sizeDefault/2;
	int currCenterX = 0;
        int currCenterY = 0;

        for(GProcessPtr &p: gProcesses){
            p->getCenterPoint()->setX(leftTopCorner->x() + GProcess::sizeDefault/2+ marginDefault);
            p->getCenterPoint()->setY(leftTopCorner->y()+ currPosYProcess);

	    currCenterX = topLeftX + GProcess::sizeDefault/2 + marginDefault;
            currCenterY = topLeftY +  currPosYProcess;

            p->getMarginRect()->setPos(currCenterX -p->getSizeEllipse()->width()/2,currCenterY-p->getSizeEllipse()->height()/2);
            p->getEllipseItem()->setRect(currCenterX -p->getSizeEllipse()->width()/2,currCenterY -p->getSizeEllipse()->height()/2, p->getSizeEllipse()->width(), p->getSizeEllipse()->height());
            QSizeF textSize = p->getText()->document()->size();
            p->getText()->setPos(currCenterX - textSize.width()/2,currCenterY- textSize.height()/2);
            currPosYProcess+= 2*marginDefault + GProcess::sizeDefault;
        }
    }
}

void GSort::actionsHide(){

    this->hide();
    std::string n = this->getSort()->getName();
    std::vector<GActionPtr> allActions=scene->getActions();

    for (GActionPtr &a: allActions){
            if (a->getAction()->getSource()->getSort()->getName() == n || a->getAction()->getTarget()->getSort()->getName() == n || a->getAction()->getResult()->getSort()->getName() == n){
            a->getDisplayItem()->hide();
        }
    }
  }

void GSort::actionsShow(){

    this->show();
    std::string n = this->getSort()->getName();
   // std::vector<GActionPtr> allActions = dynamic_cast<PHScene*>(scene())->getActions();
    std::vector<GActionPtr> allActions =scene->getActions();
    for (GActionPtr &a: allActions){
            if (!(a->getAction()->getSource()->getSort()->getName() == n || a->getAction()->getTarget()->getSort()->getName() == n || a->getAction()->getResult()->getSort()->getName() == n)){
            a->getDisplayItem()->show();
        }
    }
  }

void GSort::hide() {
    this->setOpacity(0);
}

//Make this sort to or not on bold
void GSort::toBold() {
        QPen pen;
    if(this->isBold()){
        pen.setWidth(1);
        pen.setBrush(Qt::black);
        _rect->setPen(pen);
        bold=false;
    }
    else{
        pen.setWidth(5);
        pen.setBrush(Qt::black);
        _rect->setPen(pen);
        bold=true;
    }
}

void GSort::show() {
    this->setOpacity(1);
}

bool GSort::isVisible() {
    return (this->opacity() == 1);
}

bool GSort::isVertical(){
    return vertical;
}

bool GSort::isBold(){
    return bold;
}

void GSort::ActionsInToBold(){

   std::vector<GActionPtr> allActions = scene->getActions();
     for (GActionPtr &a: allActions){
        if ( a->getAction()->getTarget()->getSort()->getName() == this->getSort()->getName() || a->getAction()->getResult()->getSort()->getName() == this->getSort()->getName()){
         //  if (a->getAction()->getSource()->getSort()->getName() == this->getSort()->getName()){
            a->toBold();
        }
    }
}


void GSort::ActionsInChangeColor(){

    // open a color dialog and get the color chosen
    QColor actionsColor = QColorDialog::getColor();
   std::vector<GActionPtr> allActions =scene->getActions();
    if (!actionsColor.isValid()) {
        return ;
    } else {
     for (GActionPtr &a: allActions){
         if ( a->getAction()->getTarget()->getSort()->getName() == this->getSort()->getName() || a->getAction()->getResult()->getSort()->getName() == this->getSort()->getName()){
            a->colorAction(actionsColor);
        }
    }
    }
}

void GSort::ActionsOutToBold(){

   std::vector<GActionPtr> allActions = scene->getActions();
     for (GActionPtr &a: allActions){
           if (a->getAction()->getSource()->getSort()->getName() == this->getSort()->getName()){
            a->toBold();
        }
    }
}


void GSort::ActionsOutChangeColor(){

    // open a color dialog and get the color chosen
    QColor actionsColor = QColorDialog::getColor();
   std::vector<GActionPtr> allActions =scene->getActions();
    if (!actionsColor.isValid()) {
        return ;
    } else {
     for (GActionPtr &a: allActions){
         if (a->getAction()->getSource()->getSort()->getName() == this->getSort()->getName()){
            a->colorAction(actionsColor);
        }
     }
    }
}

void GSort::processChangeBold(){

     for (GProcessPtr &p: gProcesses){
         p->toBold();
    }
}

void GSort::processChangeColor(){

    // open a color dialog and get the color chosen
    QColor processColor = QColorDialog::getColor();

    if (!processColor.isValid()) {
        return ;
    } else {
     for (GProcessPtr &p: gProcesses){
         p->colorProcess(processColor);
     }
    }
}

void GSort::processChangeBorderColor(){
    // open a color dialog and get the color chosen
    QColor actionsColor = QColorDialog::getColor();

    if (!actionsColor.isValid()) {
        return ;
    } else {
     for (GProcessPtr &p: gProcesses){
            p->colorProcessBorder(actionsColor);
     }
    }
}

// palette managementsizeRect

int GSort::paletteIndex = 0;

// TODO see QPalette class?
std::vector<QColor> GSort::palette = 	{	QColor(181,137,0)
										, 	QColor(220,50,47)
										, 	QColor(211,54,130)
										, 	QColor(108,113,196)
										, 	QColor(38,139,210)
										, 	QColor(42,161,152)
										, 	QColor(133,153,0)
										};

QColor* GSort::makeColor () {
	paletteIndex = (paletteIndex + 1) % palette.size();
	return &(palette[paletteIndex]);
}
