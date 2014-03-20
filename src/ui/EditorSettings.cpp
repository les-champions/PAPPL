#include "EditorSettings.h"
#include "MainWindow.h"
#include "PH.h"
#include "PHIO.h"
#include <QtGui>
#include "Area.h"


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
        if(myPHPtr->getGraphicsScene()->getGSort(s->getName())->GSort::isVisible())
            sort_Name->setChecked(true);
    }

    choiceBox = new QGroupBox("List of sorts");
    choiceBox->setLayout(groupLayout);

    selectAll=new QRadioButton("All");
    selectNone=new QRadioButton("None");

    connect(selectAll, SIGNAL(clicked()), this, SLOT(checkAll()));
    connect(selectNone, SIGNAL(clicked()), this, SLOT(checkNone()));

    checkLayout=new QHBoxLayout;
    selectAll=new QRadioButton("All");
    selectNone=new QRadioButton("None");
    checkLayout->addWidget(selectAll);
    checkLayout->addWidget(selectNone);


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

    void EditorSettings::quit(){

        this->~EditorSettings();
    }

    void EditorSettings::back(){
        QList<QString> listehidenSorts =getNonSelectedSorts();
        QList<QString> listeShownSorts =getSelectedSorts();

        for (QString &n: listeShownSorts){

            // show the QGraphicsItem representing the sort
            myPHPtr->getGraphicsScene()->getGSort(n.toStdString())->GSort::show();
            myPHPtr->getGraphicsScene()->getGSort(n.toStdString())->GSort::actionsShow();
      }

        for (QString &n: listehidenSorts){

            // Hide the QGraphicsItem representing the sort
            myPHPtr->getGraphicsScene()->getGSort(n.toStdString())->GSort::hide();
            myPHPtr->getGraphicsScene()->getGSort(n.toStdString())->GSort::actionsHide();
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


//    void EditorSettings::finish(){

//        QList<QString> selectedList =this->getSelectedSorts();
//        bool test=true;
//        if (selectedList.empty()) test=false;

//        //if no sort is selected , return a message error
//        if (test==false){
//            QMessageBox::critical(this, "Error", "At least one sort must be selected");
//        }
//        else{
//                QDialog* mb = new QDialog();
//                //Display loading window
//                mb->setWindowTitle("Please wait...");
//                mb->resize(300,150);
//                mb->show();
//                hideNonSelected();

//             sleep(2);
//             this->~EditorSettings();
//        }

//    }

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


    // method to export style and layout data to Tikz format
    void EditorSettings::generateTikz(){

        QList<QString> selectedList =this->getSelectedSorts();

        if(!selectedList.empty()){
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

    //Detroyer
    EditorSettings::~EditorSettings(){}

