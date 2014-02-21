#include "EditorOptions.h"
#include "MainWindow.h"
#include "PH.h"
#include "PHIO.h"
#include <QtGui>
#include "Area.h"
#include "PH.h"
#include "PHIO.h"


EditorOptions::EditorOptions(): QDialog()
{

    //Buttons

    Cancel = new QPushButton("&Cancel");
    Cancel->setFixedWidth(80);

    Next = new QPushButton("&Next");
    Next->setFixedWidth(80);

    Generate = new QPushButton("&Generate");
    Generate->setFixedWidth(80);


    btnLayout = new QHBoxLayout;
    btnLayout->addWidget(Cancel);
    btnLayout->addWidget(Next);
    btnLayout->addWidget(Generate);

    globalLayout = new QVBoxLayout;
    globalLayout->addLayout(btnLayout);


    setLayout(globalLayout);
    setWindowTitle("Edit Otions");
    setModal(true);
    resize(300,300);

}



    //Detroyer
    EditorOptions::~EditorOptions(){}


