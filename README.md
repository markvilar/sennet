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
- Add Cmake build types.
- Implement error system (?).
- Implement layer class.
- Revise communication system (runtime, messages, callbacks).
- Implement OpenGL render API.
- Implement 2D renderer.
- Implement shaders.
- Implement application class.
- Implement file handler.
- HIL-test ZED recorder (multi-thread interaction, changing settings, etc.)

## DONEs
- Integrate logger into system.
- Implement assertion macros.
- Implement ZED wrappers (conversion functions).
- Implement linux window.
- Implement ZED record handler.

## Acknowledgements
I would like to acknowledge Yan Chernikov (TheCherno) and Bryce
Adelstein-Lelbach for inspiring the system design of this project
through the game engine Hazel and the CppCon 2014 presentation on Boost.Asio and
Boost.Serialization, respectively. A significant portion of the source code of
this project is either directly copied or slightly altered from these two
projects.
