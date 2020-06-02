# zedutils
zedutils is a library of utility functions for the ZED and ZED Mini. zedutils is built on the [ZED SDK 3.0](https://www.stereolabs.com/docs/api/).

## Requirements
The requirements of zedutils are:
- ZED SDK 3.X (available for Windows 10 and Ubuntu 16/18)
  - CUDA 9.X/10.X (dependent on the ZED SDK installation)
- C++17 compiler (gcc 7.X+, clang 8.X+)
- Boost 1.72.0

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
To build zedutils:
```
cmake --build build
```
To test zedutils:
```
cmake --build build --target test
```
To build zedutils docs:
```
cmaek --build build --target docs
```

## TODOs
- Implement serialization of boost::asio::ip::basic_endpoint.
- Add sender/responder endpoints in requests and responses.
- Add logging system.
