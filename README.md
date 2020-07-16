# sennet

## Requirements
The requirements are:
- Boost 1.72.0
- C++17 compiler (gcc 7 or higher, clang 8 or higher)
- ZED SDK 3.0 (available for Windows 10 and Ubuntu 16/18)
- CUDA 10.2

## Configuring, building and testing
To update submodules:
```
git submodule update --remote --merge
```
To configure CMake:
```
cmake -S . -B build
```
Optionally, if you want to specify the root directory of Boost:
```
cmake -S . -B build -DBOOST_ROOT=/path/to/boost
```
To build:
```
cmake --build build
```
To test:
```
cmake --build build --target test
```
To build docs:
```
cmake --build build --target docs
```

## TODOs
- Implement ZED wrappers.
- Implement assertion macros.
- Implement sensor handler.
- Implement error wrapper.
- Revise message system.
- Implement user interface.
- Implement application class.

## DONEs
- Integrate logger into system.
