# errors

<p align="center">
  <img src="https://github.com/fogesque/errors/blob/main/logo.png?raw=true" alt="C++ errors logo" width="320"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-17%2F20%2F23-blue.svg?logo=c%2B%2B&logoColor=white" alt="C++ Standard"/>
  <img src="https://img.shields.io/badge/License-MIT-green.svg" alt="MIT License"/>
  <img src="https://img.shields.io/badge/Build-Linux-blue.svg" alt="Linux Build"/>
</p>

A modern C++ error handling package inspired by Go's error concept. This library provides transparent, composable, and type-safe error management for C++ projects, making error handling more robust and expressive.

## Features
- Simple error creation and propagation
- Error wrapping with context
- Joining multiple errors
- Type-safe error matching and extraction
- API closely modeled after Go's standard `errors` package

## Dependencies

> **Note:** Since package was built and tested on Ubuntu, there will be instructions how to setup environment on this operating system.

To use this package in your projects, you will need:

- C++ compiler with support at least C++17 standard

To build examples and tests in this repo, you will need:

- GCC 14 / G++ 14 (with C++23 support)
```bash
sudo apt install gcc-14 g++-14
```
Use ```update-alternatives``` to switch between compiler versions.
- CMake (>=3.15)
```bash 
sudo apt install cmake
```
- Ninja (can be switched to other build tool)
```bash 
sudo apt install ninja-build
```
- vcpkg (for dependency management)

See [vcpkg Quick Start](https://github.com/microsoft/vcpkg#quick-start) for setting up vcpkg.

## vcpkg Integration

This project uses vcpkg for dependency management and provides an overlay port for easy integration into other projects.

### Using errors in Your vcpkg Project

To use the `errors` library in your own project via vcpkg, you must use the provided overlay port located in the `vcpkg-overlays` directory.

1. **Add the overlay port to your vcpkg command:**
	```bash
	vcpkg install errors --overlay-ports=/path/to/errors/vcpkg-overlays
	```

2. **Or configure it in your `vcpkg-configuration.json`:**
	```json
	{
	  "overlay-ports": ["path/to/errors/vcpkg-overlays"]
	}
	```

3. **Add errors to your project's `vcpkg.json`:**
	```json
	{
	  "dependencies": [
	    "errors"
	  ]
	}
	```

4. **Use in CMake:**
	```cmake
	find_package(errors CONFIG REQUIRED)
	target_link_libraries(your_target PRIVATE errors::errors)
	```

5. **Include in your C++ code:**
	```cpp
	#include <errors/errors.hpp>
	```

## Building the Project

1. **Clone the repository and initialize vcpkg dependencies:**
	```bash
	git clone https://github.com/fogesque/errors.git
	cd errors
	vcpkg install
	```

2. **Configure the project with CMake**
	```bash
	cmake -S . -B build
	```

	Or use the vcpkg preset:
	```bash
	cmake --preset=vcpkg
	```

3. **Build examples and tests:**
	```bash
	cmake --build build
	```

## Running Examples

After building, run the examples binary:

```bash
./build/bin/examples/cpp_errors_examples
```

## Running Tests

After building, run the test binary:

```bash
./build/bin/tests/cpp_errors_tests
```

All tests are written using GoogleTest and will verify the correctness of the error handling API.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
