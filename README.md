# errors

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
