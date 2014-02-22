/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created: Sat Feb 22 19:20:54 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/MainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   11,   12,   11, 0x0a,
      30,   11,   11,   11, 0x0a,
      37,   11,   11,   11, 0x0a,
      48,   11,   11,   11, 0x0a,
      60,   11,   11,   11, 0x0a,
      72,   11,   11,   11, 0x0a,
      85,   11,   11,   11, 0x0a,
     113,  105,   11,   11, 0x0a,
     140,   11,   11,   11, 0x2a,
     160,   11,   11,   11, 0x0a,
     169,   11,   11,   11, 0x0a,
     178,   11,   11,   11, 0x0a,
     188,   11,   11,   11, 0x0a,
     214,   11,   11,   11, 0x0a,
     239,   11,   11,   11, 0x0a,
     263,   11,   11,   11, 0x0a,
     281,   11,   11,   11, 0x0a,
     300,   11,   11,   11, 0x0a,
     319,   11,   11,   11, 0x0a,
     332,   11,   11,   11, 0x0a,
     347,   11,   11,   11, 0x0a,
     375,   11,   11,   11, 0x0a,
     390,   11,   11,   11, 0x0a,
     406,   11,   11,   11, 0x0a,
     428,   11,   11,   11, 0x0a,
     443,   11,   11,   11, 0x0a,
     469,   11,   11,   11, 0x0a,
     486,   11,   11,   11, 0x0a,
     509,  499,   11,   11, 0x0a,
     537,   11,   11,   11, 0x0a,
     550,   11,   11,   11, 0x0a,
     567,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0MyArea*\0openTab()\0save()\0"
    "closeTab()\0exportPng()\0exportDot()\0"
    "openEditor()\0exportXMLMetadata()\0"
    "tempXML\0importXMLMetadata(QString)\0"
    "importXMLMetadata()\0adjust()\0zoomIn()\0"
    "zoomOut()\0switchToSimplifiedModel()\0"
    "switchToDetailledModel()\0"
    "changeBackgroundColor()\0changeSortColor()\0"
    "positiveContrast()\0negativeContrast()\0"
    "printStyle()\0hideShowText()\0"
    "changeTextBackgroundColor()\0hideShowTree()\0"
    "findFixpoints()\0computeReachability()\0"
    "EditTikzData()\0runStochasticSimulation()\0"
    "checkModelType()\0statistics()\0subWindow\0"
    "disableMenu(QMdiSubWindow*)\0searchSort()\0"
    "openConnection()\0openConnectionForm()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: { MyArea* _r = _t->openTab();
            if (_a[0]) *reinterpret_cast< MyArea**>(_a[0]) = _r; }  break;
        case 1: _t->save(); break;
        case 2: _t->closeTab(); break;
        case 3: _t->exportPng(); break;
        case 4: _t->exportDot(); break;
        case 5: _t->openEditor(); break;
        case 6: _t->exportXMLMetadata(); break;
        case 7: _t->importXMLMetadata((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->importXMLMetadata(); break;
        case 9: _t->adjust(); break;
        case 10: _t->zoomIn(); break;
        case 11: _t->zoomOut(); break;
        case 12: _t->switchToSimplifiedModel(); break;
        case 13: _t->switchToDetailledModel(); break;
        case 14: _t->changeBackgroundColor(); break;
        case 15: _t->changeSortColor(); break;
        case 16: _t->positiveContrast(); break;
        case 17: _t->negativeContrast(); break;
        case 18: _t->printStyle(); break;
        case 19: _t->hideShowText(); break;
        case 20: _t->changeTextBackgroundColor(); break;
        case 21: _t->hideShowTree(); break;
        case 22: _t->findFixpoints(); break;
        case 23: _t->computeReachability(); break;
        //case 24: _t->EditTikzData(); break;
        case 25: _t->runStochasticSimulation(); break;
        case 26: _t->checkModelType(); break;
        case 27: _t->statistics(); break;
        case 28: _t->disableMenu((*reinterpret_cast< QMdiSubWindow*(*)>(_a[1]))); break;
        case 29: _t->searchSort(); break;
        case 30: _t->openConnection(); break;
        case 31: _t->openConnectionForm(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
