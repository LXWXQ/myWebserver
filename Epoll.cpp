#include "Epoll.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include<stdio.h>
#include<stdlib.h>
Epoll::Epoll(int lfd)
{
    epollfd = epoll_create(1024);
    if(epollfd<0)
	{
		perror("create epoll error");
	}
    struct epoll_event ev;
    ev.data.fd = lfd;
	ev.events = EPOLLIN;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, lfd, &ev);
}
void Epoll::Add(int fd)
{
    struct epoll_event ev;
    ev.data.fd = fd;
	ev.events = EPOLLIN | EPOLLET;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);

    int flag = fcntl(fd, F_GETFL);
	flag |= O_NONBLOCK;
	fcntl(fd, F_SETFL, flag);//将文件描述符设置非阻塞
}
void Epoll::Del(int fd)
{
    close(fd);
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
}
void Epoll::wait(struct epoll_event* events,int &n)
{
    n = epoll_wait(epollfd, events, 1024, -1);
}
Epoll::~Epoll()
{
    close(epollfd);
}
