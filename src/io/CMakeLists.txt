#target_sources(GUI_Spreadsheet PUBLIC
#    FileIO.h
#    FileIO.cpp
#)

#target_include_directories(GUI_Spreadsheet PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

qt_add_library(FileIO STATIC)

qt_add_qml_module(FileIO
    URI src.io
    VERSION 1.0
#    RESOURCE_PREFIX src/app/
    SOURCES
        FileIO.h
        FileIO.cpp
)

target_link_libraries(FileIO PRIVATE NLohmannJson)
