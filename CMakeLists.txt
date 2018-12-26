cmake_minimum_required(VERSION 3.12)
project(Boost_Echo_Client)
include_directories(include)

set(CMAKE_CXX_STANDARD 11)

FIND_PACKAGE(Boost REQUIRED COMPONENTS system)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(BGSclient
            src/echoClient.cpp src/connectionHandler.cpp src/TaskWriteToStdOUTReadFromSocket.cpp src/TaskReadFromSTDINWriteToSocket.cpp)
    target_link_libraries(BGSclient ${Boost_LIBRARIES})
endif()


