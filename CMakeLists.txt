cmake_minimum_required(VERSION 3.12)
project(Boost_Echo_Client)
include_directories(include)

set(CMAKE_CXX_STANDARD 11)

FIND_PACKAGE(Boost REQUIRED COMPONENTS system)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(progname
            src/echoClient.cpp src/connectionHandler.cpp src/TaskReadFromSTDINWriteToSocket.cpp  src/TaskWriteToStdOUTReadFromSocket.cpp )
    target_link_libraries(progname ${Boost_LIBRARIES})
endif()


