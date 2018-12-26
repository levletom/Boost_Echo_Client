//
// Created by amitk on 12/26/18.
//

#include <TaskReadFromSTDINWriteToSocket.h>
#include <iostream>
#include "../include/connectionHandler.h"
#include "../include/TaskReadFromSTDINWriteToSocket.h"

TaskReadFromSTDINWriteToSocket::TaskReadFromSTDINWriteToSocket(int id, std::mutex &mutex,ConnectionHandler &connectionHandler): _id(id), _mutex(mutex),_connectionHandler(connectionHandler) {

}



void TaskReadFromSTDINWriteToSocket::run() {
    while (1) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        int len = line.length();
        if (!_connectionHandler.sendLine(line)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
    }
}
