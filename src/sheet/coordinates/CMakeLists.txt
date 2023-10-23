qt_add_library(Sheet STATIC
    Coordinates.h
    Area.h
    Address.h
    Position.h
    Coordinates.cpp
    Area.cpp
)

target_include_directories(Sheet INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})