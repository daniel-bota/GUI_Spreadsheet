/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#include <Table.h>


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_src_sheet_table()
{
    qmlRegisterTypesAndRevisions<CustomTableModel>("src.sheet.table", 1);
    qmlRegisterAnonymousType<QAbstractItemModel, 254>("src.sheet.table", 1);
    QMetaType::fromType<QAbstractTableModel *>().id();
    qmlRegisterModule("src.sheet.table", 1, 0);
}

static const QQmlModuleRegistration registration("src.sheet.table", qml_register_types_src_sheet_table);
