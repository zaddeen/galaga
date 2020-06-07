add_library(catch
        src/catch.h
        src/catch-main.cpp)
set_property(TARGET catch PROPERTY CXX_STANDARD 14)
set_property(TARGET catch PROPERTY CXX_STANDARD_REQUIRED On)
set_property(TARGET catch PROPERTY CXX_EXTENSIONS OFF)
target_include_directories(catch SYSTEM INTERFACE src)
target_include_directories(catch PRIVATE src)
