target_sources(Sheet PUBLIC
    Coordinates.h
    Area.h
    Address.h
    Position.h
    Coordinates.cpp
    Area.cpp
)

target_include_directories(Sheet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
