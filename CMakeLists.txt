cmake_minimum_required(VERSION 3.12)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})
find_package(Boost COMPONENTS system filesystem REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-std=c++11 -pthread -lboost_thread")


add_executable(Boost_Echo_Client
        include/connectionHandler.h
        include/TaskReadFromSTDINWriteToSocket.h
        include/TaskWriteToStdOUTReadFromSocket.h
        src/connectionHandler.cpp
        src/TaskWriteToStdOUTReadFromSocket.cpp
        src/TaskReadFromSTDINWriteToSocket.cpp
        src/echoClient.cpp)

target_link_libraries(Boost_Echo_Client ${Boost_LIBRARIES})
