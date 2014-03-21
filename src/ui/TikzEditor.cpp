
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

    //check sorts

    checkLayout=new QHBoxLayout;
    check = new QPushButton("&Check/Uncheck all");
    checkLayout->addWidget(check);
    connect(check, SIGNAL(clicked()), this, SLOT(checkUncheckAll()));

    treeLayout=new QVBoxLayout;
    treeLayout->addWidget(fontTree);
    treeLayout->addLayout(checkLayout);


    //Buttons
    Generate = new QPushButton("&Generate");
    Generate->setFixedWidth(80);

    Show = new QPushButton("&Show");
    Show->setFixedWidth(80);

    Exit = new QPushButton("&Exit");
    Exit->setFixedWidth(80);

    //connect slots
    connect(Show, SIGNAL(clicked()), this, SLOT(back()));
    connect(Generate,SIGNAL(clicked()),this,SLOT(generateTikz()));
    connect(Exit,SIGNAL(clicked()),this,SLOT(quit()));

    btnLayout = new QHBoxLayout;
    btnLayout->addWidget(Show);
    btnLayout->addWidget(Generate);
    btnLayout->addWidget(Exit);

    //
    choiceBoxS=new QGroupBox("Sorts");
    colorSorts=new QCheckBox("Color Sorts");
    boldSorts=new QCheckBox("Sort in color");
    box1=new QVBoxLayout;
    box1->addWidget(colorSorts);
    box1->addWidget( boldSorts);
    choiceBoxS->setLayout(box1);


    choiceBoxP=new QGroupBox("Process");
    colorProcess=new QCheckBox("Color selected process");
    boldProcess=new QCheckBox("Bold selected process");
    box2=new QVBoxLayout;
    box2->addWidget(colorProcess);
    box2->addWidget( boldProcess);
    choiceBoxP->setLayout(box2);

    choiceBoxA=new QGroupBox("Actions");
    colorAction=new QCheckBox("Color actions");
    boldAction=new QCheckBox("Bold actions");
    box3=new QVBoxLayout;
    box3->addWidget(colorAction);
    box3->addWidget( boldAction);
    choiceBoxA->setLayout(box3);

    choiceLayout=new QVBoxLayout;
    choiceLayout->addWidget(choiceBoxS);
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
// fontTree->topLevelItem(i)->setCheckState(0, Qt::Unchecked);

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
        colorP();
    }

//    QMap <QString,QString> nonSelectedProcess=getUnselectedProcess();
//    QMap <QString,QString>  selectedProcess=getSelectedProcess();


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
               } else QMessageBox::critical(this, "Error", "No file opened!");
    }



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



void TikzEditor::colorP(){

    QList<QPair <QString,QString> >  selectedProcesses = getSelectedProcess();
    QList<QPair <QString,QString> >  unselectedProcesses = getSelectedProcess();

    vector <GProcessPtr> process;
    list<SortPtr> allSorts = myPHPtr->getSorts();

    for (SortPtr &s : allSorts ){
        process=myPHPtr->getGraphicsScene()->getGSort(s->getName())->GSort::getGProcesses();

        for(GProcessPtr &p:process){
                p->beNonActifProcess();
        }
    }

    for (QPair<QString,QString> &sp : selectedProcesses ){
        process=myPHPtr->getGraphicsScene()->getGSort(sp.first.toStdString())->GSort::getGProcesses();

        for(GProcessPtr &p:process){
            if((QString::number(p->getProcessPtr()->getNumber()).compare(sp.second))==0)
                p->beActifProcess();
        }
    }
}

void TikzEditor::boldP(){

}

//void TikzEditor::boldP(){

//        QList<QPair <QString,QString> >  selectedProcesses = getSelectedProcess();
//        QString sortName;
//        QString processNumber;

//        for (QPair<QString,QString> &sp : selectedProcesses ){
//            std::cout<<sp.first.toStdString()<<":"<<sp.second.toStdString()<<std::endl;
//            //call function to bold
//        }
//}

void TikzEditor::onClear(){

    QTreeWidgetItem *currentItem = fontTree->currentItem();
    foreach (QTreeWidgetItem *item, fontTree->selectedItems())
            fontTree->setItemSelected(item, false);
        fontTree->setItemSelected(currentItem, true);

}

//Detroyer
TikzEditor::~TikzEditor(){}
