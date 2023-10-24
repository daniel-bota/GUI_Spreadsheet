#target_sources(Sheet PUBLIC
#    Headers.h
#    Headers.cpp
#    Table.h
#    Table.cpp
#)

#target_include_directories(Sheet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

qt_add_library(Table STATIC)

qt_add_qml_module(Table
    URI src.sheet.table
    VERSION 1.0
    QML_FILES
        ColumnHeaders.qml
        RowHeaders.qml
        SheetTable.qml
    SOURCES
        Headers.h
        Headers.cpp
        Table.h
        Table.cpp
)

target_link_libraries(Table PRIVATE Sheet)
