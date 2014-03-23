#include "TikzEditor.h"
#include "MainWindow.h"
#include "PH.h"
#include "PHIO.h"
#include <QtGui>
#include "Area.h"
#include<iostream>
#include<stdio.h>
#include<utility>

TikzEditor::TikzEditor(PHPtr myPHPtr): QDialog()
{

    this->column=1;
    this->myPHPtr=myPHPtr;
    this->allChecked=false;
    fontTree = new QTreeWidget();
    fontTree->setHeaderLabels(QStringList() << tr("List of sorts"));
    fontTree->setColumnCount(1);

    // Get all the sorts of the PH file
    list<SortPtr> allSorts = myPHPtr->getSorts();

    for(SortPtr &s : allSorts){

       QString sortName = QString::fromStdString(s->getName());
        //
        sortItem = new QTreeWidgetItem(fontTree);
        sortItem->setText(0, sortName);
        sortItem->setCheckState(0, Qt::Unchecked);
        if(myPHPtr->getGraphicsScene()->getGSort(s->getName())->GSort::isVisible()){
            allChecked=true;
            sortItem->setCheckState(0, Qt::Checked);
        }
        for(ProcessPtr &p : s->getProcesses()){
            QString processNumber=QString::number(p->getNumber());

            processItem = new QTreeWidgetItem(sortItem);
            processItem->setText(0, processNumber);
            processItem->setCheckState(0, Qt::Unchecked);
        }
    }

    //connect items changed
    connect(fontTree, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
            this, SLOT(setStatus(QTreeWidgetItem*,int)));

    //check sorts
    checkLayout=new QHBoxLayout;
    check = new QPushButton("&Check/Uncheck all");
    checkLayout->addWidget(check);
    connect(check, SIGNAL(clicked()), this, SLOT(checkUncheckAll()));

    treeLayout=new QVBoxLayout;
    treeLayout->addWidget(fontTree);
    treeLayout->addLayout(checkLayout);


    //Buttons: creation
    Generate = new QPushButton("&Generate");
    Generate->setFixedWidth(80);

    Show = new QPushButton("&Show");
    Show->setFixedWidth(80);

    Exit = new QPushButton("&Exit");
    Exit->setFixedWidth(80);

    //Buttons:connect slots
    connect(Show, SIGNAL(clicked()), this, SLOT(back()));
    connect(Generate,SIGNAL(clicked()),this,SLOT(generateTikz()));
    connect(Exit,SIGNAL(clicked()),this,SLOT(quit()));

    //Buttons: add to layout
    btnLayout = new QHBoxLayout;
    btnLayout->addWidget(Show);
    btnLayout->addWidget(Generate);
    btnLayout->addWidget(Exit);

    //Choice of a color for the process
    colorProcessLayout=new QHBoxLayout;
    grayp=new QRadioButton("gray");
    redp=new QRadioButton("red");
    greenp=new QRadioButton("green");
    bluep=new QRadioButton("blue");
    colorProcessLayout->addWidget(grayp);
    colorProcessLayout->addWidget(redp);
    colorProcessLayout->addWidget(greenp);
    colorProcessLayout->addWidget(bluep);

    //choice of color for the actions
    colorActionLayout=new QHBoxLayout;
    graya=new QRadioButton("black");
    reda=new QRadioButton("red");
    greena=new QRadioButton("green");
    bluea=new QRadioButton("blue");
    colorActionLayout->addWidget(graya);
    colorActionLayout->addWidget(reda);
    colorActionLayout->addWidget(greena);
    colorActionLayout->addWidget(bluea);


    choiceBoxP=new QGroupBox("Active process");
    colorProcess=new QCheckBox("Color process");
    boldProcess=new QCheckBox("Bold process");
    colorProcess->setCheckState(Qt::Unchecked);
    boldProcess->setCheckState(Qt::Unchecked);
        //verify if at least one process is checked before checking
    connect(colorProcess,SIGNAL(stateChanged(int)),this, SLOT(testP(int)));
    connect(boldProcess,SIGNAL(stateChanged(int)),this, SLOT(testP(int)));

    box2=new QVBoxLayout;
    box2->addWidget(colorProcess);
    box2->addWidget( boldProcess);
    box2->addLayout(colorProcessLayout);
    choiceBoxP->setLayout(box2);

    choiceBoxA=new QGroupBox("Actions jouables");
    colorAction=new QCheckBox("Color actions");
    boldAction=new QCheckBox("Bold actions");
    boldAction->setCheckState(Qt::Unchecked);
    colorAction->setCheckState(Qt::Unchecked);
    //verify if at least two process are checked
    connect(colorAction,SIGNAL(stateChanged(int)),this, SLOT(testA(int)));
    connect(boldAction,SIGNAL(stateChanged(int)),this, SLOT(testA(int)));
    connect(boldAction,SIGNAL(stateChanged(int)),this, SLOT(colorOrBoldAction(int)));
    connect(colorAction,SIGNAL(stateChanged(int)),this, SLOT(boldOrColorAction(int)));

    box3=new QVBoxLayout;
    box3->addWidget(colorAction);
    box3->addWidget( boldAction);
    box3->addLayout(colorActionLayout);
    choiceBoxA->setLayout(box3);

    choiceLayout=new QVBoxLayout;
    choiceLayout->addWidget(choiceBoxP);
    choiceLayout->addWidget(choiceBoxA);

    layoutTotal=new QHBoxLayout;
    layoutTotal->addLayout(treeLayout);
    layoutTotal->addLayout(choiceLayout);

    globalLayout=new QVBoxLayout;
    globalLayout->addLayout(layoutTotal);
    globalLayout->addLayout(btnLayout);

    setLayout(globalLayout);
    setWindowTitle("Choice of Sorts");
    setModal(true);
    resize(500,300);

}

