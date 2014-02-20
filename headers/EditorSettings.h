#ifndef EDITORSETTINGS_H
#define EDITORSETTINGS_H
#include <iostream>
#include <QtGui>
#include <QGraphicsScene>
#include <map>
#include <string>
#include "GAction.h"
<<<<<<< HEAD

=======
>>>>>>> master

class EditorSettings : public QDialog
{
    Q_OBJECT

public:
    //constructor , destructor
    EditorSettings(PHPtr);
    ~EditorSettings();
<<<<<<< HEAD
=======
    list<std::string> getSelectedSorts();
>>>>>>> master

private:


    QWidget *widget;
    QGroupBox *choiceBox;
    QCheckBox *sort_Name;

<<<<<<< HEAD
    QRadioButton *sort_Name;
=======
    list<QCheckBox*>tabSorts;
>>>>>>> master

    //Mise en page générale
    QVBoxLayout *globalLayout;
    QVBoxLayout *layoutTotal;
    QVBoxLayout *groupLayout;
    QHBoxLayout *btnLayout;

    //button
    QPushButton *Generate;
    QPushButton *Annuler;
    QPushButton *Edit;

    QScrollArea *area;



};

#endif // EDITORSETTINGS_H
