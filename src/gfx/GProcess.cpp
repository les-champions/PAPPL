#include <iostream>
#include <QPen>
#include <QColor>
#include <QBrush>
#include <QSizeF>
#include <QTextDocument>
#include <Qt>
#include "GProcess.h"
#include <math.h>


const int GProcess::marginZone  = 10;
const int GProcess::sortName    = 11;
const int GProcess::sizeDefault = 100;

GProcess::GProcess(ProcessPtr p,double centerX, double centerY) : process(p){

	display = new QGraphicsItemGroup();

	initGeometricsValues(QPointF(centerX,centerY), sizeDefault);

	initEllipseItem();

	initMarginRectItem();
    
	initTextItem();
}


GProcess::~GProcess() {
    delete text;
    delete ellipse;
    delete center;
    delete size;
    delete display;
}

// Init methods

void GProcess::initGeometricsValues(QPointF centerPoint, double diameter){
	center = new QPointF(centerPoint);	
	size = new QSizeF(diameter,diameter);
}

void GProcess::initEllipseItem(){
    	ellipse = new QGraphicsEllipseItem (center->x()-sizeDefault/2, center->y()-sizeDefault/2,
                                        size->width(), size->height(), display);
	ellipse->setPen(QPen(QColor(0,0,0)));
	ellipse->setBrush(QBrush(QColor(255,255,255)));
    bold=false;
    numberProcessColor=0;
}

void GProcess::initMarginRectItem(){
	int margin(GSort::marginDefault);

	marginRect = new QGraphicsRectItem(
                center->x() - margin/2,
                center->y() - margin/2,
                2*margin,
                2*margin,
                display);
                
	marginRect->setBrush(Qt::NoBrush);
	marginRect->setPen(Qt::NoPen);
	marginRect->setData(marginZone, true);
	marginRect->setData(sortName, process->getSort()->getName().c_str());
}

void GProcess::initTextItem(){
	text = new QGraphicsTextItem (QString("%1").arg(process->getNumber()), ellipse);
	text->setFont(QFont("TypeWriter",25));
	text->setDefaultTextColor(QColor(7,54,66));
	text->setPos(center->x(), center->y());

	QSizeF textSize = text->document()->size();
	text->setPos(text->x() - textSize.width()/2, text->y() - textSize.height()/2);
    actifState=false;
}

//Colorer le process
void GProcess::colorProcess(QColor color){
    if (!color.isValid()) {
        return ;
    } else {
        QPen pen;
        if(this->isBold())
            pen.setWidth(4);
        else
            pen.setWidth(2);
        ellipse->setBrush(QBrush(QColor(color)));
    }
}

//Colorer la bordure du process
void GProcess::colorProcessBorder(QColor color){
    if (!color.isValid()) {
        return ;
    } else {
        QPen pen;
        pen.setWidth(5);
        pen.setBrush(QBrush(QColor(color)));
        ellipse->setPen(pen);
    }
}

//Verify if this action is in bold
bool GProcess::isBold(){
    return bold;
}

//make on bold this Process
void GProcess::toBold() {
    QPen pen;
    if(this->isBold()){
        pen.setWidth(1);
        pen.setBrush(Qt::black);
        ellipse->setPen(pen);
        bold=false;
    }
    else{
        pen.setWidth(4);
        pen.setBrush(Qt::black);
        ellipse->setPen(pen);
        bold=true;
    }
}

//make the process in grey color
void GProcess::beActifProcess(int r, int g, int b){
    this->setProcessActifState(true);
    ellipse->setBrush(QBrush(QColor(r,g,b)));
}

//make the process in normal color
void GProcess::beNonActifProcess(){
    this->setProcessActifState(false);
    ellipse->setBrush(QBrush(QColor(255,255,255)));
}

//change the process state actif ou not actif
void GProcess::setProcessActifState(bool state){
    this->actifState=state;
}

//Change the number of process color
void GProcess::setProcessColorNumber(int nb){
    this->numberProcessColor=nb;
}

// Getters

ProcessPtr* GProcess::getProcess() { return &(this->process); }

ProcessPtr GProcess::getProcessPtr() { return this->process;}

QGraphicsItem* GProcess::getDisplayItem (void) { return display; }

QGraphicsEllipseItem* GProcess::getEllipseItem(){ return ellipse; }

QGraphicsRectItem* GProcess::getMarginRect() { return this->marginRect; }

QPointF* GProcess::getCenterPoint() {return this->center;}

QSizeF* GProcess::getSizeEllipse() {return this->size;}

QGraphicsTextItem* GProcess::getText() {return this->text;}

bool GProcess::getProcessActifState(){return this->actifState;}

int GProcess::getProcessColorNumber(){return this->numberProcessColor;}

// Setters

void GProcess::setCoordsForImport(int x, int y) {
    center->setX(x);
    center->setY(y);
}
