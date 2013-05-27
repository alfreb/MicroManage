/****************************************************************************
** Meta object code from reading C++ file 'qemuvm_popen.h'
**
** Created: Mon May 27 15:24:49 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qemuvm_popen.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qemuvm_popen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_qemuVm_popen[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_qemuVm_popen[] = {
    "qemuVm_popen\0\0bootConfirmed(qemuVm_popen*)\0"
    "firstByteRecieved()\0"
};

void qemuVm_popen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        qemuVm_popen *_t = static_cast<qemuVm_popen *>(_o);
        switch (_id) {
        case 0: _t->bootConfirmed((*reinterpret_cast< qemuVm_popen*(*)>(_a[1]))); break;
        case 1: _t->firstByteRecieved(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData qemuVm_popen::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject qemuVm_popen::staticMetaObject = {
    { &microMachine::staticMetaObject, qt_meta_stringdata_qemuVm_popen,
      qt_meta_data_qemuVm_popen, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &qemuVm_popen::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *qemuVm_popen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *qemuVm_popen::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_qemuVm_popen))
        return static_cast<void*>(const_cast< qemuVm_popen*>(this));
    return microMachine::qt_metacast(_clname);
}

int qemuVm_popen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = microMachine::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void qemuVm_popen::bootConfirmed(qemuVm_popen * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
