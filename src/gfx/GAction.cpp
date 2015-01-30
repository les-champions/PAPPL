#include <iostream>
#include <QMatrix>
#include <QPointF>
#include <QVector>
#include <QColor>
#include <Qt>
#include <QApplication>
#include <QMenu>
#include <QVector2D>
#include "GAction.h"
#include <QtCore/qmath.h>

#include <QPen>
#include <QBrush>
#include <QtGui>


GAction::GAction(ActionPtr a, PHScene* sc) : scene(sc), action(a) {
    display = new QGraphicsItemGroup();

    initContactPoints();

    hitLine= new QGraphicsPathItem(createHitPath(),display);
    if((targetPoint->x()==resultPoint->x())&&(targetPoint->y()==resultPoint->y())) {
        QPen pen;
        pen.setWidth(2);
        pen.setBrush(Qt::red);
        hitLine->setPen(pen);
    } else {
        QPen pen;
        pen.setWidth(1);
        pen.setBrush(Qt::black);
        hitLine->setPen(pen);
    }

    boundArc = new QGraphicsPathItem(createBoundPath(),display);
    boundArc->setPen(QPen(Qt::DashLine));
    numberActionColor=-1;
    this->bold=false;

}

void GAction::update() {

    updateContactPoints();
    QPen pen;

    boundArc->setPath(createBoundPath());
    hitLine->setPath(createHitPath());
    if((targetPoint->x()==resultPoint->x())&&(targetPoint->y()==resultPoint->y())) {
        pen.setWidth(2);
        pen.setBrush(Qt::red);
        hitLine->setPen(pen);
    } else {
        if (this->isBold())
            pen.setWidth(2);
        else
            pen.setWidth(1);
        pen.setBrush(Qt::black);
        hitLine->setPen(pen);
        pen.setStyle(Qt::DashLine);
        boundArc->setPen(pen);
    }
}

GAction::GAction() {
}

// Important for the destructor : do not delete scene, it's owned by a shared pointer in PH.h
GAction::~GAction() {
    delete display;
}

void GAction::initContactPoints() {
    GSortPtr sourceSort = scene->getGSort(action->getSource()->getSort()->getName());
    GSortPtr targetSort = scene->getGSort(action->getTarget()->getSort()->getName());

    if(sourceSort->getSimpleDisplay()!=1||targetSort->getSimpleDisplay()!=1) {
        initPointsInDetailledModel();
    } else {
        initPointsInSimpleModele();
    }
}

void GAction::updateContactPoints() {

    GSortPtr sourceSort = scene->getGSort(action->getSource()->getSort()->getName());
    GSortPtr targetSort = scene->getGSort(action->getTarget()->getSort()->getName());

    if(sourceSort->getSimpleDisplay()!=1||targetSort->getSimpleDisplay()!=1) {
        updatePointsInDetailledModel();
    } else {
        updatePointsInSimpleModel();
    }
}

void GAction::initPointsInSimpleModele() {
    GSortPtr sourceSort = scene->getGSort(action->getSource()->getSort()->getName());
    GSortPtr targetSort = scene->getGSort(action->getTarget()->getSort()->getName());

    sourcePoint = new QPointF(sourceSort->getCenterPoint());
    targetPoint = new QPointF(targetSort->getCenterPoint());
    resultPoint = new QPointF(targetSort->getCenterPoint());

}

void GAction::initPointsInDetailledModel() {
    isAutoHit() ? initPointsAutoHit() : initPointsNormalHit();
}

void GAction::updatePointsInSimpleModel() {

    GSortPtr sourceSort = scene->getGSort(action->getSource()->getSort()->getName());
    GSortPtr targetSort = scene->getGSort(action->getTarget()->getSort()->getName());

    sourcePoint->setX(sourceSort->getCenterPoint().x());
    sourcePoint->setY(sourceSort->getCenterPoint().y());
    targetPoint->setX(targetSort->getCenterPoint().x());
    targetPoint->setY(targetSort->getCenterPoint().y());
    resultPoint->setX(targetSort->getCenterPoint().x());
    resultPoint->setY(targetSort->getCenterPoint().y());

}

