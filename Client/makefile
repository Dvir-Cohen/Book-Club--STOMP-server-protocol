CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system -lpthread

all: StompBookClubClient
	
	g++ -pthread -o bin/StompBookClub bin/connectionHandler.o bin/Book.o bin/Data.o bin/Input.o bin/ServerThread.o bin/Stomp.o bin/StompBookClubClient.o $(LDFLAGS) 
	
StompBookClubClient: bin/connectionHandler.o bin/Input.o bin/ServerThread.o bin/Data.o  bin/StompBookClubClient.o bin/Book.o bin/Stomp.o
	
bin/connectionHandler.o: src/connectionHandler.cpp
	g++ -pthread $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp

bin/Data.o: src/Data.cpp
	g++ -pthread $(CFLAGS) -o bin/Data.o src/Data.cpp

bin/Input.o: src/Input.cpp
	g++ -pthread $(CFLAGS) -o bin/Input.o src/Input.cpp

bin/ServerThread.o: src/ServerThread.cpp
	g++ -pthread $(CFLAGS) -o bin/ServerThread.o src/ServerThread.cpp

bin/Stomp.o: src/Stomp.cpp
	g++ -pthread $(CFLAGS) -o bin/Stomp.o src/Stomp.cpp

bin/StompBookClubClient.o: src/StompBookClubClient.cpp
	g++ -pthread $(CFLAGS) -o bin/StompBookClubClient.o src/StompBookClubClient.cpp

bin/Book.o: src/Book.cpp
	g++ -pthread $(CFLAGS) -o bin/Book.o src/Book.cpp

	
.PHONY: clean
clean:
	rm -f bin/*

