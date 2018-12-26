//
// Created by amitk on 12/26/18.
//

#include <TaskRead.h>
#include <iostream>
#include "../include/connectionHandler.h"
#include "TaskRead.h"

TaskRead::TaskRead(int id, std::mutex &mutex): _id(id), _mutex(mutex) {}



void TaskRead::run() {
    while (1) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        int len=line.length();
        if (!connectionHandler.sendLine(line)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
}

