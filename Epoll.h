
#ifndef EPOLL_H
#define EPOLL_H

#include <sys/epoll.h>
#include <ctype.h>

class Epoll
{
private:
    int epollfd;
public:
    Epoll(int lfd);
    ~Epoll();
    void Add(int fd);
    void Del(int fd);
    void wait(struct epoll_event* events,int &n);
};


#endif //EPOLL_H