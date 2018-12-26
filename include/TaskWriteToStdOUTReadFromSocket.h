//
// Created by amitk on 12/26/18.
//

#ifndef BOOST_ECHO_CLIENT_TASKWRITE_H
#define BOOST_ECHO_CLIENT_TASKWRITE_H


#include <mutex>

class TaskWrite {
private:
    int _id;
    std::mutex &_mutex;
    ConnectionHandler & _connectionHandler;
public:
    TaskWrite(int id, std::mutex &mutex, ConnnectionHandler & connnectionHandler);

    void run();
};



#endif //BOOST_ECHO_CLIENT_TASKWRITE_H
