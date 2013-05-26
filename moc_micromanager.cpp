/****************************************************************************
** Meta object code from reading C++ file 'micromanager.h'
**
** Created: Sun May 26 15:12:31 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "micromanager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'micromanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_microManager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      27,   13,   13,   13, 0x05,
      46,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      53,   13,   13,   13, 0x0a,
      68,   66,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_microManager[] = {
    "microManager\0\0allStarted()\0"
    "bootConfirmedAll()\0exit()\0userPrompt()\0"
    "p\0bootConfirmed(qemuVm*)\0"
};

void microManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        microManager *_t = static_cast<microManager *>(_o);
        switch (_id) {
        case 0: _t->allStarted(); break;
        case 1: _t->bootConfirmedAll(); break;
        case 2: _t->exit(); break;
        case 3: _t->userPrompt(); break;
        case 4: _t->bootConfirmed((*reinterpret_cast< qemuVm*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData microManager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject microManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_microManager,
      qt_meta_data_microManager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &microManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *microManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *microManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_microManager))
        return static_cast<void*>(const_cast< microManager*>(this));
    return QObject::qt_metacast(_clname);
}

int microManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void microManager::allStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void microManager::bootConfirmedAll()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void microManager::exit()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