void GAction::updatePointsInDetailledModel() {
    isAutoHit() ? updatePointsAutoHit() : updatePointsNormalHit();
}

bool GAction::isAutoHit() {
    GProcessPtr source = getSource();
    GProcessPtr target = getTarget();

    return source==target;
}

void GAction::initPointsNormalHit() {
    GProcessPtr source = getSource();
    GProcessPtr target = getTarget();
    GProcessPtr result = getResult();

    QVector2D* hitVector = new QVector2D(*(target->getCenterPoint()) - *(source->getCenterPoint()));
    hitVector->normalize();

    QSizeF* sizeSource = source->getSizeEllipse();
    QSizeF* sizeTarget = source->getSizeEllipse();


    sourcePoint = new QPointF(sizeSource->width()*hitVector->x()/2.0 + source->getCenterPoint()->x(),sizeSource->height()*hitVector->y()/2 + source->getCenterPoint()->y());

    targetPoint = new QPointF(-sizeTarget->width()*hitVector->x()/2.0 + target->getCenterPoint()->x(),-sizeTarget->height()*hitVector->y()/2 + target->getCenterPoint()->y());

    resultPoint = new QPointF(-sizeTarget->width()*hitVector->x()/2.0 + result->getCenterPoint()->x(),sizeTarget->height()*hitVector->y()/2 + result->getCenterPoint()->y());

}

void GAction::updatePointsNormalHit() {
    GProcessPtr source = getSource();
    GProcessPtr target = getTarget();
    GProcessPtr result = getResult();

    QVector2D* hitVector = new QVector2D(*(target->getCenterPoint()) - *(source->getCenterPoint()));
    hitVector->normalize();

    QSizeF* sizeSource = source->getSizeEllipse();
    QSizeF* sizeTarget = target->getSizeEllipse();

    sourcePoint->setX(sizeSource->width()*hitVector->x()/2.0 + source->getCenterPoint()->x());
    sourcePoint->setY(sizeSource->height()*hitVector->y()/2.0 + source->getCenterPoint()->y());
    targetPoint->setX(-sizeTarget->width()*hitVector->x()/2.0 + target->getCenterPoint()->x());
    targetPoint->setY(-sizeTarget->height()*hitVector->y()/2.0 + target->getCenterPoint()->y());

    if(dynamic_cast<GSort*>(getTarget()->getDisplayItem()->parentItem())->isVertical()) {
        resultPoint->setX(-sizeTarget->width()*hitVector->x()/2.0 + result->getCenterPoint()->x());
        resultPoint->setY(sizeTarget->height()*hitVector->y()/2.0 + result->getCenterPoint()->y());
    } else {
        resultPoint->setX(sizeTarget->width()*hitVector->x()/2.0 + result->getCenterPoint()->x());
        resultPoint->setY(-sizeTarget->height()*hitVector->y()/2.0 + result->getCenterPoint()->y());
    }
}

void GAction::initPointsAutoHit() {
    GProcessPtr source = getSource();
    GProcessPtr target = getTarget();
    GProcessPtr result = getResult();

    if (dynamic_cast<GSort*>(getTarget()->getDisplayItem()->parentItem())->isVertical()) {
        sourcePoint = new QPointF(source->getCenterPoint()->x(), source->getCenterPoint()->y() + (GProcess::sizeDefault)/2.0);
        targetPoint = new QPointF(GProcess::sizeDefault/2.0 + source->getCenterPoint()->x(), source->getCenterPoint()->y());
        resultPoint = new QPointF(GProcess::sizeDefault/2.0 + result->getCenterPoint()->x(),result->getCenterPoint()->y());
    } else {
        sourcePoint = new QPointF(source->getCenterPoint()->x() + (GProcess::sizeDefault)/2.0, source->getCenterPoint()->y());
        targetPoint = new QPointF(source->getCenterPoint()->x(),GProcess::sizeDefault/2.0 + source->getCenterPoint()->y());
        resultPoint = new QPointF(result->getCenterPoint()->x(),GProcess::sizeDefault/2.0 + result->getCenterPoint()->y());
    }

}

