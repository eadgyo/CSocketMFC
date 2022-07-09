cmake_minimum_required(VERSION 3.10)

# set the project name
project(CSocketMFC)
include_directories(include)

add_library(CSocket
  SHARED
  src/CSocket.cpp src/CAsyncSocket.cpp)


# add the executable
#add_subdirectory(./src)