#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QAbstractTableModel>

#include "Resources/Table/headers.h"
#include "Resources/Table/table.h"
#include "Resources/UI/fileio.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<HeadersModel> ("SheetModel", 1, 0, "HeadersModel");
    qmlRegisterType<CustomTableModel> ("SheetModel", 1, 1, "CustomTableModel");
    qmlRegisterType<FileIO> ("UI", 1, 0, "FileIO");

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Spreadsheet_GUI", "Main");

    return app.exec();
}
