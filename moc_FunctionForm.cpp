/****************************************************************************
** Meta object code from reading C++ file 'FunctionForm.h'
**
** Created: Fri Mar 21 23:28:53 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/FunctionForm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FunctionForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FunctionForm[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      35,   13,   13,   13, 0x08,
      42,   13,   13,   13, 0x08,
      52,   13,   13,   13, 0x08,
      74,   68,   13,   13, 0x08,
      90,   13,   13,   13, 0x08,
     102,   13,   13,   13, 0x08,
     112,   13,   13,   13, 0x08,
     131,   13,   13,   13, 0x08,
     165,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FunctionForm[] = {
    "FunctionForm\0\0openConnectionForm()\0"
    "quit()\0fctBack()\0launchCompute()\0state\0"
    "enableForm(int)\0getNamePH()\0getName()\0"
    "getDirectoryName()\0getDirectoryNameFileNotExisting()\0"
    "testEmpty()\0"
};

void FunctionForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FunctionForm *_t = static_cast<FunctionForm *>(_o);
        switch (_id) {
        case 0: _t->openConnectionForm(); break;
        case 1: _t->quit(); break;
        case 2: _t->fctBack(); break;
        case 3: _t->launchCompute(); break;
        case 4: _t->enableForm((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->getNamePH(); break;
        case 6: _t->getName(); break;
        case 7: _t->getDirectoryName(); break;
        case 8: _t->getDirectoryNameFileNotExisting(); break;
        case 9: _t->testEmpty(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FunctionForm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FunctionForm::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FunctionForm,
      qt_meta_data_FunctionForm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FunctionForm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FunctionForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FunctionForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FunctionForm))
        return static_cast<void*>(const_cast< FunctionForm*>(this));
    return QDialog::qt_metacast(_clname);
}

int FunctionForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
