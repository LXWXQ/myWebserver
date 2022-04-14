#include "server.h"
#include "Epoll.h"
#include "task.h"
#include <pthread.h>

int main()
{
    Server myServer(5000);
    struct epoll_event events[1024];
    int nevents,fd,cfd;
    Epoll myepoll(myServer.getSeverfd());
    char buf[1024];
    myServer.Start();
    while (1)
    {
        myepoll.wait(events,nevents);
        if(nevents<0)
        {
            perror("epoll_wait error");
            if(errno==EINTR)//Interrupted system call
			{
				continue;
			}
			//break;
        }

        for(int i=0; i<nevents; i++)
        {
            fd = events[i].data.fd;
            if(fd == myServer.getSeverfd())//新连接 
            {
                cfd = myServer.Accept();
                myepoll.Add(cfd);
                continue;
            }

            //
            memset(buf, 0x00, sizeof(buf));
            //处理客户端请求
            pthread_t newthread;
            if (pthread_create(&newthread , NULL, accept_request, (void*)&fd) != 0)
		        perror("pthread_create");
        }
    }
    close(lfd);
}