#ifndef TIKZEDITOR_H
#define TIKZEDITOR_H

#include <iostream>
#include <QtGui>
#include <QGraphicsScene>
#include <map>
#include <string>
#include "GAction.h"



class TikzEditor : public QDialog
{
    Q_OBJECT

public:
    //constructor , destructor
    TikzEditor(PHPtr);
    ~TikzEditor();
    PHPtr myPHPtr;
    bool allChecked;

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
    QVBoxLayout *box1;
    QVBoxLayout *box2;
    QVBoxLayout *box3;

    QGroupBox *choiceBoxS;
    QCheckBox *colorSorts ;
    QCheckBox *boldSorts ;

    QGroupBox *choiceBoxP;
    QCheckBox *colorProcess ;
    QCheckBox *boldProcess ;

    QGroupBox *choiceBoxA;
    QCheckBox *colorAction;
    QCheckBox *boldAction;

    QVBoxLayout *choiceLayout;


    //check

    QPushButton *check;
    QHBoxLayout *checkLayout;


private slots:

    //void colorS();
    void colorP();
    //void colorAction();

    //void boldS();
    //void boldP();
    //void boldAction();

    void checkUncheckAll();
    QList <QTreeWidgetItem* > getSelectedSorts();
    QList <QTreeWidgetItem* > getUnselectedSorts();

    QList<QPair <QString,QString> > getUnselectedProcess();
    QList<QPair <QString,QString> > getSelectedProcess();

    void back();
    void generateTikz();
    void quit();
};





#endif // TIKZEDITOR_H
