cmake_minimum_required(VERSION 3.16)

project(Spreadsheet_GUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 23)

set(JSON_Install OFF CACHE INTERNAL "")

add_subdirectory(Resources/nlohmann_json)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS QuickControls2)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appSpreadsheet_GUI
    main.cpp
    Resources/Table/headers.h
    Resources/Table/headers.cpp
    Resources/Table/table.h
    Resources/Table/table.cpp
    Resources/UI/fileio.h
    Resources/UI/fileio.cpp
    Resources/Sheet/Sheet.h
    Resources/Sheet/Sheet.cpp
    Resources/Sheet/Misc/Misc.h
    Resources/Sheet/Misc/Misc.cpp
    Resources/Sheet/Coordinates/Coordinates.h
    Resources/Sheet/Coordinates/Coordinates.cpp
    Resources/Sheet/Coordinates/Address.h
    Resources/Sheet/Coordinates/Area.h
    Resources/Sheet/Coordinates/Area.cpp
    Resources/Sheet/Coordinates/Position.h
    Resources/Sheet/Cell/Cell.h
    Resources/Sheet/Cell/Cell.cpp
    Resources/Sheet/Cell/TextCell.h
    Resources/Sheet/Cell/TextCell.cpp
    Resources/Sheet/Cell/NumericCell.h
    Resources/Sheet/Cell/NumericCell.cpp
    Resources/Sheet/Cell/FormulaCell.h
    Resources/Sheet/Cell/FormulaCell.cpp
    Resources/Sheet/Cell/Formula.h
    Resources/Sheet/Cell/Formula.cpp
)

qt_add_qml_module(appSpreadsheet_GUI
    URI Spreadsheet_GUI
    VERSION 1.0
    QML_FILES
        Main.qml
        Resources/CustomMenuBar/FileMenu.qml
        Resources/Table/ColumnHeaders.qml
        Resources/Table/RowHeaders.qml
        Resources/Table/SheetTable.qml
)

set_target_properties(appSpreadsheet_GUI PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSpreadsheet_GUI PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(appSpreadsheet_GUI PRIVATE Qt6::Quick)
target_link_libraries(appSpreadsheet_GUI PRIVATE Qt6::QuickControls2)

install(TARGETS appSpreadsheet_GUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
