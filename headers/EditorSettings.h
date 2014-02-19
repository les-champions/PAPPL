#ifndef EDITORSETTINGS_H
#define EDITORSETTINGS_H
#include <iostream>
#include <QtGui>

class EditorSettings : public QDialog
{
    Q_OBJECT

public:
    //constructor , destructor
    EditorSettings();
    ~EditorSettings();


private:


    //QWidget *editorWindow;


    QWidget *widget;
    QGroupBox *choiceBox;

    QRadioButton *ch1;
    QRadioButton *ch2;

    //Mise en page générale
    QVBoxLayout *globalLayout;
    QVBoxLayout *layoutTotal;
    QVBoxLayout *groupLayout;
    QHBoxLayout *btnLayout;

    //button
    QPushButton *Generate;
    QPushButton *Cancel;
    QPushButton *Edit;

    QScrollArea *area;

};

#endif // EDITORSETTINGS_H
