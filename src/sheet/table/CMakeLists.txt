target_sources(Sheet PUBLIC
    Headers.h
    Headers.cpp
    Table.h
    Table.cpp
)

target_include_directories(Sheet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

qt_add_qml_module(table
    URI sheet.table
    VERSION 1.0
    QML_FILES
        ColumnHeaders.qml
        RowHeaders.qml
        SheetTable.qml
)
