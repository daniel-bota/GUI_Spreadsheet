add_subdirectory(
    cell
    coordinates
    table
)

qt_add_library(Sheet STATIC
    Sheet.h
    Sheet.cpp
)

target_include_directories(Sheet INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})