void TikzEditor::quit(){

    this->~TikzEditor();
}



void TikzEditor::back(){

    QList <QTreeWidgetItem*> selectedItems=getSelectedSorts();
    for(QTreeWidgetItem *item:selectedItems){
        // Show the QGraphicsItem representing the sort
        QString n=item->text(0);
        myPHPtr->getGraphicsScene()->getGSort(n.toStdString())->GSort::show();
        myPHPtr->getGraphicsScene()->getGSort(n.toStdString())->GSort::actionsShow();
     }

    QList <QTreeWidgetItem*> nonSelectedItems=getUnselectedSorts();
    for(QTreeWidgetItem *item:nonSelectedItems){
        // Hide the QGraphicsItem representing the sort
         QString n=item->text(0);
        myPHPtr->getGraphicsScene()->getGSort(n.toStdString())->GSort::hide();
        myPHPtr->getGraphicsScene()->getGSort(n.toStdString())->GSort::actionsHide();
     }

    if(colorProcess->isChecked()){
        if(redp->isChecked())
            colorP(1);
        else if(greenp->isChecked())
            colorP(2);
        else if(bluep->isChecked())
            colorP(3);
        else
            colorP(0);
    }else{
        unColorP();
    }

    if(boldProcess->isChecked()){
        boldP();
    }else{
        unBold();
    }
    if(colorAction->isChecked()){
        if(reda->isChecked())
            colorA(1);
        else if(greena->isChecked())
            colorA(2);
        else if(bluea->isChecked())
            colorA(3);
        else if(graya->isChecked())
            colorA(0);
    }else{
        unColorA();
    }
    if(boldAction->isChecked()){
        boldA();
    }else{
        unBoldA();
    }
}

QList<QTreeWidgetItem*> TikzEditor::getUnselectedSorts(){

    QList <QTreeWidgetItem*> nonSelectedItems;
    for(int i=0;i<fontTree->topLevelItemCount();i++){
        if(fontTree->topLevelItem(i)->checkState(0)== Qt::Unchecked){
            nonSelectedItems.push_back(fontTree->topLevelItem(i));
        }
    }
    return nonSelectedItems;
}


