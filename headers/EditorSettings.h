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
<<<<<<< HEAD
=======
    list<std::string> getSelectedSorts();
>>>>>>> master

private:


=======
    void hideNonSelected(QList<QString>,PHPtr );

private:

>>>>>>> 0857aebb2d538ff578b45dffe853d726f07d3120
    QWidget *widget;
    QGroupBox *choiceBox;
    QCheckBox *sort_Name;

<<<<<<< HEAD
<<<<<<< HEAD
    QRadioButton *sort_Name;
=======
    list<QCheckBox*>tabSorts;
>>>>>>> master
=======
    QList<QString> listehidenSorts;
    void getSelectedSorts();
>>>>>>> 0857aebb2d538ff578b45dffe853d726f07d3120

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
