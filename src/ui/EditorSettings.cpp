#include "EditorSettings.h"
#include "MainWindow.h"
#include "PH.h"
#include "PHIO.h"
#include <QtGui>
#include "Area.h"
#include "PH.h"
#include "PHIO.h"

EditorSettings::EditorSettings(PHPtr myPHPtr): QDialog()
{
    this->myPHPtr=myPHPtr;

    groupLayout = new QVBoxLayout;

    // Get all the sorts of the PH file
    list<SortPtr> allSorts = myPHPtr->getSorts();

    for(SortPtr &s : allSorts){
       sort_Name = new QCheckBox(QString::fromStdString(s->getName()));
        // Insert the item at the end of the layout: sorts
        groupLayout->addWidget(sort_Name);
        listOfSorts.push_back(sort_Name);
    }

    choiceBox = new QGroupBox("List of sorts");
    choiceBox->setLayout(groupLayout);

    selectAll=new QRadioButton("All");
    selectNone=new QRadioButton("None");

    connect(selectAll, SIGNAL(clicked()), this, SLOT(checkAll()));
    connect(selectNone, SIGNAL(clicked()), this, SLOT(checkNone()));

    checkLayout=new QHBoxLayout;
    checkLayout->addWidget(selectAll);
    checkLayout->addWidget(selectNone);

    //Buttons

    Cancel = new QPushButton("&Cancel");
    Cancel->setFixedWidth(80);

    Finish = new QPushButton("&Finish");
    Finish->setFixedWidth(80);

    //connect slots
    connect(Cancel, SIGNAL(clicked()), this, SLOT(quit()));
    connect (Finish,SIGNAL(clicked()),this,SLOT(finish()));

    btnLayout = new QHBoxLayout;
    btnLayout->addWidget(Cancel);
    btnLayout->addWidget(Finish);

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

    void EditorSettings::hideNonSelected(){
        QList<QString> listehidenSorts =getNonSelectedSorts();
        for (QString &n: listehidenSorts){
            // Hide the QGraphicsItem representing the sort
            myPHPtr->getGraphicsScene()->getGSort(n.toStdString())->GSort::hide();
            // Hide all the actions related to the sort
            std::vector<GActionPtr> allActions = myPHPtr->getGraphicsScene()->getActions();
            for (GActionPtr &a: allActions){
                if (a->getAction()->getSource()->getSort()->getName() == n.toStdString() || a->getAction()->getTarget()->getSort()->getName() == n.toStdString() || a->getAction()->getResult()->getSort()->getName() == n.toStdString()){
                a->getDisplayItem()->hide();
            }
        }
      }
    }
    //return a list of selected sorts name
    QList<QString> EditorSettings::getSelectedSorts(){
        QList<QString> selectedList;
        for (QCheckBox *s: listOfSorts){
            if(s->isChecked()){
                selectedList.push_back(s->text());
            }
    }
    return selectedList;
    }

    //return a list of non selected sorts name
    QList<QString> EditorSettings::getNonSelectedSorts(){

        QList<QString> nonSelectedList;
        for (QCheckBox *s: listOfSorts){
            if(!-s->isChecked()){
                nonSelectedList.push_back(s->text());
            }
    }
    return nonSelectedList;
    }


    void EditorSettings::quit(){

      this->~EditorSettings();
    }

    void EditorSettings::finish(){

        QList<QString> selectedList =this->getSelectedSorts();
        bool test=true;
        if (selectedList.empty()) test=false;

        //if no sort is selected , return a message error
        if (test==false){
            QMessageBox::critical(this, "Error", "At least one sort must be selected");
        }
        else{
                QDialog* mb = new QDialog();
                //Display loading window
                mb->setWindowTitle("Please wait...");
                mb->resize(300,150);
                mb->show();
                hideNonSelected();

             sleep(2);
             this->~EditorSettings();
        }

    }

    void EditorSettings::checkAll(){
        for (QCheckBox *s: listOfSorts){
             s->setChecked(true);
        }
    }

    void EditorSettings::checkNone(){

        std::cout<<"check non"<<std::endl;
        for (QCheckBox *s: listOfSorts){
             s->setChecked(false);
        }
    }

    //Detroyer
    EditorSettings::~EditorSettings(){}

