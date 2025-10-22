cmake_minimum_required(VERSION 3.15)
project(errors VERSION 1.0.0 LANGUAGES CXX)

# Header-only library target
add_library(errors INTERFACE)
add_library(errors::errors ALIAS errors)

# Specify include directories
target_include_directories(errors INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# Require C++17 minimum
target_compile_features(errors INTERFACE cxx_std_17)

# Installation rules
include(GNUInstallDirs)
install(TARGETS errors
    EXPORT errorsTargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install the header file
install(FILES errors/errors.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/errors
)

# Install CMake config files
install(EXPORT errorsTargets
    FILE errorsTargets.cmake
    NAMESPACE errors::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/errors
)

# Create and install Config files
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/errorsConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/errorsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/errorsConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/errors
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/errorsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/errorsConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/errors
)

# Build examples and tests (optional, controlled by option)
option(ERRORS_BUILD_TESTS "Build tests" OFF)
option(ERRORS_BUILD_EXAMPLES "Build examples" OFF)

if(ERRORS_BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(ERRORS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
