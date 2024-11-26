/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../main/include/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "showUserInfo",
    "",
    "onTabChanged",
    "index",
    "on_actionopen_triggered",
    "on_actionsave_triggered",
    "on_actionclose_triggered",
    "on_actiondownload_triggered",
    "handleFileDownload",
    "fileName",
    "fileContent",
    "on_actionscv_file_triggered",
    "on_actiontxt_file_triggered",
    "on_actionadd_triggered",
    "on_actionsub_triggered",
    "on_actiondel_row_triggered",
    "on_actiondel_col_triggered",
    "handleFilePathSent",
    "openFile",
    "filePath",
    "on_actionshe_triggered",
    "showUserInfoDialog",
    "receiveSendEmailForm",
    "SendEmail*",
    "form"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  122,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    1,  123,    2, 0x0a,    2 /* Public */,
       5,    0,  126,    2, 0x08,    4 /* Private */,
       6,    0,  127,    2, 0x08,    5 /* Private */,
       7,    0,  128,    2, 0x08,    6 /* Private */,
       8,    0,  129,    2, 0x08,    7 /* Private */,
       9,    2,  130,    2, 0x08,    8 /* Private */,
      12,    0,  135,    2, 0x08,   11 /* Private */,
      13,    0,  136,    2, 0x08,   12 /* Private */,
      14,    0,  137,    2, 0x08,   13 /* Private */,
      15,    0,  138,    2, 0x08,   14 /* Private */,
      16,    0,  139,    2, 0x08,   15 /* Private */,
      17,    0,  140,    2, 0x08,   16 /* Private */,
      18,    0,  141,    2, 0x08,   17 /* Private */,
      19,    1,  142,    2, 0x08,   18 /* Private */,
      21,    0,  145,    2, 0x08,   20 /* Private */,
      22,    0,  146,    2, 0x08,   21 /* Private */,
      23,    1,  147,    2, 0x08,   22 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,   10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 24,   25,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'showUserInfo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onTabChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_actionopen_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionsave_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionclose_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actiondownload_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleFileDownload'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>,
        // method 'on_actionscv_file_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actiontxt_file_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionadd_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionsub_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actiondel_row_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actiondel_col_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleFilePathSent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_actionshe_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showUserInfoDialog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'receiveSendEmailForm'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<SendEmail *, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->showUserInfo(); break;
        case 1: _t->onTabChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->on_actionopen_triggered(); break;
        case 3: _t->on_actionsave_triggered(); break;
        case 4: _t->on_actionclose_triggered(); break;
        case 5: _t->on_actiondownload_triggered(); break;
        case 6: _t->handleFileDownload((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[2]))); break;
        case 7: _t->on_actionscv_file_triggered(); break;
        case 8: _t->on_actiontxt_file_triggered(); break;
        case 9: _t->on_actionadd_triggered(); break;
        case 10: _t->on_actionsub_triggered(); break;
        case 11: _t->on_actiondel_row_triggered(); break;
        case 12: _t->on_actiondel_col_triggered(); break;
        case 13: _t->handleFilePathSent(); break;
        case 14: _t->openFile((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 15: _t->on_actionshe_triggered(); break;
        case 16: _t->showUserInfoDialog(); break;
        case 17: _t->receiveSendEmailForm((*reinterpret_cast< std::add_pointer_t<SendEmail*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< SendEmail* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)();
            if (_t _q_method = &MainWindow::showUserInfo; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::showUserInfo()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
