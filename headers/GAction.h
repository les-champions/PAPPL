#pragma once
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <list>
#include <utility>
#include "GVEdge.h"
#include "PHScene.h"
#include "Action.h"
#include "GSort.h"

#include <QtGui/qgraphicswidget.h>
#include <QColor>
#include <QSize>
#include <QPoint>
#include <vector>


/**
  * @file GAction.h
  * @brief header for the GAction class
  * @author PAPPL_2012
  *
  */

class GAction;
typedef boost::shared_ptr<GAction> GActionPtr;
class Action;
typedef boost::shared_ptr<Action> ActionPtr;
class PHScene;

using std::pair;


/**
  * @class GAction
  * @brief contains style and layout info to draw an action
  *
  */
class GAction {

	public:

    /**
      * @brief constructor
      *
      * @param ActionPtr the related Action object
      * @param GVEdge the object that contains style and layout info for hit arrow
      * @param GVEdge the object that contains style and layout info for bounce (result) arrow
      * @param PHScene the related scene
      */
	GAction(ActionPtr a, GVEdge e, GVEdge f, PHScene* sc);

    /**
      * @brief constructor
      *
      * @param ActionPtr the related Action object
      * @param PHScene the related scene
      */
	GAction(ActionPtr a, PHScene* sc);

	GAction();

        ~GAction();

     /**
       * @brief update position of GAction
       *
       */
        void update();

     /**
       * @brief gets the display
       *
       * @return QGraphicsItem the graphical item representing the Action
       */
		QGraphicsItem* getDisplayItem (void);

        /**
          * @brief gets the action
          *
          */
        ActionPtr getAction();

        /**
          * @brief gets the source GProcess item
          *
          * @preturn GProcessPtr a pointer to the source GProcess item
          */
        GProcessPtr getSource();

        /**
          * @brief gets the target GProcess item
          *
          * @return GProcessPtr a pointer to the target GProcess item
          */
        GProcessPtr getTarget();

        /**
          * @brief gets the result GProcess item
          *
          * @param GProcessPtr a pointer to the result GProcess item
          */
        GProcessPtr getResult();
        /**
          * @brief indicates whether or not this action is in bold
          */
        bool isBold();
        /**
          * @brief change this GAction to bold
          */
        void toBold();
        /**
          * @brief change this GAction color
          */
        void colorAction(QColor);
	
	protected:
	
        /**
          * @brief the PHScene related to the Action
          *
          */
	PHScene* scene;

        /**
          * @brief the graphical item representing the Action
          *
          */
	QGraphicsItem* display;

        /**
          * @brief line representing the first part of the action
          *
          */
     QGraphicsPathItem* hitLine;

        /**
          * @brief path representing the second part of the action
          *
          */
        QGraphicsPathItem* boundArc;

        /**
          * @brief target Point of the line representing the first part of the action
          *
          */
        QPointF* targetPoint;

        /**
          * @brief source Point of the line representing the first part of the action
          *
          */
        QPointF* sourcePoint;


        /**
          * @brief source Point of the arc representing the second part of the action
          *
          */
        QPointF* resultPoint;


        /**
          * @brief the related Action
          *
          */
        ActionPtr action;

        /**
          * @brief if the action is in bold or not
          *
          */
        bool bold;

        /**
          * @brief the pair of graphical items representing the tails of the arrows of the Action
          *
          */
	pair<QGraphicsPathItem*, QGraphicsPathItem*> 		arrowTails;

        /**
          * @brief the pair of graphical items representing the heads of the arrows of the Action
          *
          */
        pair<QGraphicsPolygonItem* , QGraphicsPolygonItem*>	arrowHeads;

        /**
          * @brief the edges related to the arrows
          *
          */
	pair<GVEdge, GVEdge> edges;

        /**
          * @brief init the position of sourcePointLine, targetPointLine and resultPointLine
          */
	void initContactPoints();

        /**
          * @brief update the position of sourcePointLine, targetPointLine and resultPointLine
          */
	void updateContactPoints();
        
	/**
          * @brief build the line corresponding to the first part of the action
	  *
	  * @return QPainterPath the line representing the first part of the action
          */
    	QPainterPath createHitPath();

    	/**
          * @brief build the arc corresponding to the second part of the action
      	  *
      	  * @return QPainterPath the arc representing the second part of the action
          */
    	QPainterPath createBoundPath();


        /**
          * @brief draws the head of the arrow
          *
          * @param GVEdge the edge related to the arrow
          * @param Qcolor the color of the arrow
          *
          * @return QGraphicsPolygonItem* the graphical item representing the head of the arrow
          *
          */
	QPolygonF makeArrowHead(QPainterPath path);

	/**
	  * @brief init contact points to display the GAction in simple model
	  *
	  */
	void initPointsInSimpleModele();

	/**
	  * @brief init contact points to display the GAction in detailled model
	  *
	  */
	void initPointsInDetailledModel();

	/**
	  * @brief update contact points to display the GAction in simple model
	  *
	  */
	void updatePointsInSimpleModel();	

	/**
	  * @brief update contact points to display the GAction in detailled model
	  *
	  */
	void updatePointsInDetailledModel();

	/**
	  * @brief check if the source and the target process are the same
	  *
	  */
	bool isAutoHit();

	/**
	  * @brief init contact points in the case of normal hit
	  *
	  */
	void initPointsNormalHit();

	/**
	  * @brief update contact points in the case of normal hit
	  *
	  */
	void updatePointsNormalHit();

	/**
	  * @brief init contact points in the case of an auto hit
	  *
	  */
	void initPointsAutoHit();

	/**
	  * @brief init contact points in the case of an auto hit
	  *
	  */
	void updatePointsAutoHit();

    /**
      * @brief check if the hit needs to be curved
      *
      */
    bool isCurvedHit(GSortPtr sourceSort,GSortPtr targetSort,  GProcessPtr source,  GProcessPtr target);
};
