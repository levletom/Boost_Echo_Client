//
// Created by amitk on 12/26/18.
//

#ifndef BOOST_ECHO_CLIENT_TASKREAD_H
#define BOOST_ECHO_CLIENT_TASKREAD_H

#include <mutex>

class TaskRead{
private:
    int _id;
    std::mutex & _mutex;
public:
    TaskRead (int id, std::mutex& mutex);

    void run();


};

#endif //BOOST_ECHO_CLIENT_TASKREAD_H
