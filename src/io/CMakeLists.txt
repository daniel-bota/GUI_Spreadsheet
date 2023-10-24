target_sources(GUI_Spreadsheet PUBLIC
    FileIO.h
    FileIO.cpp
)

target_include_directories(GUI_Spreadsheet PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
