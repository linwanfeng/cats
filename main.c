#include "common.h"

int main(void)
{
	struct sockaddr_in sin, cin;
	socklen_t len=sizeof(cin);
	int port, lfd;
	char path[MAX_LINE];
	struct stat statbuf;
	signal(SIGCHLD, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);

	printf("initilizing..\n");

	if(init(&sin, &lfd, &port, path)==-1)
	{
		printf("error during initializing\n");
		exit(1);
	}

	epoll_event events[MAX_EVENT_NUMBER];
	int epollfd=epoll_create(5);
	if(epollfd==-1)
	{
		printf("error epoll_create");
		exit(1);
	}
	addfd(epollfd, lfd, false);

	while(1)
	{
		int num=epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
		if((num<0)&&(errno!=EINTR))
		{
			printf("epoll failure\n");
			break;
		}
		for(int i=0; i<num; i++)
		{
			int sfd=events[i].data.fd;
			printf("num=%d, sfd=%d\n", num, sfd);
			if(sfd==lfd)
			{
				while(1)
				{
					struct sockaddr_in client_address;
					socklen_t client_addrlength=sizeof(client_address);
					int cfd=accept(lfd, (struct sockaddr*)&client_address, &client_addrlength);
					printf("lfd=%d, cfd=%d\n", lfd, cfd); 
					if(cfd==-1)
					{
						if((errno==EAGAIN)||(errno==EWOULDBLOCK))
						{
							printf("accept: %s\n\n", strerror(errno));
							break;
						}
					}
					addfd(epollfd, cfd, true);
				}
			}
			else if(events[i].events&EPOLLIN)
			{
				pthread_t thread;
				fds args;
				args.epollfd=epollfd;
				args.sockfd=sfd;
				printf("sfd=%d in thread\n", sfd);
			//	pthread_create(&thread, NULL, worker, (void*)&args);
			}
		}
	}
	return 0;
}
