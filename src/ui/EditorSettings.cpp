#include "EditorSettings.h"
#include "MainWindow.h"
#include <QtGui>
#include "Area.h"
#include "PH.h"
#include "PHIO.h"

EditorSettings::EditorSettings(PHPtr myPHPtr): QDialog()
{

    groupLayout = new QVBoxLayout;
    choiceBox = new QGroupBox("Exclusive checkBox");

    // Get all the sorts of the PH file
    list<SortPtr> allSorts = myPHPtr->getSorts();
    for(SortPtr &s : allSorts){

       sort_Name = new QCheckBox(QString::fromStdString(s->getName()));
       tabSorts.push_back(sort_Name);
        // Insert the item at the end of the layout: sorts
        groupLayout->addWidget(sort_Name);
    }


    //Button Generate
    Generate = new QPushButton("Generate");
    Cancel = new QPushButton("Cancel");
    Edit = new QPushButton("Edit");


    btnLayout = new QHBoxLayout;
    btnLayout->addWidget(Cancel);
    btnLayout->addWidget(Edit);
    btnLayout->addWidget(Generate);


    globalLayout = new QVBoxLayout;
    globalLayout->addLayout(groupLayout);
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
    resize(500,500);

}


 list<std::string> EditorSettings::getSelectedSorts(){

//     list<std::string> vect=new list<std::string> ;

//    for(QCheckBox &s : this->tabSorts){
//        if(s.isChecked())
//            vect.push_back(s.accessibleName());
//    }
//    return vect;

}


    //Detroyer
    EditorSettings::~EditorSettings(){}


