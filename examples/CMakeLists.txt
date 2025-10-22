cmake_minimum_required(VERSION 3.15)
project(CppErrorsExamples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} errors_examples.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    OUTPUT_NAME "cpp_errors_examples"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/examples
)

# Link errors library
target_link_libraries(${PROJECT_NAME} PRIVATE errors::errors)
