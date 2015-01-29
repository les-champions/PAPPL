#pragma once
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QColor>
#include <QSize>
#include <QPoint>
#include <vector>
#include "Sort.h"
#include "GVNode.h"
#include "GProcess.h"
#include "PHScene.h"

/**
  * @file GSort.h
  * @brief header for the GSort class
  * @author PAPPL_2012
  *
  */

class GSort;
typedef boost::shared_ptr<GSort> GSortPtr;
class GSimpleProcess;
class PHScene;
typedef boost::shared_ptr<GProcess> GProcessPtr;

/**
  * @class GSort
  * @brief contains style and layout info to draw a Sort
  *
 */
class GSort : public QGraphicsRectItem {

  public:

    static const int marginDefault;

    static const int defaultDistance;

    /**
      * @brief constructor
      *
      * @param SortPtr the related Sort object
      * @param GVNode the node of the skeleton graph containing layout info
      * @param qreal width of the Sort
      * @param qreal height of the Sort
      */
    GSort(SortPtr p, GVNode n, qreal width, qreal height,PHScene* sc);

    ~GSort();

    /**
      * @brief get the rect item
      *
      */
    QGraphicsRectItem* getRect();

    /**
      * @brief the color used by the Actions that have this Sort as source
      *
      */
    QColor* color;

    /**
      * @brief Handles mouse press event (handles drag start)
      *
      * @param QGraphicsSceneMouseEvent the event to be handled
      */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /**
      * @brief Handles mouse move event (handles drag)
      *
      * @param QGraphicsSceneMouseEvent the event to be handled
      */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    /**
      * @brief Handles mouse release event (handles drop)
      *
      * @param QGraphicsSceneMouseEvent the event to be handled
      */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    /**
      * @brief Handles context menu event (typically on right click)
      *
      * @param QGraphicsSceneContextMenuEvent the event to be handled
      */
    //  void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    /**
      * @brief gets the related Sort object
      *
      * @return SortPtr a pointer to the related Sort object
      */
    SortPtr getSort();

    /**
      * @brief gets the related Node object
      *
      * @return GVnode a pointer to the related Sort object
      */
    GVNode getNode();

    /**
      * @brief gets the text of the sort
      *
      */
    QGraphicsTextItem* getText();

    /**
      * @brief gets the point used to record mouse press event position
      *
      */
    QPoint geteventPressPoint();

    /**
      * @brief get the left top corner of the GSort
      *
      * @return GPointF* a pointer to the leftTopCorner attribute
      *
      */
    QPointF* getLeftTopCornerPoint();

    /**
      * @brief get the center of the GSort
      *
      * @return GPointF center of the GSort
      *
      */
    QPointF getCenterPoint();

    /**
      * @brief get the size of the ellipse representing the process
      *
      * @return GSize the size of the ellipse
      *
      */
    QSize* getSizeRect();

    /**
      * @brief get the simple display state
      *
      * @return bool value of the attribute simpleDisplay
      *
      */

    vector <GProcessPtr>getGProcesses();
    bool getSimpleDisplay();

    void changeDisplayState();

    /**
          * @brief setters for simpleDisplay attributes
          *
      * @param bool value to set simpleDisplay to
          */
    void setSimpleDisplay(bool isSimpleDisplay);

    /**
      * @brief hides this GSort setting opacity to 0
      */
    void hide();

    void actionsHide();
    /**
      * @brief show the GSort setting full opacity
      */
    void show();

    void actionsShow();

    /**
      * @brief indicates whether or not this GSort is made visible (test based on opacity, cf. hide() and show())
      */
    bool isVisible();

