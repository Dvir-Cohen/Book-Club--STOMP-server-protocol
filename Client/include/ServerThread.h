//
// Created by dvir on 13/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_SERVERTHREAD_H
#define BOOST_ECHO_CLIENT_SERVERTHREAD_H
#include "connectionHandler.h"
#include <iostream>
#include "connectionHandler.h"
#include "Data.h"
#include "Input.h"
#include <map>



using namespace std;


class ServerThread {
private:
    ConnectionHandler &connectionHandler;
    Input &input;
    Data &data;


public:
    ServerThread(ConnectionHandler &connectionHandler, Data &data, Input &input);
    void run();

};


#endif //BOOST_ECHO_CLIENT_SERVERTHREAD_H
