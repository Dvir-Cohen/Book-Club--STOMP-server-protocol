//
// Created by עידו on 16 ינואר 2020.
//

#include <connectionHandler.h>

#include <utility>
#include "Stomp.h"
#include "Data.h"
using namespace std;

Stomp::Stomp(ConnectionHandler &c, string msg, Data &data) : CH(c), msg(msg), data(data), terminate(false) {

    vector <string> lines;
    vector <string> words;
    splitWordByChar(lines, msg, "\n");
    auto lineiter =lines.begin();

    if (*lineiter == "CONNECTED") {
            cout << "Login successful" << endl;
        }

    if (*lineiter == "ERROR"){
        lineiter ++;
        cout<< *lineiter <<endl;
    }
    if (*lineiter == "RECEIPT"){
        lineiter++;
        splitWordByChar(words, *lineiter, ":");
        auto worditer =words.begin();
        worditer ++;
        string act = data.getMsgByRecipteId(stoi(*worditer));
        if ( act== "logout"){
            terminate= true;
        }

             else {// subscribe
            cout << act << endl;
             }


    }
    if (*lineiter == "MESSAGE"){

        lineiter++;
        string  Genre;
        int SubId;
        splitWordByChar(words, *lineiter, ":" );
        auto wordIt = words.begin();
        wordIt++;
        SubId = stoi(*wordIt);
        lineiter++;
        lineiter++;
        splitWordByChar(words, *lineiter, ":" );
        wordIt = words.begin();
        wordIt++;
        Genre = *wordIt;
        lineiter++;
        splitWordByChar(words, *lineiter, " " );
        wordIt = words.begin();

        if (*wordIt == "Taking"){
            Taking(*lineiter, SubId,Genre);
        }
        else if (*wordIt == "Returning"){
            Returning(*lineiter, SubId,Genre);
        }
        else if (*wordIt == "Book"){
            PrintBooks(Genre);
        }
        string s= *lineiter;
        if (hasChar(':',s)) {
            cout << *lineiter << endl;
        }
        wordIt++;

        if((*wordIt)=="wish") {

            WisHBook(*lineiter, SubId, Genre);

        }
         if (*wordIt == "has") {
             wordIt++;
            if (*wordIt == "added"){
                cout << *lineiter << endl;
            }
            else {
                hasBook(*lineiter, SubId, Genre);

            }        }


     }


}

void Stomp::splitWordByChar(std::vector<std::string> &words , const std::string &toSplit, string c) {
    boost::split(words, toSplit, boost::is_any_of(c));
}

void Stomp::Taking(string &line, int SubID, string genre) {
    vector<string> words;
    splitWordByChar(words, line, " ");
    auto it = words.begin();
    it++;
    string bookName = *it;
    it++;
    it++;
    if (data.getMyName() == *it) {
       auto it=data.getMyBooks().find(genre);
       if (it!= data.getMyBooks().end()) {
           for (Book book: it->second) {
               if (book.getName() == bookName) {
                   book.lendBook(true);


               }

           }
       }

    }
}

void Stomp::Returning(string &line, int SubID, const string& genre) {
    vector<string> words;
    splitWordByChar(words, line, " ");
    auto it= words.begin();
    it++;
    string bookName = *it;
    it++;
    it++;
    if (data.getMyName() == *it){
        auto it=data.getMyBooks().find(genre);
        if (it!= data.getMyBooks().end()) {
            for (Book book: it->second) {
                if (book.getName() == bookName) {
                    book.lendBook(false);
    }


}}}}

void Stomp::PrintBooks(const string& genre){
    string content;

    content = "SEND\ndestination:" +  genre +"\n"+data.getMyName() +": ";
    if (data.getMyBooks().size()>0) {
        auto genit = data.getMyBooks().find(genre);
        if (genit != data.getMyBooks().end()) {
            auto bookit = (*genit).second.begin();
            while (bookit != (*genit).second.end() && !(*bookit).isLend()) {
                content += (*bookit).getName() + ',';
                bookit++;
            }
        }

        content = content.substr(0, content.size() - 1);
        CH.sendLine(content);
    }
}

void Stomp::WisHBook(string &line, int SubID, const string& genre){
    cout<< "here in wishBook\n";
    vector<string> words;
    splitWordByChar(words, line, " ");
    auto it= words.begin();
    string name = *it;
    it++;
    it++;
    it++;
    it++;
    string bookName = *it;
    cout<<bookName<<endl;
    if (data.getMyName() != name && data.findBookByGenre(genre, bookName)){
        auto it=data.getMyBooks().find(genre);
        if (it!= data.getMyBooks().end()) {
            for (Book book: it->second) {
                if (book.getName() == bookName) {
                   if (!book.isLend()){
                        string msg= "SEND\ndestination:" +  genre +"\n"+data.getMyName()+ " has " +bookName+"\n" + "\0";
                        CH.sendLine(msg);
                   }
    }
}}}}

void Stomp::hasBook(string &line, int SubID, const string& genre) {
    vector<string> words;
    splitWordByChar(words, line, " ");
    auto it= words.begin();
    string name = *it;
    it++;
    it++;
    string bookName = *it;
    if (data.isThisMe(genre, SubID) && !data.findBookByGenre(genre,bookName)  ){
        Book book (bookName);
        book.setOwner(name);
        data.addToMyBooks(genre, book);
        string msg= "SEND\ndestination:" +  genre +"\nTaking "+ bookName+ " from " + name + "\n\0";
        CH.sendLine(msg);
    }

}

bool Stomp::logout() {
    return terminate;
}
bool Stomp:: hasChar (char c, string s){
    for(unsigned int i=0; i< s.length(); i++)
        if (s.at(i)==c)
            return true;
    return false;
}