QList<QTreeWidgetItem*> TikzEditor::getSelectedSorts(){

    QList <QTreeWidgetItem*> selectedItems;
    for(int i=0;i<fontTree->topLevelItemCount();i++){
        if(fontTree->topLevelItem(i)->checkState(0)== Qt::Checked){
            selectedItems.push_back(fontTree->topLevelItem(i));
        }
    }
    return selectedItems;
}


QList<QPair <QString,QString> >  TikzEditor::getSelectedProcess(){

  QList<QPair <QString,QString> >  selectedItems;
  QPair<QString,QString> elem;
    for (int i=0;i<fontTree->topLevelItemCount();i++) {
        QTreeWidgetItem *sortItem = fontTree->topLevelItem(i);
        for (int j = 0; j < sortItem->childCount(); j++) {
            QTreeWidgetItem *processItem = sortItem->child(j);
            if (processItem->checkState(0) == Qt::Checked){
               elem.first=fontTree->topLevelItem(i)->text(0);
               elem.second=processItem->text(0);
                selectedItems.push_back(elem);
        }
        }

    }
    return selectedItems;
}


QList<QPair <QString,QString> >   TikzEditor::getUnselectedProcess(){

    QList<QPair <QString,QString> >  unSelectedItems;
    QPair <QString,QString> elem;
    for (int i=0;i<fontTree->topLevelItemCount();i++) {
        QTreeWidgetItem *sortItem = fontTree->topLevelItem(i);
        for (int j = 0; j < sortItem->childCount(); j++) {
            QTreeWidgetItem *processItem = sortItem->child(j);
            if (processItem->checkState(0) == Qt::Unchecked)
                elem.first=fontTree->topLevelItem(i)->text(0);
                elem.second=processItem->text(0);
                unSelectedItems.push_back(elem);
              }
    }
    return unSelectedItems;
}


// method to export style and layout data to Tikz format
void TikzEditor::generateTikz(){

    QList <QTreeWidgetItem*> selectedSorts=getSelectedSorts();
    if (!selectedSorts.empty()){
        back();
        // SaveFile dialog
        QString tikzFile = QFileDialog::getSaveFileName(this, "Export preferences", QString(), "*.tex");

        // add .dot to the name if necessary
        if (tikzFile.indexOf(QString(".tex"), 0, Qt::CaseInsensitive) < 0){
              tikzFile += ".tex";
         }

        // open file if possible and write Tikz into it
         QFile output(tikzFile);
         if (!output.open(QIODevice::WriteOnly)){
             QMessageBox::critical(this, "Error", "Sorry, unable to open file.");
                output.errorString();
                return;
                } else {
                        PHIO::exportTikzMetadata(myPHPtr,output);
                    }
               } else QMessageBox::critical(this, "Error", "No sort selected!");
    }

//check and uncheck alla sorts
void TikzEditor::checkUncheckAll(){
    if(allChecked){

        for(int i=0;i<fontTree->topLevelItemCount();i++){
            fontTree->topLevelItem(i)->setCheckState(0, Qt::Unchecked);
         }
         allChecked=false;
    }

    else{

        for(int i=0;i<fontTree->topLevelItemCount();i++){
        fontTree->topLevelItem(i)->setCheckState(0, Qt::Checked);
     }
        allChecked=true;
    }

}

//Color selected process
void TikzEditor::colorP(int n){

    QList<QPair <QString,QString> >  selectedProcesses = getSelectedProcess();
    vector <GProcessPtr> process;

    unColorP();
    for (QPair<QString,QString> &sp : selectedProcesses ){
        process=myPHPtr->getGraphicsScene()->getGSort(sp.first.toStdString())->GSort::getGProcesses();

        for(GProcessPtr &p:process){
            p->setProcessColorNumber(n);
            if((QString::number(p->getProcessPtr()->getNumber()).compare(sp.second))==0){
                p->setProcessColorNumber(n);
                p->setProcessActifState(true);
                if(n==1){
                    p->beActifProcess(255,0,0);
                }else if(n==2){
                    p->beActifProcess(0,255,0);
                }else if(n==3){
                    p->beActifProcess(0,0,255);
                }else{
                    p->beActifProcess(201,201,201);
                }
            }
        }
    }
}

