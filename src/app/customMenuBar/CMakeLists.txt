qt_add_qml_module(customMenuBar
    URI app.customMenuBar
    VERSION 1.0
###    RESOURCE_PREFIX qt/qml
    QML_FILES
        FileMenu.qml
)

set(QML_IMPORT_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE STRING "" FORCE)
