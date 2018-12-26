//
// Created by amitk on 12/26/18.
//

#ifndef BOOST_ECHO_CLIENT_TASKREAD_H
#define BOOST_ECHO_CLIENT_TASKREAD_H

#include <mutex>
#include <../include/connectionHandler.h>

class TaskReadFromSTDINWriteToSocket{
private:
    int _id;
    std::mutex & _mutex;
    ConnectionHandler & _connectionHandler;
public:
    TaskReadFromSTDINWriteToSocket (int id, std::mutex& mutex,ConnectionHandler& connectionHandler);

    void run();


};

#endif //BOOST_ECHO_CLIENT_TASKREAD_H
