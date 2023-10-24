qt_add_library(Sheet STATIC
    Sheet.h
    Sheet.cpp
)

target_include_directories(Sheet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Sheet PUBLIC NLohmannJson Qt6::Gui Qt6::Quick Utilities)

add_subdirectory(cell)
add_subdirectory(coordinates)
add_subdirectory(table)