//uncolor all process before color them
void TikzEditor::unColorP(){

    vector <GProcessPtr> process;
    list<SortPtr> allSorts = myPHPtr->getSorts();
    for (SortPtr &s : allSorts ){
        process=myPHPtr->getGraphicsScene()->getGSort(s->getName())->GSort::getGProcesses();
        for(GProcessPtr &p:process){
                p->beNonActifProcess();
        }
    }
}

//transform the process on bold
void TikzEditor::boldP(){

    QList<QPair <QString,QString> >  selectedProcesses = getSelectedProcess();
    vector <GProcessPtr> process;

    unBold();
    for (QPair<QString,QString> &sp : selectedProcesses ){
        process=myPHPtr->getGraphicsScene()->getGSort(sp.first.toStdString())->GSort::getGProcesses();

        for(GProcessPtr &p:process){
            if((QString::number(p->getProcessPtr()->getNumber()).compare(sp.second))==0){
                if(!p->isBold()){
                    p->toBold();
                }
                p->setProcessActifState(true);
            }
        }
    }
}

//transform to unBold processes
void TikzEditor::unBold(){

    vector <GProcessPtr> process;
    list<SortPtr> allSorts = myPHPtr->getSorts();
    for (SortPtr &s : allSorts ){
        process=myPHPtr->getGraphicsScene()->getGSort(s->getName())->GSort::getGProcesses();
        for(GProcessPtr &p:process){
            if(p->isBold()){
                p->toBold();
                p->setProcessActifState(false);
            }
        }
    }

}

//color selected Actions
void TikzEditor::colorA(int n){

    this->unColorA();
    this->unBoldA();
    QString pnumS;
    QString pnumT;
    QString snameS;
    QString snameT;
    QList<QPair <QString,QString> >  selectedProcesses = getSelectedProcess();
    vector <GActionPtr> allActions=myPHPtr->getGraphicsScene()->getActions();
    for (GActionPtr &a: allActions){

        pnumS = QString::number(a->getAction()->getSource()->getNumber());
        pnumT = QString::number(a->getAction()->getTarget()->getNumber());

        snameS=QString::fromStdString(a->getAction()->getSource()->getSort()->getName());
        snameT=QString::fromStdString(a->getAction()->getTarget()->getSort()->getName());

        for (QPair<QString,QString> &sp : selectedProcesses ){
            if(sp.second.compare(pnumS)==0 && sp.first.compare(snameS)==0){
                for (QPair<QString,QString> &s : selectedProcesses ){
                    if(s.second.compare(pnumT)==0 && s.first.compare(snameT)==0){
                       if(n==1){
                          a->setActionColorNUmber(255,0,0,n);
                       }else if(n==2){
                           a->setActionColorNUmber(0,255,0,n);
                       }else if(n==3){
                           a->setActionColorNUmber(0,0,255,n);
                       }else{
                           a->setActionColorNUmber(0,0,0,n);
                       }
                    }
                }
            }
        }
    }
}

//uncolor all actions
void TikzEditor::unColorA() {

    vector <GActionPtr> allActions=myPHPtr->getGraphicsScene()->getActions();
    for (GActionPtr &a: allActions){
        a->setActionColorNUmber(0,0,0,-1);
    }
}

