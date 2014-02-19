#include "EditorSettings.h"
#include "MainWindow.h"
#include <QtGui>
#include "Area.h"

EditorSettings::EditorSettings(): QDialog()
{




    choiceBox = new QGroupBox("Exclusive checkBox");
    ch1 = new QRadioButton("Radio button &1");
    ch2 =new QRadioButton("Radio button &2");

    ch1->setChecked("true");

    groupLayout = new QVBoxLayout;
    groupLayout->addWidget(ch1);
    groupLayout->addWidget(ch2);


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
    //Detroyer
    EditorSettings::~EditorSettings(){}