void GAction::updatePointsAutoHit() {
    GProcessPtr source = getSource();
    GProcessPtr target = getTarget();
    GProcessPtr result = getResult();

    if(dynamic_cast<GSort*>(getTarget()->getDisplayItem()->parentItem())->isVertical()) {
        sourcePoint->setX(source->getCenterPoint()->x());
        sourcePoint->setY(source->getCenterPoint()->y() + (GProcess::sizeDefault)/2.0);
        targetPoint->setX(GProcess::sizeDefault/2 + source->getCenterPoint()->x());
        targetPoint->setY(source->getCenterPoint()->y());
        resultPoint->setX(GProcess::sizeDefault/2 + result->getCenterPoint()->x());
        resultPoint->setY(result->getCenterPoint()->y());
    } else {
        sourcePoint->setX(source->getCenterPoint()->x() + (GProcess::sizeDefault)/2.0);
        sourcePoint->setY(source->getCenterPoint()->y());
        targetPoint->setX(source->getCenterPoint()->x());
        targetPoint->setY(source->getCenterPoint()->y() + GProcess::sizeDefault/2);
        resultPoint->setX(result->getCenterPoint()->x());
        resultPoint->setY(result->getCenterPoint()->y() + GProcess::sizeDefault/2);
    }
}
bool GAction::isCurvedHit(GSortPtr sourceSort, GSortPtr targetSort, GProcessPtr source, GProcessPtr target) {

    QLineF* hitLineTemp;

    QLineF* sourceSortBottomLine;
    QLineF* sourceSortTopLine;
    QPointF sourceSortBottomLeft = sourceSort->getRect()->rect().bottomLeft();
    QPointF sourceSortBottomRight = sourceSort->getRect()->rect().bottomRight();
    QPointF sourceSortTopLeft = sourceSort->getRect()->rect().topLeft();
    QPointF sourceSortTopRight = sourceSort->getRect()->rect().topRight();

    QLineF* targetSortBottomLine;
    QLineF* targetSortTopLine;
    QPointF targetSortBottomLeft = targetSort->getRect()->rect().bottomLeft();
    QPointF targetSortBottomRight = targetSort->getRect()->rect().bottomRight();
    QPointF targetSortTopLeft = targetSort->getRect()->rect().topLeft();
    QPointF targetSortTopRight = targetSort->getRect()->rect().topRight();

    hitLineTemp = new QLineF(*sourcePoint,*targetPoint);
    sourceSortBottomLine = new QLineF(sourceSortBottomLeft,sourceSortBottomRight);
    sourceSortTopLine= new QLineF(sourceSortTopLeft,sourceSortTopRight);
    const QLineF & refToSourceSortBottomLine = *sourceSortBottomLine ;// built a reference to the QLinef* associate because of the function intersect() used after, which whants only reference and no pointer
    const QLineF & refToSourceSortTopLine = *sourceSortTopLine ;// built a reference to the QLinef* associate because of the function intersect() used after, which whants only reference and no pointer

    targetSortBottomLine = new QLineF(targetSortBottomLeft,targetSortBottomRight);
    targetSortTopLine = new QLineF(targetSortTopLeft,targetSortTopRight);
    const QLineF & refToTargetSortBottomLine = *targetSortBottomLine ;// built a reference to the QLinef* associate because of the function intersect() used after, which whants only reference and no pointer
    const QLineF & refToTargetSortTopLine = *targetSortTopLine ;// built a reference to the QLinef* associate because of the function intersect() used after, which whants only reference and no pointer

    if((hitLineTemp->intersect(refToSourceSortBottomLine, 0) == QLineF::BoundedIntersection &&
        source->getCenterPoint()->y() + GProcess::sizeDefault < sourceSort->getRect()->rect().bottomLeft().y()) ||
        (hitLineTemp->intersect(refToSourceSortTopLine, 0) == QLineF::BoundedIntersection &&
         source->getCenterPoint()->y() - GProcess::sizeDefault > sourceSort->getRect()->rect().topLeft().y())) {
        return true;
    } else if((hitLineTemp->intersect(refToTargetSortBottomLine, 0) == QLineF::BoundedIntersection &&
               target->getCenterPoint()->y() + GProcess::sizeDefault < targetSort->getRect()->rect().bottomLeft().y()) ||
              (hitLineTemp->intersect(refToTargetSortTopLine, 0) == QLineF::BoundedIntersection &&
               target->getCenterPoint()->y() - GProcess::sizeDefault > targetSort->getRect()->rect().topLeft().y())) {
        return true;
    } else {
        return false;
    }
}

