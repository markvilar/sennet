# Sennet

Sennet is a static, cross-platform library for creating C++ applications 
with graphics and networking functionality that is developed with focus on 
sensor networking.

## Requirements
The requirements are:
- Boost 1.72.0+
- C++17 compiler
- CMake 3.16+

## Configuring, building and testing
Configure CMake:
```
cmake -S . -B build -DBOOST_ROOT=/path/to/boost
```
To build:
```
cmake --build build
```

## TODOs
- Add Cmake build configurations.
- Move current network system from Boost.Asio to Asio standalone.
- Improve and expand network system:
    - Implement Endpoint.
    - Implement Service.
    - Implement Session.
    - Implement Message Queue.
    - Implement Message Register.
- Implement 2D renderer.
    - Implement batch rendering.
    - Add rendering thread and rendering submission.
- Revise application class (non-GUI applications?).

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
- Implement ZED messages (in separate project?).

## Acknowledgements
I would like to acknowledge Yan Chernikov (TheCherno) for inspiring the system 
design of this project through the game engine 
[Hazel](https://github.com/TheCherno/Hazel). A significant portion of the source 
code of this project is adapted from this project or inspired by it.