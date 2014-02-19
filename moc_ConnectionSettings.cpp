/****************************************************************************
** Meta object code from reading C++ file 'ConnectionSettings.h'
**
** Created: Wed Feb 19 20:39:14 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/ConnectionSettings.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConnectionSettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ConnectionSettings[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,
      33,   19,   19,   19, 0x08,
      40,   19,   19,   19, 0x08,
      60,   19,   19,   19, 0x08,
      91,   19,   19,   19, 0x08,
     110,   19,   19,   19, 0x08,
     124,   19,   19,   19, 0x08,
     138,   19,   19,   19, 0x08,
     150,   19,   19,   19, 0x08,
     180,  174,   19,   19, 0x08,
     199,   19,   19,   19, 0x08,
     212,  174,   19,   19, 0x08,
     239,  234,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ConnectionSettings[] = {
    "ConnectionSettings\0\0buildTable()\0"
    "quit()\0exportXMLSettings()\0"
    "validationConnectionSettings()\0"
    "testFunctionName()\0testProgram()\0"
    "testOutline()\0testChoix()\0"
    "testNecessaryArgument()\0param\0"
    "choixCrea(QString)\0buildChoix()\0"
    "setEnability(QString)\0text\0"
    "prefixMaj(QString)\0"
};

void ConnectionSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ConnectionSettings *_t = static_cast<ConnectionSettings *>(_o);
        switch (_id) {
        case 0: _t->buildTable(); break;
        case 1: _t->quit(); break;
        case 2: _t->exportXMLSettings(); break;
        case 3: _t->validationConnectionSettings(); break;
        case 4: _t->testFunctionName(); break;
        case 5: _t->testProgram(); break;
        case 6: _t->testOutline(); break;
        case 7: _t->testChoix(); break;
        case 8: _t->testNecessaryArgument(); break;
        case 9: _t->choixCrea((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->buildChoix(); break;
        case 11: _t->setEnability((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->prefixMaj((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ConnectionSettings::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ConnectionSettings::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ConnectionSettings,
      qt_meta_data_ConnectionSettings, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ConnectionSettings::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ConnectionSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ConnectionSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConnectionSettings))
        return static_cast<void*>(const_cast< ConnectionSettings*>(this));
    return QDialog::qt_metacast(_clname);
}

int ConnectionSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
