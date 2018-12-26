//
// Created by amitk on 12/26/18.
//


#include <iostream>
#include <connectionHandler.h>

#include "../include/TaskWriteToStdOUTReadFromSocket.h"

TaskWrite::TaskWrite(int id, std::mutex &mutex,ConnectionHandler & connectionHandler):_id(id), _mutex(mutex),_connectionHandler(connectionHandler) {}



void TaskWrite::run(){
    for (int i= 0; i < 100; i++){
        std::lock_guard<std::mutex> lock(_mutex); // constructor locks the mutex while destructor (out of scope) unlocks it
        std::cout << i << ") Task " << _id << " is working" << std::endl;
    }
}


