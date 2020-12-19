//
// Created by dvir on 13/01/2020.
//
#include <stdlib.h>
#include <iostream>

#include "../include/connectionHandler.h"
#include "../include/Input.h"
#include "../include/ServerThread.h"
#include "../include/Data.h"
#include <string>
#include <thread>
#include <mutex>

using namespace std;

int main (int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }

    const short bufsize = 1024;
    char buf[bufsize];
    cin.getline(buf, bufsize);

    std::string start(buf);
    std::string w;
    std::vector<std::string> inputIP;
    std::istringstream parsing(start);
    while (getline(parsing, w, ' ')) {
        if (w != "") {
            inputIP.push_back(w);
        }
    }
    //login 127.0.0.1:7777 g g
    if(start.size()!=0){
    if(inputIP[0]=="login") {
        if (inputIP.size() > 2) {
            string hostport = inputIP[1];
            string  name = inputIP[2];
            string code = inputIP[3];
            boost::split(inputIP, hostport, boost::is_any_of(":"));
            string host= inputIP[0];
            short port = std::atoi(inputIP[1].c_str());



            string msg;
            msg = string("CONNECT\n")
                  + string("accept-version:1.2\n") +
                  string("host:" + host + "\n") +
                  string("login:") + name + string("\n") +
                  string("passcode:") + code + "\n";



            //std::string host = argv[1];
            // short port = atoi(argv[2]);

            ConnectionHandler connectionHandler(host, port);
            if (!connectionHandler.connect()) {
                std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
                return 1;
            }
            Data data(host);
            data.setMyname(name);
            connectionHandler.sendLine(msg);
            Input input(connectionHandler, data);
            ServerThread serverThread(connectionHandler, data, input);
            thread IOthread(&Input::run, &input);
            thread ServThread(&ServerThread::run, &serverThread);

            ServThread.join();
            IOthread.join();

             return 0;
        }
    }}}