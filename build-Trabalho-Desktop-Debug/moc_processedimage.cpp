/****************************************************************************
** Meta object code from reading C++ file 'processedimage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Trabalho1/imagewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'processedimage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ImageWindow_t {
    QByteArrayData data[10];
    char stringdata0[96];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageWindow_t qt_meta_stringdata_ImageWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ImageWindow"
QT_MOC_LITERAL(1, 12, 12), // "verticalFlip"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 14), // "horizontalFlip"
QT_MOC_LITERAL(4, 41, 9), // "greyScale"
QT_MOC_LITERAL(5, 51, 12), // "quantization"
QT_MOC_LITERAL(6, 64, 5), // "quant"
QT_MOC_LITERAL(7, 70, 9), // "loadImage"
QT_MOC_LITERAL(8, 80, 5), // "char*"
QT_MOC_LITERAL(9, 86, 9) // "saveImage"

    },
    "ImageWindow\0verticalFlip\0\0horizontalFlip\0"
    "greyScale\0quantization\0quant\0loadImage\0"
    "char*\0saveImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    1,   47,    2, 0x0a /* Public */,
       7,    1,   50,    2, 0x0a /* Public */,
       9,    1,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Int, 0x80000000 | 8,    2,
    QMetaType::Int, 0x80000000 | 8,    2,

       0        // eod
};

void ImageWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImageWindow *_t = static_cast<ImageWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->verticalFlip(); break;
        case 1: _t->horizontalFlip(); break;
        case 2: _t->greyScale(); break;
        case 3: _t->quantization((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: { int _r = _t->loadImage((*reinterpret_cast< char*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 5: { int _r = _t->saveImage((*reinterpret_cast< char*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject ImageWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ImageWindow.data,
      qt_meta_data_ImageWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ImageWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ImageWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ImageWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE