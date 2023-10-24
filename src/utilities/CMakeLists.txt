qt_add_library(Utilities STATIC
    StringUtility.h
    StringUtility.cpp
)

target_include_directories(Utilities INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})