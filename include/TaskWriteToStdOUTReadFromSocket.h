//
// Created by amitk on 12/26/18.
//

#ifndef BOOST_ECHO_CLIENT_TASKWRITE_H
#define BOOST_ECHO_CLIENT_TASKWRITE_H
#include <../include/connectionHandler.h>

#include <mutex>

class TaskWriteToStdOUTReadFromSocket {
private:
    int _id;
    std::mutex &_mutex;
    ConnectionHandler & _connectionHandler;
public:
    TaskWriteToStdOUTReadFromSocket(int id, std::mutex& mutex,ConnectionHandler& connectionHandler);

    void run();

    bool terminate;

    std::string* getNextProccessedMessage();
    short bytesToShort(char* bytesArr);

    std::string *createAndProcessNotificationString();

    std::string *createAndProcessAckString();

    std::string *createAndProccessErrorString();
};



#endif //BOOST_ECHO_CLIENT_TASKWRITE_H
