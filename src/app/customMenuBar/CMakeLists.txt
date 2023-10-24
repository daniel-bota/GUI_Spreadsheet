qt_add_library(CustomMenuBar STATIC)

qt_add_qml_module(CustomMenuBar
    URI src.app.customMenuBar
    VERSION 1.0
#    RESOURCE_PREFIX src/app/
    QML_FILES
        FileMenu.qml
)

target_link_libraries(CustomMenuBar PRIVATE FileIOplugin)

### set(QML_IMPORT_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE STRING "" FORCE)