// Create actions paths
//Hit Part
QPainterPath GAction::createHitPath() {

    GProcessPtr source = getSource();
    GProcessPtr target = getTarget();
    GProcessPtr result = getResult();
    GSortPtr sourceSort = scene->getGSort(action->getSource()->getSort()->getName());
    GSortPtr targetSort = scene->getGSort(action->getTarget()->getSort()->getName());


    qreal rectCornerX;
    qreal rectCornerY;
    qreal widthRect;
    qreal heightRect;
    qreal sweepAngle;
    qreal startAngle;
    int invertSweep;
    int invertStart;
    int wCoef=1;
    int hCoef=1;

    QPointF* controlPointSource;
    QPointF* controlPointTarget;

    QLineF* hitLineTemp;
    hitLineTemp = new QLineF(*sourcePoint,*targetPoint);

    QPainterPath hitPath(*sourcePoint);

    if(!isAutoHit()) {
        if(isCurvedHit(sourceSort, targetSort, source, target) && (sourceSort->getSimpleDisplay()!=1 || targetSort->getSimpleDisplay()!=1)) {
            if(sourcePoint->x() >= targetPoint->x()) {
                wCoef= -1;
            } else {
                wCoef= 1;
            }
            if(sourcePoint->y() >= targetPoint->y()) {
                hCoef = 1;
            } else {
                hCoef = -1;
            }
            controlPointSource = new QPointF(sourcePoint->x() + wCoef*hitLineTemp->length()/2.0,sourcePoint->y()-hCoef*hitLineTemp->length()/3.0);
            controlPointTarget = new QPointF(targetPoint->x() + wCoef*hitLineTemp->length()/2.0,targetPoint->y() + hCoef*hitLineTemp->length()/3.0);

            hitPath.cubicTo(*controlPointSource,*controlPointTarget, *targetPoint);
        } else {
            hitPath.lineTo(*targetPoint);
        }
    } else if ( (isAutoHit() && sourceSort->getSimpleDisplay() != 1)
                ||targetSort->getSimpleDisplay()!=1) {
        if(dynamic_cast<GSort*>(getTarget()->getDisplayItem()->parentItem())->isVertical() && targetPoint->y() > resultPoint->y()) {
            rectCornerY = source->getCenterPoint()->y();
            heightRect = (sourcePoint->y() - targetPoint->y())*2;
            invertSweep=1;
        } else if (dynamic_cast<GSort*>(getTarget()->getDisplayItem()->parentItem())->isVertical() && targetPoint->y() < resultPoint->y()) {
            heightRect = (targetPoint->y() - sourcePoint->y())*2;
            rectCornerY = source->getCenterPoint()->y() - heightRect;
            invertSweep=-1;
        } else if (!(dynamic_cast<GSort*>(getTarget()->getDisplayItem()->parentItem())->isVertical())) {
            heightRect = (targetPoint->y() - sourcePoint->y())*2;
            rectCornerY = source->getCenterPoint()->y();
            invertSweep= -1;
        }
        if(dynamic_cast<GSort*>(getTarget()->getDisplayItem()->parentItem())->isVertical() && resultPoint->x() < getResult()->getCenterPoint()->x()) {
            widthRect = (sourcePoint->x() - targetPoint->x())*2;
            rectCornerX = sourcePoint->x() - widthRect;
            invertStart=-1;
        } else if (dynamic_cast<GSort*>(getTarget()->getDisplayItem()->parentItem())->isVertical() && resultPoint->x() > getResult()->getCenterPoint()->x()) {
            rectCornerX = sourcePoint->x();
            widthRect = (targetPoint->x() - sourcePoint->x())*2;
            invertStart=1;
        } else if(!(dynamic_cast<GSort*>(getTarget()->getDisplayItem()->parentItem())->isVertical()) && resultPoint->x() < targetPoint->x()) {
            rectCornerX = source->getCenterPoint()->x();
            widthRect = (sourcePoint->x() - targetPoint->x())*2;
            invertStart=-1;
        } else if (!(dynamic_cast<GSort*>(getTarget()->getDisplayItem()->parentItem())->isVertical()) && resultPoint->x() > targetPoint->x()) {
            widthRect = (targetPoint->x() - sourcePoint->x())*2;
            rectCornerX = sourcePoint->x() - widthRect;
            invertStart=1;
        }
        if (dynamic_cast<GSort*>(getTarget()->getDisplayItem()->parentItem())->isVertical()) {
            startAngle = invertStart*180 ;
            sweepAngle = invertSweep*270;
        } else {
            startAngle = /**invertStart**/90 ;
            sweepAngle = invertSweep*270 ;
        }

        hitPath.arcTo(QRectF(rectCornerX,rectCornerY,widthRect,heightRect),startAngle,sweepAngle);
    }

    hitPath.addPolygon(makeArrowHead(hitPath));


    return hitPath;
}
// Bound Part
QPainterPath GAction::createBoundPath() {
    QPainterPath boundPath(*targetPoint);

    if((targetPoint->x()!=resultPoint->x())||(targetPoint->y()!=resultPoint->y())) {
        qreal rectCornerX;
        qreal rectCornerY;
        qreal widthRect;
        qreal heightRect;
        qreal sweepAngle;
        qreal startAngle;
        int invertSweep;

        if(dynamic_cast<GSort*>(getTarget()->getDisplayItem()->parentItem())->isVertical()) {
            if(targetPoint->y()<resultPoint->y()) {
                rectCornerY = targetPoint->y();
                heightRect = resultPoint->y()-targetPoint->y();
                startAngle = 90;
                invertSweep = 1;
            } else {
                rectCornerY = resultPoint->y();
                heightRect = targetPoint->y()-resultPoint->y();
                startAngle = -90;
                invertSweep = -1;
            }

            if(resultPoint->x() < getResult()->getCenterPoint()->x()) {
                sweepAngle = 180*invertSweep;
            } else {
                sweepAngle = -180*invertSweep;
            }

            rectCornerX = resultPoint->x()- (GProcess::sizeDefault)/2.0;
            widthRect = GProcess::sizeDefault;
        } else {

            if(targetPoint->x()<resultPoint->x()) { //target point à gauche de resultpoint
                rectCornerX = targetPoint->x();
                widthRect = resultPoint->x() - targetPoint->x();
                startAngle =180;
                invertSweep = -1;
            } else { //resultpoint à gauche de targetpoint
                rectCornerX = resultPoint->x();
                widthRect = targetPoint->x() - resultPoint->x();
                startAngle =0;
                invertSweep = 1;
            }
            if(resultPoint->y()<getResult()->getCenterPoint()->y()) { //resultpoint au-dessus du centre du process
                rectCornerY = resultPoint->y()-(GProcess::sizeDefault)/2.0;
                sweepAngle = 180*invertSweep;
            } else { //resultpoint en-dessus du centre du process
                rectCornerY= resultPoint->y()-(GProcess::sizeDefault)/2.0;
                sweepAngle = -180*invertSweep;
            }
            heightRect = GProcess::sizeDefault;
        }


        boundPath.arcTo(QRectF(rectCornerX,rectCornerY,widthRect,heightRect),startAngle,sweepAngle);

        boundPath.addPolygon(makeArrowHead(boundPath));
    }

    return boundPath;
}