void TikzEditor::boldA(){

    this->unColorA();
    this->unBoldA();
    QString pnumS;
    QString pnumT;
    QString snameS;
    QString snameT;
    QList<QPair <QString,QString> >  selectedProcesses = getSelectedProcess();
    vector <GActionPtr> allActions=myPHPtr->getGraphicsScene()->getActions();
    for (GActionPtr &a: allActions){

        pnumS = QString::number(a->getAction()->getSource()->getNumber());
        pnumT = QString::number(a->getAction()->getTarget()->getNumber());

        snameS=QString::fromStdString(a->getAction()->getSource()->getSort()->getName());
        snameT=QString::fromStdString(a->getAction()->getTarget()->getSort()->getName());

        for (QPair<QString,QString> &sp : selectedProcesses ){
            if(sp.second.compare(pnumS)==0 && sp.first.compare(snameS)==0){
                for (QPair<QString,QString> &s : selectedProcesses ){
                    if(s.second.compare(pnumT)==0 && s.first.compare(snameT)==0){
                        a->setActionColorNUmber(0,0,0,0);
                        a->toBold();
                    }
                }
            }
        }
     }
}

//transform all actions to unbold
void TikzEditor:: unBoldA(){

    vector <GActionPtr> allActions=myPHPtr->getGraphicsScene()->getActions();
    for (GActionPtr &a: allActions){
        if(a->isBold()){
             a->toBold();
         }
    }
}

void TikzEditor:: setStatus(QTreeWidgetItem *item,int column){

        if (!item || column != 0)
            return;
        Qt::CheckState state = item->checkState(0);
        QTreeWidgetItem *parent = item->parent();
        QList<QPair <QString,QString> >  selectedProcesses ;
        if (parent) {

            if (state == Qt::Checked) {
                // Mark parent items when child items are checked.
                parent->setCheckState(0, Qt::Checked);
                colorProcess->setCheckState(Qt::Checked);
            }
            else if (state == Qt::Unchecked) {
                 selectedProcesses = getSelectedProcess();
                // Unmark color process and color sort when child items are unchecked.
                if (selectedProcesses.size()<2){
                    boldAction->setCheckState(Qt::Unchecked);
                    colorAction->setCheckState(Qt::Unchecked);
                }
                if (selectedProcesses.size()==0){
                    boldProcess->setCheckState(Qt::Unchecked);
                    colorProcess->setCheckState(Qt::Unchecked);
                }
                }
        } else {
            int row;
            int number = 0;
            for (row = 0; row < item->childCount(); ++row) {
                if (item->child(row)->checkState(0) == Qt::Checked)
                    ++number;
            }
            // unmark all child items when unmarking top-level
            // items.
          if (state == Qt::Unchecked && number > 0) {
                for (row = 0; row < item->childCount(); ++row) {
                    if (item->child(row)->checkState(0) == Qt::Checked)
                        item->child(row)->setCheckState(0, Qt::Unchecked);
                }
            }
        }
}


//test if the user has selected at least two processes
void TikzEditor::testA(int state){

    QList<QPair <QString,QString> >  selectedProcesses = getSelectedProcess();
    if(state){
        if (selectedProcesses.size()<=1){
            QMessageBox::critical(this, "Error", "At least two process must be selected");
            if(colorAction->isChecked()==true)
                colorAction->setCheckState(Qt::Unchecked);
            if(boldAction->isChecked()==true)
                boldAction->setCheckState(Qt::Unchecked);

        }
    }

}

// test if the user has selected at least one process
void TikzEditor::testP(int state){

    QList<QPair <QString,QString> >  selectedProcesses = getSelectedProcess();

    if(state){
        if (selectedProcesses.size()==0){
            QMessageBox::critical(this, "Error", "At least one process must be selected");
            if(colorProcess->isChecked()==true)
                colorProcess->setCheckState(Qt::Unchecked);
            if(boldProcess->isChecked()==true)
                boldProcess->setCheckState(Qt::Unchecked);
        }
    }
}

//the action can be only in bold or colored
void TikzEditor::colorOrBoldAction(int state){
    if (state)
        colorAction->setCheckState(Qt::Unchecked);
}

void TikzEditor::boldOrColorAction(int state){
    if (state)
        boldAction->setCheckState(Qt::Unchecked);
}

//Detroyer
TikzEditor::~TikzEditor(){}

