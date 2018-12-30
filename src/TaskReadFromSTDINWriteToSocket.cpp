//
// Created by amitk on 12/26/18.
//
#include <vector>
#include <TaskReadFromSTDINWriteToSocket.h>
#include <iostream>
#include "../include/connectionHandler.h"
#include "../include/TaskReadFromSTDINWriteToSocket.h"
#include <sstream>
#include <iterator>

using namespace std;

TaskReadFromSTDINWriteToSocket::TaskReadFromSTDINWriteToSocket(int id, std::mutex &mutex,ConnectionHandler &connectionHandler): _id(id), _mutex(mutex),_connectionHandler(connectionHandler) {

}



void TaskReadFromSTDINWriteToSocket::run() {
    while (1) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);

        vector<string> toStrings = explode(line,' ');
        char* opCodeBytes = new char[2];

        if(toStrings.front()=="REGISTER"){
           shortToBytes(1,opCodeBytes);
            _connectionHandler.sendBytes(opCodeBytes,2);
            _connectionHandler.sendFrameAscii(toStrings.at(1),'\0');
            _connectionHandler.sendFrameAscii(toStrings.at(2),'\0');
        }
        else if(toStrings.front()=="LOGIN"){
            shortToBytes(2,opCodeBytes);
            _connectionHandler.sendBytes(opCodeBytes,2);
            _connectionHandler.sendFrameAscii(toStrings.at(1),'\0');
            _connectionHandler.sendFrameAscii(toStrings.at(2),'\0');
        }
        else if(toStrings.front()=="LOGOUT"){
            shortToBytes(3,opCodeBytes);
            _connectionHandler.sendBytes(opCodeBytes,2);
        }
        else if(toStrings.front()=="FOLLOW"){
            shortToBytes(4,opCodeBytes);
            _connectionHandler.sendBytes(opCodeBytes,2);
            _connectionHandler.sendBytes(toStrings.at(1).c_str(),1);
            _connectionHandler.sendFrameAscii(toStrings.at(2).c_str(),toStrings.at(2).size());
            int numOfUsers = std::stoi(toStrings.at(2));
            for(int i=0;i<numOfUsers;i++){
                _connectionHandler.sendFrameAscii(toStrings.at(i+3),'\0');
            }
        }
        else if(toStrings.front()=="POST"){
            shortToBytes(5,opCodeBytes);
            _connectionHandler.sendBytes(opCodeBytes,2);
            if(toStrings.size()>1) {
                for (int i = 1; i < toStrings.size() - 1; i++) {
                    _connectionHandler.sendFrameAscii(toStrings.at(i), ' ');
                }
                _connectionHandler.sendFrameAscii(toStrings.at(toStrings.size()-1),'\0');
            }
        }
        else if(toStrings.front()=="PM"){
            shortToBytes(6,opCodeBytes);
            _connectionHandler.sendBytes(opCodeBytes,2);
            _connectionHandler.sendFrameAscii(toStrings.at(1),'\0');
            if(toStrings.size()>2) {
                for (int i = 2; i < toStrings.size() - 1; i++) {
                    _connectionHandler.sendFrameAscii(toStrings.at(i), ' ');
                }
                _connectionHandler.sendFrameAscii(toStrings.at(toStrings.size()-1),'\0');
            }
        }
        else if(toStrings.front()=="USERLIST"){
            shortToBytes(7,opCodeBytes);
            _connectionHandler.sendBytes(opCodeBytes,2);
        }
        else if(toStrings.front()=="STAT"){
            shortToBytes(8,opCodeBytes);
            _connectionHandler.sendBytes(opCodeBytes,2);
            _connectionHandler.sendFrameAscii(toStrings.at(1),'\0');
        }
        else{
            cout<<"ERROR WHILE READING FIRST 2 BYTES" << endl;
        }





    }
}

void TaskReadFromSTDINWriteToSocket::shortToBytes(short num, char* bytesArr)
{
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

vector<string> TaskReadFromSTDINWriteToSocket::explode(const string& str, const char& ch) {
    string next;
    vector<string> result;

    // For each character in the string
    for (string::const_iterator it = str.begin(); it != str.end(); it++) {
        // If we've hit the terminal character
        if (*it == ch) {
            // If we have some characters accumulated
            if (!next.empty()) {
                // Add them to the result vector
                result.push_back(next);
                next.clear();
            }
        } else {
            // Accumulate the next character into the sequence
            next += *it;
        }
    }
    if (!next.empty())
        result.push_back(next);
    return result;
}


int TaskReadFromSTDINWriteToSocket::stringToInt(string s) {
    return stoi(s);
}
