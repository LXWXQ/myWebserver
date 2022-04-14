/*
 * @Author       : leixu
 * @Date         : 2022-04-12
 */ 
#ifndef SERVER_H
#define SERVER_H

#include <unordered_map>
#include <fcntl.h>       // fcntl()
#include <unistd.h>      // close()
#include <assert.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include<iostream>

class Server {
public:
    Server();
    Server(int port);

    ~Server();
    void Start();
    int Accept();
    int getSeverfd() const{
        return serverfd;
    }

private:
    int port_;
    int serverfd;
};


#endif //SERVER_H