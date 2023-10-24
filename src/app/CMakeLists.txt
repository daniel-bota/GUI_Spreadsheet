add_subdirectory(customMenuBar)

qt_add_executable(GUI_Spreadsheet
    Main.cpp
)

qt_add_qml_module(GUI_Spreadsheet
    URI src.app
    VERSION 1.0
#    RESOURCE_PREFIX "/src/"
    QML_FILES
        Main.qml
)

target_link_libraries(GUI_Spreadsheet PRIVATE
    NLohmannJson
    Sheet
    CustomMenuBarplugin
    Tableplugin
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick)
