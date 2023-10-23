qt_add_executable(GUI_Spreadsheet
    Main.cpp
)

qt_add_qml_module(GUI_Spreadsheet
    URI app
    QML_FILES
        Main.qml
)

qt_add_qml_module(menuBar
    URI gui.menuBar
    VERSION 1.0
    QML_FILES
        FileMenu.qml
)

target_link_libraries(GUI_Spreadsheet PRIVATE NLohmannJson Qt6::Gui Qt6::Quick)