cmake_minimum_required(VERSION 3.3)
project(final-project CXX)
include(.eecs211/cmake/CMakeLists.txt)

set(MODEL_SRC
        # LIST ADDITIONAL MODEL .cpp FILES HERE
        src/model.cpp)

add_program(main
    src/main.cpp
        src/view.cpp
    # LIST ADDITIONAL NON-MODEL (UI) .cpp FILES HERE
    ${MODEL_SRC})
target_link_libraries(main ge211)

add_test_program(model_test
    test/model_test.cpp
    ${MODEL_SRC})
target_link_libraries(model_test ge211)
