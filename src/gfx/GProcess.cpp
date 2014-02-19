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
}

// Getters

ProcessPtr* GProcess::getProcess() { return &(this->process); }

QGraphicsItem* GProcess::getDisplayItem (void) { return display; }

QGraphicsEllipseItem* GProcess::getEllipseItem(){ return ellipse; }

QGraphicsRectItem* GProcess::getMarginRect() { return this->marginRect; }

QPointF* GProcess::getCenterPoint() {return this->center;}

QSizeF* GProcess::getSizeEllipse() {return this->size;}

QGraphicsTextItem* GProcess::getText() {return this->text;}

// Setters

void GProcess::setCoordsForImport(int x, int y) {
    center->setX(x);
    center->setY(y);
}
