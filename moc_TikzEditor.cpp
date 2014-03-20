/****************************************************************************
** Meta object code from reading C++ file 'TikzEditor.h'
**
** Created: Thu Mar 20 13:42:11 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/TikzEditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TikzEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TikzEditor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      22,   11,   11,   11, 0x08,
      40,   11,   11,   11, 0x08,
      47,   11,   11,   11, 0x08,
      62,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TikzEditor[] = {
    "TikzEditor\0\0onClear()\0checkUncheckAll()\0"
    "back()\0generateTikz()\0quit()\0"
};

void TikzEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TikzEditor *_t = static_cast<TikzEditor *>(_o);
        switch (_id) {
        case 0: _t->onClear(); break;
        case 1: _t->checkUncheckAll(); break;
        case 2: _t->back(); break;
        case 3: _t->generateTikz(); break;
        case 4: _t->quit(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData TikzEditor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TikzEditor::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TikzEditor,
      qt_meta_data_TikzEditor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TikzEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TikzEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TikzEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TikzEditor))
        return static_cast<void*>(const_cast< TikzEditor*>(this));
    return QDialog::qt_metacast(_clname);
}

int TikzEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
