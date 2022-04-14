/*
 * @Author       : leixu
 * @Date         : 2022-4-12
 */
#include "server.h"
#include "error.h"
using namespace std;

Server::Server(){
    port_= 5000;
    if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error_exit("socket error");
}

Server::Server(int port){
    port_=port;
    if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error_exit("socket error");
}
Server::~Server(){
    close(serverfd);
}
void Server::Start(){
    struct sockaddr_in serv_addr;
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port   = htons(port_);
    int opt = 1;
    setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));//设置地址复用
    setsockopt(serverfd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(int));//设置地址复用

    int n;
    if ((n = bind(serverfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr))) < 0)
		error_exit("bind error");

    if ((n = listen(serverfd, 128)) < 0)//
		error_exit("listen error");
}
int Server::Accept(){
    struct sockaddr_in cnt_addr;
    int cfd;
    socklen_t size = sizeof(cnt_addr);
    if ((cfd = accept(serverfd,(struct sockaddr *)&cnt_addr,&size)) < 0) {
        error_exit("accept error");
    }
    printf("New connection from  ip: %s , port: %d\n",inet_ntoa(cnt_addr.sin_addr),ntohs(cnt_addr.sin_port));
    return cfd;
}