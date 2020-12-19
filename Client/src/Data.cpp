//
// Created by dvir on 14/01/2020.
//

#include "../include/Data.h"

#include <utility>
using namespace std;
Data::Data(string host): RecipteId(0), SubsribeId(0), RecipteId_msg(), Topic_Id(
        ), MyBooks(map<string, vector<Book>>()),myName(), host(std::move(host)), terminate(false){}

Data::~Data() {
    //delete maps
    for ( auto it=RecipteId_msg.begin() ; it != RecipteId_msg.end() ; ++it) {
        RecipteId_msg.erase(it);
    }
    for ( auto it=Topic_Id.begin() ; it != Topic_Id.end() ; ++it) {
        Topic_Id.erase(it);
    }
    for ( auto it=MyBooks.begin() ; it != MyBooks.end() ; ++it) {
        for (Book book : it->second)

        MyBooks.erase(it);
    }
}

unsigned int Data::getRecipteId() {
        return RecipteId++;}
unsigned int Data::getSubscribeId() { return SubsribeId++;}

void Data::addToRecipteId_msgMap(unsigned int recipte, const string& msg) {
    RecipteId_msg.insert(pair<unsigned int, string>(recipte,msg));
}
string Data::getMsgByRecipteId(unsigned int recipte) {
    return RecipteId_msg.find(recipte)->second;
}

void Data::addToTopic_IdMap(const string& topic, unsigned int id) {
    Topic_Id.insert(pair<string,unsigned int>(topic,id));
}

void Data::addToMyBooks(const string& GenreBookName,const Book& book ) {
    auto it = MyBooks.find(GenreBookName);
    if (it != MyBooks.end())
        it->second.push_back(book);
    else {
    vector<Book> newVector;
    newVector.push_back(book);
    MyBooks.insert(pair<string, vector<Book>>(GenreBookName, newVector));
}
}

map<string, vector<Book>> Data::getMyBooks() {
    return MyBooks;
}

string Data::getMyName() { return  myName;}
void Data::setMyname(string name) {myName=std::move(name);}





bool Data::findBookByGenre(const string& genre, const string& bookName) {
    auto genit =MyBooks.find(genre);
    if (genit!= MyBooks.end()){
        auto bookit = (*genit).second.begin();
        while  (bookit != (*genit).second.end()){
            if ((*bookit).getName() == bookName)
                return true;
        }
        return false;
    }
    return false;
}

bool Data :: isThisMe (const string& genre, int id){
    auto topicIt = Topic_Id.find(genre);
    if (topicIt != Topic_Id.end())
       if ((*topicIt).second == unsigned (id))
           return true;
    return false;


}

void Data::shouldTerminate() {
    terminate=true;
}
bool Data::getTerminate() {
    return terminate;
}