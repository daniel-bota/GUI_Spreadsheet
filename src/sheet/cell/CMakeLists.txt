target_sources(Sheet PUBLIC
    Cell.h
    NumericCell.h
    TextCell.h
    FormulaCell.h
    Formula.h
    Cell.cpp
    NumericCell.cpp
    TextCell.cpp
    FormulaCell.cpp
    Formula.cpp
)

target_include_directories(Sheet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
