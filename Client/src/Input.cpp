
#include <iterator>
#include "../include/connectionHandler.h"
#include "../include/Input.h"

using namespace std;

Input::Input(ConnectionHandler &c, Data &data) : connectionHandler(c), data(data),  SubscribeId(data.getSubscribeId()), RecipteId(data.getRecipteId())  {}

void Input::run() {
    while(!data.getTerminate()){ {
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

            if (inputIP[0]== "join"){
                join(inputIP);}
            else if (inputIP[0] == "login"){
                login(inputIP);
            }
            else if (inputIP[0]== "add"){
                add(inputIP);}
            else if (inputIP[0]== "exit"){
                exit(inputIP);}
            else if (inputIP[0]== "borrow"){
                borrow(inputIP);}
            else if (inputIP[0]== "return"){
                Return(inputIP);}
            else if (inputIP[0]== "status"){
                status(inputIP);}
            else if (inputIP[0]== "logout"){
                logout();
}
        }

    }

    connectionHandler.close();
}

void Input::login(vector<std::string> inputIP) {
    string hostport = inputIP[1];
    string  name = inputIP[2];
    string code = inputIP[3];
    boost::split(inputIP, hostport, boost::is_any_of(":"));
    string host= inputIP[0];
    //short port = std::atoi(inputIP[1].c_str());



    string msg;
    msg = string("CONNECT\n")
          + string("accept-version:1.2\n") +
          string("host:" + host + "\n") +
          string("login:") + name + string("\n") +
          string("passcode:") + code + "\n";
    connectionHandler.sendLine(msg);


}
void  Input :: join (vector<std::string> inputIP) {
    string genre, msg;
    genre = inputIP[1];
    int Rid= data.getRecipteId();
    msg = string("SUBSCRIBE\n")+
          "destination:" + genre+ "\n"
                                  "id:" + to_string(SubscribeId) +"\n"+
          "receipt:" + to_string(Rid) + "\n";
    data.addToTopic_IdMap(genre, SubscribeId );
    data.addToRecipteId_msgMap(Rid, "Joined club: " + genre);
    // map. add id-sub , reciept-sub
    connectionHandler.sendLine(msg);
}

void  Input :: add (vector<std::string> inputIP) {
    string genre, bookName, msg;
    genre= inputIP[1];
    bookName= inputIP[2];
    // add book to my book map
    Book newBook = Book(bookName);
    newBook.setOwner(data.getMyName());
    data.addToMyBooks(genre, newBook);
    msg = string("SEND\n")+
          "destination:"+ genre +"\n"+
          data.getMyName()+  " has added the book "+ bookName +"\n";
    connectionHandler.sendLine(msg);
}

void  Input :: borrow (vector<std::string> inputIP) {
    string genre, bookName, msg;
    genre = inputIP[1];
    bookName = inputIP[2];
    msg = string("SEND\n")+
          "destination:"+ genre+"\n"+
          data.getMyName() + " wish to borrow "+ bookName + "\n";
    connectionHandler.sendLine(msg);
}

void  Input :: Return (vector<std::string> inputIP) {
    string genre, bookName, msg;
    genre = inputIP[1];
    bookName = inputIP[2];
    auto it = data.getMyBooks().find(genre);
    if (it != data.getMyBooks().end()) {
        for (Book book:it->second) {
            if (book.getName() == bookName) {
                book.lendBook(true);
                msg = string("SEND\n") +
                      "destination:" + genre + "\n" +
                      "Returning " + bookName + " to " + book.getOwner() + "\n"; // hold lending map

                connectionHandler.sendLine(msg);

            } else
                cout << "you do not have the book in your inventory" << endl;
        }
    }
}
void  Input :: status (vector<std::string> inputIP) {
    string genre, msg;
    genre = inputIP[1];
    msg = 	string("SEND\n")+
             "destination:" + genre + "\n"+
             "book status\n";
    connectionHandler.sendLine(msg);
}

void Input::logout() {
     string msg;
    int Rid= data.getRecipteId();
    msg = 	string("DISCONNECT\n")+
             "receipt:" + to_string(Rid)+"\n";
    data.addToRecipteId_msgMap(Rid, "logout");
    connectionHandler.sendLine(msg);
    while (!data.getTerminate())
        sleep(0.1);

}


void  Input :: exit (vector<std::string> inputIP) {
    string genre, msg;
    genre = inputIP[1];
    int Rid= data.getRecipteId();
    msg = string("UNSUBSCRIBE\n")+
          "destination:" + genre+ "\n"
                                  "id:" + to_string(SubscribeId) +"\n"+
          "receipt:" + to_string(Rid) + "\n";
    data.addToTopic_IdMap(genre, SubscribeId );
    data.addToRecipteId_msgMap(Rid, "Exited club: " + genre);
    // map. add id-sub , reciept-sub
    connectionHandler.sendLine(msg);
}