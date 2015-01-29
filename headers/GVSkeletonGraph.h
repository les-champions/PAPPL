#pragma once
#include <graphviz/gvc.h>
#include <boost/shared_ptr.hpp>
#include <QFont>
#include <QMap>
#include <QPair>
#include <QString>
#include "GVNode.h"
#include "GVEdge.h"

/**
  * @file GVSkeletonGraph.h
  * @brief header for the GVSkeletonGraph class
  * @author PGROU_2013
  *
  */

class GVSkeletonGraph;
typedef boost::shared_ptr<GVSkeletonGraph> GVSkeletonGraphPtr;


/**
  * @class GVSkeletonGraph
  * @brief the object containing a libraph graph representing the skeleton (sorts+actions) of the model and its associated nodes and edges
  *
  */
class GVSkeletonGraph {

  public:

    /**
     * @brief GVSkeletonGraph constructor
     * @param QString name the name given to the skeleton graph
     * @param QFont font
     */
    GVSkeletonGraph(QString name, QFont font =QFont());

    virtual ~GVSkeletonGraph();

    // Constants for GraphViz constraints

    /**
     * @brief Default DPI value used by dot (which uses points instead of pixels for coordinates)
     *
     */
    static const qreal DotDefaultDPI;

    /**
     * @brief Size in pixels of each node of the skeleton, related to the size of the corresponding Sort
     *
     */
    static const qreal nodeSize;

    /**
     * @brief Minimum margin around each node (in points for graphviz)
     *
     */
    static const qreal sepValue;

    // Graph management

    /**
     	 * @brief Set the graph dpi and sepValue to their default values
     *
     */
    void  setGraphAttributes();


    /**
     * @brief set an attribute to a given value for a graph element
     * @param void *object the element to set attribute of
     * @param QString attr the name of the attribute to set
     * @param QString value the value to set the attribute to
     */
    void setGraphObjectAttributes(void *object, QString attr, QString value);

    /**
     * @brief set the font used for the graph
     * @param QFont font the font to set for the graph
     */
    void setFont(QFont font);

    // Layout

    /**
     * @brief builds the layout
     */
    void  applyLayout();

    /**
     * @brief export the graph into the file out.png (for test purpose)
     */
    void exportToPng();

    // Node management

    /**
     	 * @brief tranforms the _nodes attribute into a liste of GVNode
     *
     * @return a list QList<GVNode> containing nodes of the graph
     */
    QList<GVNode>  nodes();

    /**
     * @brief add a node to the graph
     * @param QString name the name of the node to add to the graph
     */
    void addNode(const QString& name);

    /**
     * @brief remove a node from the graph
     * @param QString name the name of the node to remove from the graph
     */
    void removeNode(const QString& name);

    /**
     * @brief check if a node exists in the graph
     * @param QString name the name of the node which existence is to be checked
     */
    bool hasNode(const QString& name);

    /**
     * @brief setter for the nodeSize attribute
     * @param object : the node to modify
     * @param width : new width of the node
     * @param height : new height of the node
     */
    void setNodeSize(void* object, qreal width, qreal height);

    /**
     * @brief gets a node by its name
     * @param QString name the name of the node to get
     	 * @return Agnode_t* a pointer to the retrieved node
     */
    Agnode_t* getNode(const QString& name);

    /**
     * @brief remove all nodes of the graph
     */
    void  clearNodes();

    // Edge management

    /**
     * @brief add a edge to the graph
     * @param QString source the name first node related to the edge
     * @param QString target the name second node related to the edge
     */
    void addEdge(const QString &source, const QString &target);

    /**
     * @brief remove a edge to the graph
     * @param QString source the name first node related to the edge
     * @param QString target the name second node related to the edge
     */
    void removeEdge(const QString &source, const QString &target);

    /**
     * @brief remove a edge to the graph
     * @param QPair<QString, QString> key pair of nodes related to the edge
     */
    void removeEdge(const QPair<QString, QString>& key);

    /**
     	 * @brief check if an edge exists between two nodes in the graph
     * @param QString source the name first node related to the edge
     * @param QString target the name second node related to the edge
     * @return bool true if the connection exists, false if it doesn't
     */
    bool connectionExists(const QString &sourceName, const QString &targetName);

    /**
     * @brief gets the DPI value
     *
     * @return qreal the DPI value
     */
    qreal  getDPI();

    /**
     * @brief gets the graphviz graph struct of this GVSkeletonGraph
     *
     * @return Agraph_t* a pointer to the graph
     */
    Agraph_t*  graph();

  protected:

    QFont _font;
    GVC_t *_context;
    Agraph_t* _graph;
    QMap<QString, Agnode_t*> _nodes;
    QMap<QPair<QString, QString>, Agedge_t*> _edges;
};