    /**
      * @brief return the value of the vertical attribute
      *
    * @return bool value of the vertical attribute
      */
    bool isVertical();
    /**
      * @brief indicates whether or not this GSort is made in bold
      */
    bool isBold();
    /**
      * @brief change this GSort to bold
      */
    void toBold();
    /**
      * @brief change the GActions In of this Sort to bold
      */
    void ActionsInToBold();
    /**
    * @brief change the GActions out of this Sort to bold
    */
    void ActionsOutToBold();
    /**
      * @brief change the GActions In color
      */
    void ActionsInChangeColor();
    /**
      * @brief change the GActions out color
      */
    void ActionsOutChangeColor();
    /**
      * @brief change the process color
      */
    void processChangeColor();
    /**
      * @brief change the process border color
      */
    void processChangeBorderColor();
  protected:

    /**
      * @brief position of the left top corner of the rectangle representing the sort
      *
      */
    QPointF* leftTopCorner;

    /**
      * @brief size of the rectangle representing the sort
      *
      */
    QSize* sizeRect;

    /**
      * @brief the graphical item representing the rectangle of the Sort
      *
      */
    QGraphicsRectItem* _rect;

    /**
      * @brief the graphical item representing the text of the Sort
      *
      */
    QGraphicsTextItem* text;

    /**
      * @brief the related Sort
      *
      */
    SortPtr sort;

    /**
      * @brief list of GProcessPtr contained by the sort
      *
      */
    vector<GProcessPtr> gProcesses;

    /**
      * @brief the related of the skeletonGraph
      *
      */
    GVNode node;

    /**
      * @brief the palette of colors that may be used as color member
      *
      */
    static std::vector<QColor> palette;

    /**
      * @brief palette management index
      *
      */
    static int paletteIndex;

    /**
      * @brief gets a new color in the palette
      *
      * @return QColor* the color retrieved in the palette
      */
    static QColor* makeColor(void);

    /**
      * @brief the point used to record this GSort's coordinates when user clicks it (ie. starts drag&drop)
      *
      */
    QPoint initPosPoint;

    /**
      * @brief the point used to record mouse press event position
      *
      */
    QPoint eventPressPoint;

    /**
      * @brief the space between this GSort's top side and the top GProcess
      *
      */
    qreal paddingTop;

    /**
      * @brief if the sort is vertical or not
      *
      */
    bool vertical;
    /**
      * @brief if the sort is in bold or not
      *
      */
    bool bold;

    /**
      * @brief if action related to this sort has to be displayed following the simplified model
      *
      */
    bool simpleDisplay;

    /**
          * @brief to know if the right button of the mouse is pressed (to prevent drag'n'drop in this case)
          *
          */
    bool isRightButtonPressed;

    PHScene* scene;

    /**
          * @brief initialize inner attributes of the GSort
          *
          */
    void initInnerAttributes();

    /**
          * @brief initialize geometrics attributes of the GSort
          *
      * @param QSize size of the GSort
          */
    void initGeometricAttributes(QSize size);

    /**
          * @brief initialize the _rect item of the GSort
          *
          */
    void initRectItem();

    /**
          * @brief initialize the label of the GSort
          *
          */
    void initTextItem();

    /**
          * @brief initialize GProcess related to the GSort
          *
          */
    void initGProcessChildren();

    /**
      * @brief shifts the GSort according to the coordinates of a shiftVector
      *
    * @param QPointF the shifting vector
      */
    void shiftPosition(QPointF shiftVector);

    /**
      * @brief check if the GSort is over another
      *
    * @return bool the result of the checking
      */
    bool isOverAnotherGSort();

    /**
      * @brief check if the GSort is over a specified GSort
      *
    * @return bool the result of the checking
      */
    bool isOver(GSort* otherGSort);

    /**
      * @brief set the position of the GSort at the state before it has moved
      *
      */
    void cancelShift();

    /**
      * @brief change the orientation of the GSort
      *
      */
    void changeOrientation();
    /**
      * @brief change the color of the GSort
      *
      */
    void changeColor();

    /**
      * @brief change the orientation of the GSort rectangle
      *
      */
    void changeOrientationRect();

    /**
      * @brief change the orientation of the GProcess children
      *
      */
    void changeOrientationGProcess();
    void processChangeBold();

};
