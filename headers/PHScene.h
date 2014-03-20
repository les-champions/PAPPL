#pragma once
#include <boost/shared_ptr.hpp>
#include <QObject>
#include <QGraphicsScene>
#include <map>
#include <string>
#include "GAction.h"



/**
  * @file PHScene.h
  * @brief header for the PHScene class
  * @author PAPPL_2012
  *
  */

using std::map;
using std::string;

// mutual inclusions
class PH;
class GProcess;
typedef boost::shared_ptr<GProcess> GProcessPtr;
class GSort;
typedef boost::shared_ptr<GSort> GSortPtr;
class GAction;
typedef boost::shared_ptr<GAction> GActionPtr;

class PHScene;
typedef boost::shared_ptr<PHScene> PHScenePtr;

typedef std::pair<string, GSortPtr> GSortEntry;


/**
  * @class PHScene
  * @brief the graphic object representing the process hitting
  * extends QGraphicsScene
  *
  */
class PHScene: public QGraphicsScene {
	
	public:
        /**
          * @brief constructor
          * @param PH* the PH graph to use
          *
          */
        PHScene(PH* _ph);

        /**
          * @brief create a GVSkeletonGraph from the PH object, then draw the PHSCene from it
          *
          */
        void drawFromSkeleton(void);

        /**
          * @brief gets a GSort by its related Sort's name
          * @param string the name of the (G)Sort to get
          * @return GSortPtr pointer to the GSort to get
          *
          */
	GSortPtr getGSort (const string& s);

        /**
          * @brief getter for sorts
          *
          */
        map<string, GSortPtr> getGSorts();

        /**
          * @brief get the processes
          *
          */
        std::vector<GProcessPtr> getProcesses();

        /**
          * @brief get the actions
          *
          */
        std::vector<GActionPtr> getActions();


        /**
          * @brief update the position of actions
          *
          */
        void updateActions();


        /**
          * @brief switch the display mode between detailled/simplified
          * @param bool activate or not the simplified model
          */
        void setSimpleDisplay(bool onOff);
        /**
          * @brief Handles mouse press event (handles drag start)
          *
          * @param QGraphicsSceneMouseEvent the event to be handled
          */
       void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

       /**
         * @brief change the color of the background
         *
         */
        void BackgroundColor();
        /**
          * @brief change the actions in bold
          *
          */
         void ActionsInBold();
         /**
           * @brief change the color of the action
           *
           */
         void ActionColor();

	protected:

        /**
          * @brief the related process hitting
          *
          */
		PH* ph;

        /**
          * @brief map of the Sorts drawn in the scene: the keys are the names of the Sorts
          *
          */
        map<string, GSortPtr> sorts;

        /**
          * @brief vector of the Processes drawn in the scene
          *
          */
        std::vector<GProcessPtr> processes;

        /**
          * @brief vector of the Actions drawn in the scene
          *
          */
        std::vector<GActionPtr> actions;

        /**
          * @brief creates GAction items from graphviz graph (GVEdge structs)
          *
          */
        void createActions();

};
