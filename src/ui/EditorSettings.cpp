#include "EditorSettings.h"
#include "MainWindow.h"
#include "PH.h"
#include "PHIO.h"
#include <QtGui>
#include "Area.h"

EditorSettings::EditorSettings(PHPtr myPHPtr): QDialog()
{
    choiceBox = new QGroupBox("Exclusive checkBox");

    groupLayout = new QVBoxLayout;

    // Get all the sorts of the PH file
    list<SortPtr> allSorts = myPHPtr->getSorts();
    for(SortPtr &s : allSorts){

    sort_Name = new QRadioButton(QString::fromStdString(s->getName()));
    // Insert the item at the end of the layout: sorts
    groupLayout->addWidget(sort_Name);

    }

    //Buttons
    Generate = new QPushButton("Generate");
    Annuler = new QPushButton("Cancel");
    Edit = new QPushButton("Edit");


    btnLayout = new QHBoxLayout;
    btnLayout->addWidget(Annuler);
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
    //Detroyer
    EditorSettings::~EditorSettings(){}
