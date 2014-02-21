#ifndef EDITORSETTINGS_H
#define EDITORSETTINGS_H
#include <iostream>
#include <QtGui>
#include <QGraphicsScene>
#include <map>
#include <string>
#include "GAction.h"
#include "EditorOptions.h"


class EditorSettings : public QDialog
{
    Q_OBJECT

public:
    //constructor , destructor
    EditorSettings(PHPtr);
    ~EditorSettings();
    PHPtr myPHPtr;
    //get the list of selected sort name
    QList<QString> getSelectedSorts();

private:
    QList <QCheckBox*> listOfSorts;

    QWidget *widget;
    QGroupBox *choiceBox;
    QCheckBox *sort_Name;

    //liste des sortes
    list<QCheckBox*>tabSorts;

    //
    QRadioButton *selectAll;
    QRadioButton *selectNone;

    //Mise en page générale
    QVBoxLayout *globalLayout;

    QVBoxLayout *layoutTotal;
    QVBoxLayout *groupLayout;
    QHBoxLayout *btnLayout;
    QHBoxLayout *checkLayout;

    //button
    QPushButton *Generate;
    QPushButton *Cancel;
    QPushButton *Next;

    //scroll
    QScrollArea *area;

    void hideNonSelected();

private slots:

    void checkAll();
    void checkNone();
    void next();
    void quit();
    //ToDo : implement
    void generate();

protected:
    EditorOptions* EditorOptionsWindow;

};

#endif // EDITORSETTINGS_H
