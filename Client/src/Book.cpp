//
// Created by dvir on 14/01/2020.
//

# include "../include/Book.h"
using namespace std;
Book::Book() :lend (false), BookName(""), BookOwner(""){}

Book::Book(string name) :lend(false),BookName(name),BookOwner(""){}

Book::~Book() {

}

string Book::getName() { return  BookName;}
bool Book:: isLend(){return lend;}
void Book::lendBook(bool b) {lend = b;}

string Book::getOwner() { return BookOwner;}

void Book::setOwner(string name) {BookOwner= name;}
