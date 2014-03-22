#pragma once
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <list>
#include "PH.h"
#include "Process.h"
/**
  * @file GProcess.h
  * @brief header for the GProcess class
  * @author PAPPL_2013
  *
  */

class GProcess;
typedef boost::shared_ptr<GProcess> GProcessPtr;
class Process;
typedef boost::shared_ptr<Process> ProcessPtr;


/**
  * @class GProcess
  * @brief contains style and layout info to draw a process
  *
  */
class GProcess {

	public:

	static const int sizeDefault;

        /**
          * @brief constructor
          *
          * @param ProcessPtr the related Process object
          * @param double centerX position of the center of the ellipse in the x axis
          * @param double centerY position of the center of the ellipse in the y axis
          */
	GProcess(ProcessPtr p,double centerX, double centerY);

	~GProcess();

        /**
          * @brief gets the related Process
          *
          */
        ProcessPtr* getProcess();
        /**
          * @brief gets the related Process
          *
          */
        ProcessPtr getProcessPtr();

        /**
          * @brief gets the display
          *
          * @return QGraphicsItem the graphical item representing the Process
          */
	QGraphicsItem* getDisplayItem (void);

        /**
          * @brief gets the ellipse
          *
          */
        QGraphicsEllipseItem* getEllipseItem();

        /**
          * @brief gets the rect item that represents the margin of this GProcess
          *
          */
        QGraphicsRectItem* getMarginRect();

        /**
          * @brief get the center of the ellipse representing the process
          *
          * @return GPoint the center of the ellipse
          *
          */
	QPointF* getCenterPoint();

        /**
          * @brief get the size of the ellipse representing the process
          *
          * @return GSize the size of the ellipse
          *
          */
	QSizeF* getSizeEllipse();

        /**
          * @brief gets the text item
          *
          */
	QGraphicsTextItem* getText();

        /**
          * @brief updates the related center's coordinates with a point
          *
          * @param int x the horizontal coordinate of the node
          * @param int y the vertical coordinate of the node
          *
          */

        void setCoordsForImport(int x, int y);

        /**
          * @brief colorer les process
          */
        void colorProcess(QColor);
        /**
          * @brief colorer la bordure du process
          */
        void colorProcessBorder(QColor color);
        /**
          * @brief transform this process to bold
          */
        void toBold();      
        /**
          * @brief transform this process to actif state
          */
        void beActifProcess(int r, int g, int b);
        /**
          * @brief transform this process to non actif state
          */
        void beNonActifProcess();
        /**
          * @brief gets the state of the process
          *
          */
        bool getProcessActifState();
        /**
          * @brief sets the state of the process
          *
          */
        void setProcessActifState(bool state);
        /**
          * @brief gets the number of color RGB to tikZ file
          *
          */
        int getProcessColorNumber();
        /**
          * @brief sets the number of the process color RGB to TikZ file
          *
          */
        void setProcessColorNumber(int nb);
        /**
          * @brief verify if this process is bold
          */
        bool isBold();
	
	protected:

        /**
          * @brief the related Process
          *
          */
	ProcessPtr process;

        /**
          * @brief position of the center of the ellipse representing the process
          *
          */
	QPointF* center;

        /**
          * @brief size of the ellipse representing the process
          *
          */
	QSizeF* size;

        /**
          * @brief the graphical item representing the Process
          *
          */
	QGraphicsItem* display;

        /**
          * @brief the graphical item representing the ellipse of the Process
          *
          */
	QGraphicsEllipseItem* ellipse;

        /**
          * @brief the graphical item representing the text of the Process
          *
          */
        QGraphicsTextItem* text;

        /**
          * @brief the margin around this process, must exclude any other process' margin (cf. graphviz attribute "pos" in GVSubGraph)
          *
          */
        QGraphicsRectItem* marginRect;

        /**
          * @brief if this process is bold or not
          */
        bool bold;
        /**
          * @brief if this process is bold or not
          */
        bool actifState;
        /**
          * @brief color of this process
          */
        int numberProcessColor;

        /**
          * @brief arbitrarily-chosen key for "margin item" data
          *
          */
        static const int marginZone;

        /**
          * @brief arbitrarily-chosen key for sort name data
          *
          */
        static const int sortName;

	/**
	  * @brief init geometrics characteristics of the GProcess
	  *
	  * @param QPointF center point to set the GProcess
	  * @param double diameter of the GProcess
	  */
	void initGeometricsValues(QPointF centerPoint, double diameter);

	/**
	  * @brief init the ellipse item
	  */
	void initEllipseItem();

	/**
	  * @brief init the marginRect item
	  */
	void initMarginRectItem();

	/**
	  * @brief init the text item
	  */
    void initTextItem();

};
