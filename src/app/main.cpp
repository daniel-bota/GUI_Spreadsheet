#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QAbstractTableModel>

#include "Headers.h"
#include "Table.h"
#include "FileIO.h"

int main(int argc, char *argv[])
{
    //    QGuiApplication app(argc, argv);

    //    qmlRegisterType<HeadersModel> ("SheetModel", 1, 0, "HeadersModel");
    //    qmlRegisterType<CustomTableModel> ("SheetModel", 1, 1, "CustomTableModel");
    //    qmlRegisterType<FileIO> ("UI", 1, 0, "FileIO");

    //    QQmlApplicationEngine engine;
    //    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
    //        &app, []() { QCoreApplication::exit(-1); },
    //        Qt::QueuedConnection);
    //    engine.loadFromModule("GUI_Spreadsheet", "Main");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/qt/qml/app");
    auto pathList = engine.importPathList();

    const QUrl url(u"qrc:qt/qml/app/Main.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
