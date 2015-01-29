#ifndef TIKZEDITOR_H
#define TIKZEDITOR_H

#include <iostream>
#include <QtGui>
#include <QGraphicsScene>
#include <map>
#include <string>
#include "GAction.h"



class TikzEditor : public QDialog {
    Q_OBJECT

  public:
    //constructor , destructor
    TikzEditor(PHPtr);
    ~TikzEditor();
    PHPtr myPHPtr;
    bool allChecked;

    int column;
    void colorP(int n);
    void unColorP();
    void boldP();
    void unBold();
    void colorA(int n);
    void unColorA();
    void boldA();
    void unBoldA();

    QList <QTreeWidgetItem* > getSelectedSorts();
    QList <QTreeWidgetItem* > getUnselectedSorts();

    QList<QPair <QString,QString> > getUnselectedProcess();
    QList<QPair <QString,QString> > getSelectedProcess();



  private:

    //button
    QPushButton *Show;
    QPushButton *Generate;
    QPushButton *Exit;
    QHBoxLayout *btnLayout ;

    //
    QTreeWidget *fontTree;
    QVBoxLayout *treeLayout;

    QVBoxLayout *globalLayout;
    QHBoxLayout *layoutTotal;

    QTreeWidgetItem *sortItem;
    QTreeWidgetItem *processItem;


    //choice

    QVBoxLayout *box2;
    QVBoxLayout *box3;

    QGroupBox *choiceBoxP;
    QCheckBox *colorProcess ;
    QCheckBox *boldProcess ;

    QGroupBox *choiceBoxA;
    QCheckBox *colorAction;
    QCheckBox *boldAction;

    QVBoxLayout *choiceLayout;

    //Color
    QHBoxLayout *colorProcessLayout;
    QRadioButton *grayp;
    QRadioButton *redp;
    QRadioButton *greenp;
    QRadioButton *bluep;

    QHBoxLayout *colorActionLayout;
    QRadioButton *graya;
    QRadioButton *reda;
    QRadioButton *greena;
    QRadioButton *bluea;

    //check/unchek all

    QPushButton *check;
    QHBoxLayout *checkLayout;


  private slots:

    void setStatus(QTreeWidgetItem *item, int column);
    void checkUncheckAll();
    void back();
    void generateTikz();
    void quit();
    void testA(int);
    void testP(int);
    void colorOrBoldAction(int);
    void boldOrColorAction(int);
};


#endif // TIKZEDITOR_H
