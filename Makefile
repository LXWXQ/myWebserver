all: myserver

myserver: main.cpp server.cpp Epoll.cpp
		g++ -o myserver main.cpp server.cpp Epoll.cpp -lpthread

clean: rm -f myserver