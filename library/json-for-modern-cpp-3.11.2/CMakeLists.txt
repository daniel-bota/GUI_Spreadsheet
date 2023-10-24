qt_add_library(NLohmannJson INTERFACE
    nlohmann/json.hpp
)

target_include_directories(NLohmannJson INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
