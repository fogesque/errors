cmake_minimum_required(VERSION 3.20)
project(CppErrorsSamples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} errors_samples.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    OUTPUT_NAME "cpp_errors_samples"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/samples
)

# Link errors library
target_link_libraries(${PROJECT_NAME} PRIVATE errors::errors)
