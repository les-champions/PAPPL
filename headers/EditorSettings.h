#ifndef EDITORSETTINGS_H
#define EDITORSETTINGS_H
#include <iostream>
#include <QtGui>
#include <QGraphicsScene>
#include <map>
#include <string>
#include "GAction.h"


class EditorSettings : public QDialog
{
    Q_OBJECT

public:
    //constructor , destructor
    EditorSettings(PHPtr);
    ~EditorSettings();

private:


    //QWidget *editorWindow;


    QWidget *widget;
    QGroupBox *choiceBox;

    QRadioButton *sort_Name;

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
