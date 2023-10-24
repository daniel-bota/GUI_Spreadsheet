/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#include <FileIO.h>


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_src_io()
{
    qmlRegisterTypesAndRevisions<FileIO>("src.io", 1);
    qmlRegisterModule("src.io", 1, 0);
}

static const QQmlModuleRegistration registration("src.io", qml_register_types_src_io);
