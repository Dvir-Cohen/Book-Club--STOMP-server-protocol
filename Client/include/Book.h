//
// Created by dvir on 14/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_BOOK_H
#define BOOST_ECHO_CLIENT_BOOK_H
#include <iostream>
#include <string>

using namespace std;
class Book {
private:
    bool lend;
    string BookName;

    string BookOwner;
public:

    Book();
    void lendBook (bool b);
    Book(string name);
    virtual ~Book();
    string getName();

    string getOwner();
    void  setOwner(string name);
    bool isLend();



};


#endif //BOOST_ECHO_CLIENT_BOOK_H
