//
// Created by amitk on 12/26/18.
//


#include <iostream>
#include <connectionHandler.h>

#include "../include/TaskWriteToStdOUTReadFromSocket.h"

using namespace std;

TaskWriteToStdOUTReadFromSocket::TaskWriteToStdOUTReadFromSocket(int id, std::mutex &mutex,
                                                                 ConnectionHandler &connectionHandler) : _id(id),
                                                                                                         _mutex(mutex),
                                                                                                         _connectionHandler(
                                                                                                                 connectionHandler) {
    terminate = false;
}


void TaskWriteToStdOUTReadFromSocket::run() {
    /*for (int i= 0; i < 100; i++){
        std::lock_guard<std::mutex> lock(_mutex); // constructor locks the mutex while destructor (out of scope) unlocks it
        std::cout << i << ") Task " << _id << " is working" << std::endl;
    }*/
    while (!_connectionHandler.shouldTerminate()) {
        string  *messageToPrint = getNextProccessedMessage();
        if(messageToPrint != nullptr) {
            cout << *messageToPrint << endl;
            delete messageToPrint;
        }

    }
}

std::string* TaskWriteToStdOUTReadFromSocket::getNextProccessedMessage() {
    char *bytes = new char[2];
    short opcode = -1;
    bool success = _connectionHandler.getBytes(bytes, 2);
    if (success) {
        opcode = bytesToShort(bytes);
        delete[] bytes;
        switch (opcode) {
            case 9  :
                return createAndProcessNotificationString();
            case 10  :
                return createAndProcessAckString();
            case 11:
                return createAndProccessErrorString();


            default :
                return new string("Unexpected Error Reading Reacieved Opcode");
        }
    }
    return nullptr;


}

short TaskWriteToStdOUTReadFromSocket::bytesToShort(char *bytesArr) {
    short result = (short) ((bytesArr[0] & 0xff) << 8);
    result += (short) (bytesArr[1] & 0xff);
    return result;
}

std::string* TaskWriteToStdOUTReadFromSocket::createAndProcessNotificationString() {
    char *pmOrPost = new char[1];
    bool success = _connectionHandler.getBytes(pmOrPost, 1);
    if (success) {
        string postingUser;
        if (!_connectionHandler.getLine(postingUser)) {
            std::cout << "unexpected error while reading posting user" << std::endl;

        }
        int len = postingUser.length();
        postingUser.resize(len - 1);
        string content;
        if (!_connectionHandler.getLine(content)) {
            std::cout << "unexpected error while reading content" << std::endl;

        }
        len = content.length();
        content.resize(len - 1);
        string pmOrPostString;
        if (pmOrPost[0] == 0)
            pmOrPostString = "PM ";
        else if (pmOrPost[0] == 1)
            pmOrPostString = "Public ";
        else
            cout << "unexpected error when deciding if PM or POST" << endl;
        delete[]  pmOrPost;
        return new string("NOTIFICATION " + pmOrPostString + postingUser + " " + content);


    }
    delete[] pmOrPost;
    return nullptr;
}

std::string* TaskWriteToStdOUTReadFromSocket::createAndProcessAckString() {
    char *bytes = new char[2];
    short messageOpcode = -1;
    bool success = _connectionHandler.getBytes(bytes, 2);
    if (success) {
        messageOpcode = bytesToShort(bytes);
        delete[] bytes;
        short numOfUsers;
        char *numOfUsersbytes = new char[2];
        short numPosts;
        short numFollowers;
        short numFollowing;
        vector<string> users;
        string result;
        switch (messageOpcode) {
            //register
            case 1  :
                delete[] numOfUsersbytes;
                return new string("ACK 1");
                //login
            case 2:
                _connectionHandler.setIsLoggedIn(true);
                delete[] numOfUsersbytes;
                return new string("ACK 2");
                //logout
            case 3:
                _connectionHandler.setShouldTerminate(true);
                _connectionHandler.setWaitingForLogoutAck(false);
                delete[] numOfUsersbytes;
                return new string("ACK 3");
                //follow/unfollow
            case 4:


                if (!_connectionHandler.getBytes(numOfUsersbytes, 2))
                    return new string("unexpected error when reading numOfUsers");

                numOfUsers = bytesToShort(numOfUsersbytes);

                for (int i = 0; i < numOfUsers; i++) {
                    string name;
                    _connectionHandler.getLine(name);
                    int len = name.length();
                    name.resize(len - 1);
                    users.push_back(name);

                }

                result = "ACK 4 " + to_string(numOfUsers);
                for (string name:users) {
                    result += " " + name;
                }
                delete[] numOfUsersbytes;
                return new string(result);
                //POST
            case 5:
                delete[] numOfUsersbytes;
                return new string("ACK 5");
                //PM
            case 6:
                delete[] numOfUsersbytes;
                return new string("ACK 6");
                //UserList
            case 7:
                if (!_connectionHandler.getBytes(numOfUsersbytes, 2))
                    return new string("unexpected error when reading numOfUsers");

                numOfUsers = bytesToShort(numOfUsersbytes);
                delete[] numOfUsersbytes;

                for (int i = 0; i < numOfUsers; i++) {
                    string name;
                    _connectionHandler.getLine(name);
                    int len = name.length();
                    name.resize(len - 1);
                    users.push_back(name);

                }

                result = "ACK 7 " + to_string(numOfUsers);
                for (string name:users) {
                    result += " " + name;
                }
                return new string(result);
            case 8:
                if (!_connectionHandler.getBytes(numOfUsersbytes, 2))
                    return new string("unexpected error when reading numOfPosts");

                numPosts = bytesToShort(numOfUsersbytes);

                if (!_connectionHandler.getBytes(numOfUsersbytes, 2))
                    return new string("unexpected error when reading numOfFollowers");

                numFollowers = bytesToShort(numOfUsersbytes);

                if (!_connectionHandler.getBytes(numOfUsersbytes, 2))
                    return new string("unexpected error when reading numFollowing");

                numFollowing = bytesToShort(numOfUsersbytes);
                result = "ACK 8 "+to_string(numPosts)+" "+to_string(numFollowers)+" "+to_string(numFollowing);
                delete[] numOfUsersbytes;
                return new string(result);
            default:
                delete[] numOfUsersbytes;
                return new string("unexpected Error - recieved ack message without proper message operator 1-8");


        }
    }

return nullptr;
}

std::string* TaskWriteToStdOUTReadFromSocket::createAndProccessErrorString() {
    char *bytes = new char[2];
    short messageOpcode = -1;
    bool success = _connectionHandler.getBytes(bytes, 2);
    if (success) {
        messageOpcode = bytesToShort(bytes);
        if(messageOpcode==3)
            _connectionHandler.setWaitingForLogoutAck(false);
        return new string("ERROR " + to_string(messageOpcode));
    } else
        return new string("Unexpected Error while reading Error Message recicving message opcode");


}
