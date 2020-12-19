//
// Created by עידו on 16 ינואר 2020.
//
using namespace std;
#include <vector>
#ifndef BOOST_ECHO_CLIENT_STOMP_H
#define BOOST_ECHO_CLIENT_STOMP_H
#include "../include/Data.h"

#include <string>

class Stomp {
private:
    ConnectionHandler &CH;
    string msg;
    Data &data;
    bool terminate;
public:
    Stomp(ConnectionHandler &c, string msg, Data &data);
    void splitWordByChar(vector<string> &words , const string &toSplit, string c);

    void Taking(string &line, int SubId, string genre);

    void Returning(string &line, int SubId, const string& genre);

    void WisHBook(string &line, int SubId, const string& genre);

    void hasBook(string &line, int SubId, const string& genre);

    void PrintBooks(const string& genre);
    bool logout();
    bool hasChar (char c, string s);
};




#endif //BOOST_ECHO_CLIENT_STOMP_H
