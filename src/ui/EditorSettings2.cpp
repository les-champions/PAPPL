#include "EditorSettings2.h"
#include "MainWindow.h"
#include "PH.h"
#include "PHIO.h"
#include <QtGui>
#include "Area.h"
#include "PH.h"
#include "PHIO.h"

EditorSettings
EditorSettings2::EditorSettings2(): QDialog()
{

    groupLayout = new QVBoxLayout;


    choiceBox = new QGroupBox("List of sorts");
    choiceBox->setLayout(groupLayout);

    selectAll=new QRadioButton("All");
    selectNone=new QRadioButton("None");

    checkLayout=new QHBoxLayout;
    checkLayout->addWidget(selectAll);
    checkLayout->addWidget(selectNone);

    //Buttons

    Cancel = new QPushButton("&Cancel");
    Cancel->setFixedWidth(80);

    Next = new QPushButton("&Next");
    Next->setFixedWidth(80);

    Generate = new QPushButton("&Generate");
    Generate->setFixedWidth(80);

    connect(Next, SIGNAL(clicked()), this, SLOT(next()));
    connect(Cancel, SIGNAL(clicked()), this, SLOT(quit()));
    //ToDO : method generate
    connect (Generate,SIGNAL(clicked()),this,SLOT(quit()));

    btnLayout = new QHBoxLayout;
    btnLayout->addWidget(Cancel);
    btnLayout->addWidget(Next);
    btnLayout->addWidget(Generate);

    globalLayout = new QVBoxLayout;
    globalLayout->addWidget(choiceBox);
    globalLayout->addLayout(checkLayout);
    globalLayout->addLayout(btnLayout);


    this->setLayout(globalLayout);

    //ajout du scroll
    widget = new QWidget;
    widget->setLayout(globalLayout);
    area = new QScrollArea;
    area->setWidget(widget);
    area->setWidgetResizable(true);

    layoutTotal = new QVBoxLayout;
    layoutTotal->addWidget(area);


    setLayout(layoutTotal);
    setWindowTitle("Choice of Sorts");
    setModal(true);
    resize(300,300);

}


//void EditorSettings2::hideNonSelected(QList<QString> listehidenSorts,PHPtr myPHPtr){

//    for (QString &n: listehidenSorts){
//        // Hide the QGraphicsItem representing the sort
//        myPHPtr->getGraphicsScene()->getGSort(n.toStdString())->GSort::hide();

//        // Hide all the actions related to the sort
//        std::vector<GActionPtr> allActions = myPHPtr->getGraphicsScene()->getActions();
//        for (GActionPtr &a: allActions){
//            if (a->getAction()->getSource()->getSort()->getName() == n.toStdString() || a->getAction()->getTarget()->getSort()->getName() == n.toStdString() || a->getAction()->getResult()->getSort()->getName() == n.toStdString()){
//                a->getDisplayItem()->hide();
//            }
//        }
//        }
//}


//return a list of selected sortss name
QList<QString> EditorSettings2::getSelectedSorts(){

    QList<QString> selectedList;
    for (QCheckBox *s: listOfSorts){
        if(s->isChecked()){
            selectedList.push_back(s->text());
        }
    }
    return selectedList;
}



void EditorSettings2::quit(){

      this->~EditorSettings2();
}


void EditorSettings2::next(){

     QList<QString> selectedList =this->getSelectedSorts();

     for (QString s: selectedList){
         std::cout<<s.toStdString()<<std::endl;
         }

    this->~EditorSettings2();

}

void EditorSettings2::generate(){
    this->~EditorSettings2();

}

    //Detroyer
    EditorSettings2::~EditorSettings2(){}


