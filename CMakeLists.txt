cmake_minimum_required(VERSION 3.17)
project(MyService)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(MyService main.cpp src/threadPool.cpp src/serviceSocket.h src/serivceSocket.cpp)

#include_directories(/home/jon/CLionProjects/MyService/src)

