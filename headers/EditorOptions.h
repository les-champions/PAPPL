#ifndef EDITOROPTIONS_H
#define EDITOROPTIONS_H

#include <iostream>
#include <QtGui>
#include <QGraphicsScene>
#include <map>
#include <string>
#include "GAction.h"


class EditorOptions : public QDialog
{
    Q_OBJECT

public:
    //constructor , destructor
     EditorOptions();
    ~EditorOptions();


private:

    QHBoxLayout *btnLayout;
    QVBoxLayout *globalLayout;
    //button
    QPushButton *Generate;
    QPushButton *Cancel;
    QPushButton *Next;


};


#endif // EDITOROPTIONS_H
