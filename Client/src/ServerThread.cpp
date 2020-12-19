//
// Created by dvir on 13/01/2020.
//

#include "ServerThread.h"
#include <map>
#include <string>
#include <Stomp.h>
#include <Input.h>

using namespace std;

//login 127.0.0.1:7777 alice bob
ServerThread::ServerThread(ConnectionHandler &CH, Data &data, Input &input ):
        connectionHandler(CH), input(input), data(data){}

void ServerThread::run() {

        while(true){
            string ans;
            if (!connectionHandler.getLine(ans)) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                break;
            }

            Stomp stomp(connectionHandler,ans,data);
            if (stomp.logout()){
                data.shouldTerminate();
                connectionHandler.close();
                break;
            }


}


}