// draw an arrowhead
QPolygonF GAction::makeArrowHead(QPainterPath path) {

    // arrow pointing to the right
    QPointF p = path.pointAtPercent(1);
    QPointF* q = new QPointF(p.x() - 8, p.y() - 5);
    QPointF* r = new QPointF(p.x() - 8, p.y() + 5);
    QPointF* s = new QPointF(p.x() - 1, p.y());
    QPointF* t = new QPointF(p.x() - 7.5, p.y() + 4);
    QPointF* u = new QPointF(p.x() - 7.5, p.y() - 4);
    QPolygonF polygon;
    polygon.push_back(p);
    polygon.push_back(*q);
    polygon.push_back(*u);
    polygon.push_back(*s);
    polygon.push_back(*t);
    polygon.push_back(*r);

    // rotate arrow
    QMatrix matrix;
    matrix.translate(p.x(), p.y());
    if(sourcePoint!=targetPoint) {
        matrix.rotate(-path.angleAtPercent(1));
    } else {
        matrix.rotate(-path.angleAtPercent(0.98));
    }
    matrix.translate(-p.x(), -p.y());
    polygon = matrix.map(polygon);

    // turn into QGraphicsPolygonItem
    return polygon;
}

//Verify if this action is in bold
bool GAction::isBold() {
    return bold;
}

