cmake_minimum_required (VERSION 3.10...3.22)

project (test_shapes LANGUAGES CXX)

add_executable(testsh test_shapes.cpp)

target_include_directories(testsh
    PRIVATE 
        "../benchmark/include"
        "../variant/include"
)

target_link_directories(testsh
    PRIVATE
        "../benchmark/build/src"
)

target_link_libraries(testsh
    PRIVATE
        benchmark  benchmark_main
)