/****************************************************************************
** Meta object code from reading C++ file 'TreeArea.h'
**
** Created: Thu Mar 20 01:51:10 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/TreeArea.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TreeArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TreeArea[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      18,    9,    9,    9, 0x0a,
      31,    9,    9,    9, 0x0a,
      46,    9,    9,    9, 0x0a,
      57,    9,    9,    9, 0x0a,
      66,    9,    9,    9, 0x0a,
      83,   79,    9,    9, 0x0a,
     120,  108,    9,    9, 0x0a,
     134,  108,    9,    9, 0x0a,
     148,  108,    9,    9, 0x0a,
     171,  169,    9,    9, 0x0a,
     217,   79,    9,    9, 0x0a,
     243,    9,    9,    9, 0x0a,
     255,    9,    9,    9, 0x0a,
     267,    9,    9,    9, 0x0a,
     286,    9,    9,    9, 0x0a,
     312,    9,    9,    9, 0x0a,
     338,    9,    9,    9, 0x0a,
     371,    9,    9,    9, 0x0a,
     398,    9,    9,    9, 0x0a,
     425,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TreeArea[] = {
    "TreeArea\0\0build()\0searchSort()\0"
    "cancelSearch()\0addGroup()\0remove()\0"
    "addToGroup()\0pos\0sortsItemClicked(QPoint)\0"
    "clickedTree\0hideSort(int)\0showSort(int)\0"
    "changeSortColor(int)\0,\0"
    "changeSortRectColor(QTreeWidgetItem*,QColor*)\0"
    "groupsItemClicked(QPoint)\0hideGroup()\0"
    "showGroup()\0changeGroupColor()\0"
    "hideSortClickedFromSort()\0"
    "showSortClickedFromSort()\0"
    "changeSortColorClickedFromSort()\0"
    "hideSortClickedFromGroup()\0"
    "showSortClickedFromGroup()\0"
    "changeSortColorClickedFromGroup()\0"
};

void TreeArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TreeArea *_t = static_cast<TreeArea *>(_o);
        switch (_id) {
        case 0: _t->build(); break;
        case 1: _t->searchSort(); break;
        case 2: _t->cancelSearch(); break;
        case 3: _t->addGroup(); break;
        case 4: _t->remove(); break;
        case 5: _t->addToGroup(); break;
        case 6: _t->sortsItemClicked((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 7: _t->hideSort((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->showSort((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->changeSortColor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->changeSortRectColor((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QColor*(*)>(_a[2]))); break;
        case 11: _t->groupsItemClicked((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 12: _t->hideGroup(); break;
        case 13: _t->showGroup(); break;
        case 14: _t->changeGroupColor(); break;
        case 15: _t->hideSortClickedFromSort(); break;
        case 16: _t->showSortClickedFromSort(); break;
        case 17: _t->changeSortColorClickedFromSort(); break;
        case 18: _t->hideSortClickedFromGroup(); break;
        case 19: _t->showSortClickedFromGroup(); break;
        case 20: _t->changeSortColorClickedFromGroup(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TreeArea::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TreeArea::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TreeArea,
      qt_meta_data_TreeArea, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TreeArea::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TreeArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TreeArea::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TreeArea))
        return static_cast<void*>(const_cast< TreeArea*>(this));
    return QWidget::qt_metacast(_clname);
}

int TreeArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
