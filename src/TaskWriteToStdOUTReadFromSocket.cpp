//
// Created by amitk on 12/26/18.
//

#include <TaskWriteToStdOUTReadFromSocket.h>
#include <iostream>

#include "TaskWriteToStdOUTReadFromSocket.h"

TaskWriteToStdOUTReadFromSocket::TaskWriteToStdOUTReadFromSocket(int id, std::mutex &mutex):_id(id), _mutex(mutex) {}



void TaskWriteToStdOUTReadFromSocket::run(){
    for (int i= 0; i < 100; i++){
        std::lock_guard<std::mutex> lock(_mutex); // constructor locks the mutex while destructor (out of scope) unlocks it
        std::cout << i << ") Task " << _id << " is working" << std::endl;
    }
}


