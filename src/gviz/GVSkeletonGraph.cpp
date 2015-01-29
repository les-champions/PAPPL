#include <iostream>
#include <graphviz/gvc.h>
#include <boost/make_shared.hpp>
#include <QStringList>
#include <QRectF>
#include "Exceptions.h"
#include "GVSkeletonGraph.h"
#include "locale.h"

const qreal GVSkeletonGraph::DotDefaultDPI=72.0;
const qreal GVSkeletonGraph::nodeSize = 1;
const qreal GVSkeletonGraph::sepValue = 30.0;

// Utils

static inline Agnode_t* _agnode(Agraph_t* object, QString name) {
    setlocale(LC_NUMERIC,"en_US.UTF-8"); // To set "." as decimal delimiter for GraphViz

    return agnode(object, const_cast<char *>(qPrintable(name)));
}

static inline Agraph_t* _agopen(QString name, int kind) {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    return agopen(const_cast<char *>(qPrintable(name)),kind);
}

static inline QString _agget(void *object, QString attr, QString alt=QString()) {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    QString str = agget(object, const_cast<char *>(qPrintable(attr)));
    if(str==QString()) return alt;
    else return str;
}

static inline Agsym_t* _agnodeattr(Agraph_t* object, QString attr, QString value) {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    return agnodeattr(object, const_cast<char *>(qPrintable(attr)),const_cast<char *>(qPrintable(value)));
}

static inline Agsym_t* _agedgeattr(Agraph_t* object, QString attr, QString value) {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    return agedgeattr(object, const_cast<char *>(qPrintable(attr)),const_cast<char *>(qPrintable(value)));
}

static inline void _gvLayout(GVC_t* context, Agraph_t* graph, QString alg) {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    gvLayout(context, graph, const_cast<char *>(qPrintable(alg)));
}

GVSkeletonGraph::GVSkeletonGraph(QString name, QFont font) {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    _context = gvContext();
    _graph = _agopen(name, AGDIGRAPHSTRICT);
    setGraphAttributes();
    setFont(font);
}

GVSkeletonGraph::~GVSkeletonGraph() {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    gvFreeLayout(_context,_graph);
    agclose(_graph);
    gvFreeContext(_context);
}

void GVSkeletonGraph::setGraphAttributes() {
    setlocale(LC_NUMERIC,"en_US.UTF-8");
    setGraphObjectAttributes(_graph,"dpi","96,0");
    QString strSepValue = QString::number(sepValue).prepend("+");
    setGraphObjectAttributes(_graph, "sep", strSepValue);
}

void GVSkeletonGraph::setGraphObjectAttributes(void *object, QString attr, QString value) {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    agsafeset(object, const_cast<char *>(qPrintable(attr)),const_cast<char *>(qPrintable(value)),const_cast<char *>(qPrintable(value)));
}

void GVSkeletonGraph::setFont(QFont font) {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    _font = font;
    setGraphObjectAttributes(_graph,"fontname",font.family());
}

void GVSkeletonGraph::applyLayout() {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    gvFreeLayout(_context, _graph);
    _gvLayout(_context, _graph, "dot");
}


void GVSkeletonGraph::exportToPng() {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    gvRenderFilename(_context,_graph,"png","out.png");
}

// Node management

QList<GVNode> GVSkeletonGraph::nodes() {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    QList<GVNode> list;
    qreal dpi = this->getDPI();
    for(QMap<QString, Agnode_t*>::const_iterator it = _nodes.begin(); it != _nodes.end(); ++it) {
        Agnode_t *node = it.value();
        GVNode object;
        object.name = node->name;

        qreal x = node ->u.coord.x *(dpi/GVSkeletonGraph::DotDefaultDPI);
        qreal y = -node ->u.coord.y *(dpi/GVSkeletonGraph::DotDefaultDPI);

        object.centerPos = QPoint(x,y);

        object.height = node->u.height * dpi;
        object.width = node->u.width * dpi;

        list << object;
    }

    return list;
}

void GVSkeletonGraph::addNode(const QString& name) {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    if(_nodes.contains(name)) removeNode(name);

    _nodes.insert(name, _agnode(_graph, name));
}

void GVSkeletonGraph::removeNode(const QString& name) {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    if(_nodes.contains(name)) {
        agdelete(_graph, _nodes[name]);
        _nodes.remove(name);
    }
}

bool GVSkeletonGraph::hasNode(const QString& name) {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    if(_nodes.contains(name)) return true;
    return false;
}

Agnode_t* GVSkeletonGraph::getNode(const QString& name) {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    if(_nodes.contains(name)) return _nodes[name];

    return NULL;
}

void GVSkeletonGraph::setNodeSize(void* object, qreal width, qreal height) {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    QString nodePtsWidth = QString("%1").arg(width/_agget(_graph,"dpi", "96,0").replace(',',".").toDouble());
    setGraphObjectAttributes(object,"width",nodePtsWidth.replace('.',","));
    QString nodePtsHeight = QString("%1").arg(height/_agget(_graph,"dpi", "96,0").replace(',',".").toDouble());
    setGraphObjectAttributes(object,"height",nodePtsHeight.replace('.',","));
}

void GVSkeletonGraph::clearNodes() {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    QList<QString> keys = _nodes.keys();
    for(int i=0; i<keys.size(); ++i) {
        removeNode(keys.at(i));
    }
}

// Edge management

void GVSkeletonGraph::addEdge(const QString &source, const QString &target) {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    if (hasNode(source) && hasNode(target)) {
        QPair<QString, QString> key(source, target);

        if(!_edges.contains(key)) _edges.insert(key, agedge(_graph, getNode(source), getNode(target)));

    }
}

void GVSkeletonGraph::removeEdge(const QString &source, const QString &target) {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    removeEdge(QPair<QString, QString>(source, target));
}

void GVSkeletonGraph::removeEdge(const QPair<QString, QString>& key) {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    if(_edges.contains(key)) {
        agdelete(_graph, _edges[key]);
        _edges.remove(key);
    }
}

bool GVSkeletonGraph::connectionExists(const QString &sourceName, const QString &targetName) {
    setlocale(LC_NUMERIC,"en_US.UTF-8");

    QPair<QString,QString> firstPossibility(sourceName,targetName);
    QPair<QString,QString> secondPossibility(targetName,sourceName);
    return _edges.contains(firstPossibility)||_edges.contains(secondPossibility);
}

qreal GVSkeletonGraph::getDPI() {
    setlocale(LC_NUMERIC,"en_US.UTF-8");
    return _agget(_graph, "dpi","96,0").replace(',',".").toDouble();
}

Agraph_t* GVSkeletonGraph::graph() {
    setlocale(LC_NUMERIC,"en_US.UTF-8");
    return this->_graph;
}

