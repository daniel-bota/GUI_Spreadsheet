cmake_minimum_required(VERSION 3.21.1)

project(GUI_Spreadsheet VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Gui)
qt_standard_project_setup(REQUIRES 6.5)

add_subdirectory(library)
add_subdirectory(src)
