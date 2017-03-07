# File server and client

Boost simple file server and client

Client sends file name that want to download, server transmits this file from local folder if exists.


## Dependencies

- c++14

- CMake 2.8+

- Boost library 1.58+

## Build

```
cd FileServer
cmake CMakeLists.txt
make

cd FileClient
cmake CMakeLists.txt
make
```