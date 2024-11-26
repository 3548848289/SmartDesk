/****************************************************************************
** Meta object code from reading C++ file 'server.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../email/simple-mail/src/server.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'server.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSSimpleMailSCOPEServerENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSSimpleMailSCOPEServerENDCLASS = QtMocHelpers::stringData(
    "SimpleMail::Server",
    "smtpError",
    "",
    "SmtpError",
    "e",
    "description",
    "sslErrors",
    "QList<QSslError>",
    "sslErrorList",
    "AuthMethod",
    "AuthNone",
    "AuthPlain",
    "AuthLogin",
    "AuthCramMd5",
    "ConnectionTimeoutError",
    "ResponseTimeoutError",
    "SendDataTimeoutError",
    "AuthenticationFailedError",
    "ServerError",
    "ClientError",
    "ConnectionType",
    "TcpConnection",
    "SslConnection",
    "TlsConnection",
    "PeerVerificationType",
    "VerifyNone",
    "VerifyPeer"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSimpleMailSCOPEServerENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       4,   34, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   26,    2, 0x06,    5 /* Public */,
       6,    1,   31,    2, 0x06,    8 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

 // enums: name, alias, flags, count, data
       9,    9, 0x0,    4,   54,
       3,    3, 0x0,    6,   62,
      20,   20, 0x0,    3,   74,
      24,   24, 0x0,    2,   80,

 // enum data: key, value
      10, uint(SimpleMail::Server::AuthNone),
      11, uint(SimpleMail::Server::AuthPlain),
      12, uint(SimpleMail::Server::AuthLogin),
      13, uint(SimpleMail::Server::AuthCramMd5),
      14, uint(SimpleMail::Server::ConnectionTimeoutError),
      15, uint(SimpleMail::Server::ResponseTimeoutError),
      16, uint(SimpleMail::Server::SendDataTimeoutError),
      17, uint(SimpleMail::Server::AuthenticationFailedError),
      18, uint(SimpleMail::Server::ServerError),
      19, uint(SimpleMail::Server::ClientError),
      21, uint(SimpleMail::Server::TcpConnection),
      22, uint(SimpleMail::Server::SslConnection),
      23, uint(SimpleMail::Server::TlsConnection),
      25, uint(SimpleMail::Server::VerifyNone),
      26, uint(SimpleMail::Server::VerifyPeer),

       0        // eod
};

Q_CONSTINIT const QMetaObject SimpleMail::Server::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSSimpleMailSCOPEServerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSimpleMailSCOPEServerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSimpleMailSCOPEServerENDCLASS_t,
        // enum 'AuthMethod'
        QtPrivate::TypeAndForceComplete<Server::AuthMethod, std::true_type>,
        // enum 'SmtpError'
        QtPrivate::TypeAndForceComplete<Server::SmtpError, std::true_type>,
        // enum 'ConnectionType'
        QtPrivate::TypeAndForceComplete<Server::ConnectionType, std::true_type>,
        // enum 'PeerVerificationType'
        QtPrivate::TypeAndForceComplete<Server::PeerVerificationType, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Server, std::true_type>,
        // method 'smtpError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<SmtpError, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'sslErrors'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QSslError> &, std::false_type>
    >,
    nullptr
} };

void SimpleMail::Server::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Server *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->smtpError((*reinterpret_cast< std::add_pointer_t<SmtpError>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->sslErrors((*reinterpret_cast< std::add_pointer_t<QList<QSslError>>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Server::*)(SmtpError , const QString & );
            if (_t _q_method = &Server::smtpError; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Server::*)(const QList<QSslError> & );
            if (_t _q_method = &Server::sslErrors; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *SimpleMail::Server::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SimpleMail::Server::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSimpleMailSCOPEServerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SimpleMail::Server::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void SimpleMail::Server::smtpError(SmtpError _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SimpleMail::Server::sslErrors(const QList<QSslError> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
