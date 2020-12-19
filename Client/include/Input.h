//
// Created by dvir on 13/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_INPUT_H
#define BOOST_ECHO_CLIENT_INPUT_H


#include <iostream>

#include "connectionHandler.h"
#include "Data.h"

using namespace std;


class Input{
private:
    ConnectionHandler & connectionHandler;

    Data &data;
    unsigned int SubscribeId;
    unsigned int RecipteId;


public:
    Input(ConnectionHandler &c, Data &data);
    void run();
    void login(vector<std::string> inputIP);
    void join(vector<std::string> inputIP);
    void exit(vector<std::string> inputIP);
    void add(vector<std::string> inputIP);
    void borrow(vector<std::string> inputIP);
    void Return(vector<std::string> inputIP);
    void status(vector<std::string> inputIP);
    void logout();




};


#endif //BOOST_ECHO_CLIENT_INPUT_H