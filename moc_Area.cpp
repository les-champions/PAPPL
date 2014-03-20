/****************************************************************************
** Meta object code from reading C++ file 'Area.h'
**
** Created: Thu Mar 20 11:46:52 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/Area.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Area.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Area[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x05,
      16,    5,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      30,    5,    5,    5, 0x0a,
      47,    5,    5,    5, 0x0a,
      68,    5,    5,    5, 0x0a,
      85,    5,    5,    5, 0x0a,
     102,   98,    5,    5, 0x0a,
     116,    5,    5,    5, 0x2a,
     127,    5,    5,    5, 0x0a,
     140,    5,    5,    5, 0x0a,
     153,    5,    5,    5, 0x0a,
     167,    5,    5,    5, 0x0a,
     181,    5,    5,    5, 0x0a,
     195,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Area[] = {
    "Area\0\0edition()\0makeTempXML()\0"
    "hideOrShowText()\0expandOrReduceText()\0"
    "hideOrShowTree()\0cancelEdit()\0del\0"
    "saveEdit(int)\0saveEdit()\0onTextEdit()\0"
    "setOldText()\0showToolTip()\0hideToolTip()\0"
    "tempXMLfile()\0deleteTempXML()\0"
};

void Area::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Area *_t = static_cast<Area *>(_o);
        switch (_id) {
        case 0: _t->edition(); break;
        case 1: _t->makeTempXML(); break;
        case 2: _t->hideOrShowText(); break;
        case 3: _t->expandOrReduceText(); break;
        case 4: _t->hideOrShowTree(); break;
        case 5: _t->cancelEdit(); break;
        case 6: _t->saveEdit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->saveEdit(); break;
        case 8: _t->onTextEdit(); break;
        case 9: _t->setOldText(); break;
        case 10: _t->showToolTip(); break;
        case 11: _t->hideToolTip(); break;
        case 12: _t->tempXMLfile(); break;
        case 13: _t->deleteTempXML(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Area::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Area::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Area,
      qt_meta_data_Area, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Area::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Area::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Area::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Area))
        return static_cast<void*>(const_cast< Area*>(this));
    return QWidget::qt_metacast(_clname);
}

int Area::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void Area::edition()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Area::makeTempXML()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
