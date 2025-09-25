cmake_minimum_required(VERSION 3.15)
project(CppErrorsExamples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} errors_examples.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    OUTPUT_NAME "cpp_errors_examples"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/examples
)

# Include errors directory
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../errors)