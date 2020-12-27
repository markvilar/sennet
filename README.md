# Sennet 
[![Build Status](https://travis-ci.com/markvilar/Sennet.svg?branch=master)](https://travis-ci.com/markvilar/Sennet)

## Description
Sennet is a static, cross-platform library for creating C++ applications 
with graphics and networking functionality that is developed with focus on 
sensor networking.

## Requirements
The requirements are:
- C++17 compiler
- CMake 3.16+

## CMake configuration and building

Install GLFW dependencies:
```
apt install libxrandr-dev
apt install libxinerama-dev
apt install libxcursor-dev
apt install libxi-dev
apt install libxext-dev
```

Configure CMake source and build directories:
```
cmake -S . -B build
```

Issue CMake build command:
```
cmake --build build
```

## TODOs
- Add Cmake build configurations.
- Add move constructor to image.
- Improve and expand network system:
    - Implement Endpoint.
    - Implement Socket.
    - Implement NetworkContext.
    - Implement bit conversion procedure.
- Implement 2D renderer.
    - Implement batch rendering.
    - Add rendering thread and rendering submission.
- Implement memory allocation metrics.

## DONEs
- Integrate logger into system.
- Implement assertion macros.
- Implement ZED wrappers (conversion functions).
- Implement linux window.
- Implement ZED record handler.
- Implement layer class.
- Implement application class.
- Revise communication system (runtime, messages, callbacks).
- Implement OpenGL render API.
- Implement shaders.
- Add event for window iconification.
- Move current network system from Boost.Asio to Asio standalone.
- Implement thread-safe queue.
- Implement server and client class.
- Implement templated message system.
- Implement visual profiling metrics.
