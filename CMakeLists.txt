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

add_executable(server ${PROJECT_SOURCE_DIR}/server.cpp)
add_executable(client ${PROJECT_SOURCE_DIR}/client.cpp)
target_link_libraries(server ${PROJECT_SOURCE_DIR}/libCSocketMFC.so)
target_link_libraries(client ${PROJECT_SOURCE_DIR}/libCSocketMFC.so)

add_executable(server_udp ${PROJECT_SOURCE_DIR}/server_udp.cpp)
add_executable(client_udp ${PROJECT_SOURCE_DIR}/client_udp.cpp)
target_link_libraries(server_udp ${PROJECT_SOURCE_DIR}/libCSocketMFC.so)
target_link_libraries(client_udp ${PROJECT_SOURCE_DIR}/libCSocketMFC.so)