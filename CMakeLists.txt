cmake_minimum_required(VERSION 3.10)

# set the project name
project(CSocketMFC C CXX)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS " -Wall -g ")

include_directories(include)

#file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)

#set(SRC ${PROJECT_SOURCE_DIR}/src/CSocket.cpp
#        ${PROJECT_SOURCE_DIR}/src/CAsyncSocket.cpp)

add_library(CSocketMFC SHARED ${SRC})
# add the executable
