//
// Created by dvir on 14/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_DATA_H
#define BOOST_ECHO_CLIENT_DATA_H
#include <iostream>
#include <map>
#include <vector>
#include <atomic>
#include "Book.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

using namespace std;

class Data {
private:
    atomic <int> RecipteId;
    atomic <int> SubsribeId;
    map<unsigned int ,string > RecipteId_msg;
    map<string, unsigned int > Topic_Id;
    map<string, vector<Book>> MyBooks; //map who contain all the books by genre, and vector of all the books of this genre.

    string myName;
    string host;
    atomic<bool> terminate;
public:
    Data(string host);
    virtual ~Data();

    unsigned int getRecipteId();
    unsigned int getSubscribeId();
    void addToRecipteId_msgMap(unsigned int recipte, const string& msg);
    void addToTopic_IdMap(const string& topic, unsigned int id );
    void addToMyBooks(const string& generBookName, const Book& book);
    map<string, vector<Book>> getMyBooks();

    string getMsgByRecipteId (unsigned int recipte);
    string getMyName();
    void setMyname(string name);



    bool findBookByGenre(const string& genre, const string& bookName);
    bool isThisMe (const string& genre, int id);


    void shouldTerminate();
    bool getTerminate();

};


#endif //BOOST_ECHO_CLIENT_DATA_H
