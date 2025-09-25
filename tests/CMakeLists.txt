cmake_minimum_required(VERSION 3.15)
project(CppErrorsTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
    
find_package(GTest CONFIG REQUIRED)

add_executable(${PROJECT_NAME} errors_tests.cpp)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
    GTest::gtest 
    GTest::gtest_main
)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    OUTPUT_NAME "cpp_errors_tests"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests
)

# Include errors directory
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../errors)