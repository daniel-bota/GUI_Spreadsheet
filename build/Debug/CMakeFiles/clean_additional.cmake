# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "src\\app\\CMakeFiles\\GUI_Spreadsheet_autogen.dir\\AutogenUsed.txt"
  "src\\app\\CMakeFiles\\GUI_Spreadsheet_autogen.dir\\ParseCache.txt"
  "src\\app\\GUI_Spreadsheet_autogen"
  "src\\app\\customMenuBar\\CMakeFiles\\customMenuBar_autogen.dir\\AutogenUsed.txt"
  "src\\app\\customMenuBar\\CMakeFiles\\customMenuBar_autogen.dir\\ParseCache.txt"
  "src\\app\\customMenuBar\\CMakeFiles\\customMenuBarplugin_autogen.dir\\AutogenUsed.txt"
  "src\\app\\customMenuBar\\CMakeFiles\\customMenuBarplugin_autogen.dir\\ParseCache.txt"
  "src\\app\\customMenuBar\\customMenuBar_autogen"
  "src\\app\\customMenuBar\\customMenuBarplugin_autogen"
  "src\\sheet\\CMakeFiles\\Sheet_autogen.dir\\AutogenUsed.txt"
  "src\\sheet\\CMakeFiles\\Sheet_autogen.dir\\ParseCache.txt"
  "src\\sheet\\Sheet_autogen"
  "src\\sheet\\table\\CMakeFiles\\table_autogen.dir\\AutogenUsed.txt"
  "src\\sheet\\table\\CMakeFiles\\table_autogen.dir\\ParseCache.txt"
  "src\\sheet\\table\\CMakeFiles\\tableplugin_autogen.dir\\AutogenUsed.txt"
  "src\\sheet\\table\\CMakeFiles\\tableplugin_autogen.dir\\ParseCache.txt"
  "src\\sheet\\table\\table_autogen"
  "src\\sheet\\table\\tableplugin_autogen"
  "src\\utilities\\CMakeFiles\\Utilities_autogen.dir\\AutogenUsed.txt"
  "src\\utilities\\CMakeFiles\\Utilities_autogen.dir\\ParseCache.txt"
  "src\\utilities\\Utilities_autogen"
  )
endif()