//make on bold this action
void GAction::toBold() {
    QPen pen;
    if(this->isBold()) {
        pen.setWidth(1);
        pen.setBrush(Qt::black);
        hitLine->setPen(pen);
        pen.setStyle(Qt::DashLine);
        boundArc->setPen(pen);
        this->bold=false;
    } else {
        pen.setWidth(2);
        pen.setBrush(Qt::black);
        hitLine->setPen(pen);
        pen.setStyle(Qt::DashLine);
        boundArc->setPen(pen);
        bold=true;
    }
}

//Color this action
void GAction::colorAction(QColor color) {

    if (!color.isValid()) {
        return ;
    } else {
        QPen pen;
        pen.setWidth(3);
        pen.setBrush(QBrush(QColor(color)));
        hitLine->setPen(pen);
        pen.setStyle(Qt::DashLine);
        boundArc->setPen(pen);
    }
}

//Change the number of action color
void GAction::setActionColorNUmber(int r, int g, int b, int nb) {
    this->numberActionColor=nb;
    QPen pen;
    if(r==0 && g==0 && b==0)
        pen.setWidth(1);
    else
        pen.setWidth(2);
    pen.setBrush(QBrush(QColor(r,g,b)));
    hitLine->setPen(pen);
    pen.setStyle(Qt::DashLine);
    boundArc->setPen(pen);
}

// getters

QGraphicsItem* GAction::getDisplayItem (void) {
    return display;
}

ActionPtr GAction::getAction() {
    return action;
}

GProcessPtr GAction::getSource() {
    return action->getSource()->getGProcess();
}

GProcessPtr GAction::getTarget() {
    return action->getTarget()->getGProcess();
}

GProcessPtr GAction::getResult() {
    return action->getResult()->getGProcess();
}

int GAction::getActionColorNumber() {
    return this->numberActionColor;
}
