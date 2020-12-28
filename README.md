# Sennet 
[![Build Status](https://travis-ci.com/markvilar/Sennet.svg?branch=master)](https://travis-ci.com/markvilar/Sennet)

## Description
Sennet is a static, cross-platform library for creating C++ applications 
with graphics and networking functionality that is developed with focus on 
geometric data visualization and sensor networking.

## Requirements
The requirements are:
- C++17 compiler
- CMake 3.16+

## Dependencies

Install GLFW dependencies:
```
apt install libxrandr-dev
apt install libxinerama-dev
apt install libxcursor-dev
apt install libxi-dev
apt install libxext-dev
```

## Building with CMake

Configure CMake source and build directories:
```
cmake -S . -B build
```

Issue CMake build command:
```
cmake --build build
```

## Development Plan

[Trello board][https://trello.com/b/iZZPB2t0/sennet]

## Acknowledgements
I would like to acknowledge the following projects for inspiring this one:
- [Hazel](https://github.com/TheCherno/Hazel)
- [FlexEngine](https://github.com/ajweeks/FlexEngine)
- [olcPixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine)
- [anki-3d-engine](https://github.com/godlikepanos/anki-3d-engine)
- [cilantro](https://github.com/kzampog/cilantro)
