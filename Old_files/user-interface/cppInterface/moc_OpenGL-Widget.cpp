/****************************************************************************
** Meta object code from reading C++ file 'OpenGL-Widget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "OpenGL-Widget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OpenGL-Widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_glWidgetConsole[] = {

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
      28,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      63,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_glWidgetConsole[] = {
    "glWidgetConsole\0\0text,r,g,b\0"
    "sendGLMessage(QString,int,int,int)\0"
    "updateGL()\0"
};

void glWidgetConsole::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        glWidgetConsole *_t = static_cast<glWidgetConsole *>(_o);
        switch (_id) {
        case 0: _t->sendGLMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: _t->updateGL(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData glWidgetConsole::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject glWidgetConsole::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_glWidgetConsole,
      qt_meta_data_glWidgetConsole, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &glWidgetConsole::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *glWidgetConsole::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *glWidgetConsole::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_glWidgetConsole))
        return static_cast<void*>(const_cast< glWidgetConsole*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int glWidgetConsole::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
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
void glWidgetConsole::sendGLMessage(const QString & _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
