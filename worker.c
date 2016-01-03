#include"common.h"
#include<iostream>

void * worker(void * arg)
{
	pthread_t tid;
	tid=pthread_self();
	int cfd=((fds*)arg)->sockfd;
	int epollfd=((fds*)arg)->epollfd;
	printf("\nThread ID: %ld, Sock FD: %d\n",tid, cfd);

	while(1)
	{
		char path[MAX_LINE];
		int port;
		configuration(&port, path); 
		char buf[MAX_LINE];
		memset(buf, '\0', MAX_LINE);

		int ret=read(cfd, buf, MAX_LINE);
		if(ret==0)
		{
			close(cfd);
			printf("foreign has closed the connection\n");
			break;
		}
		else if(ret<0)
		{
			if(errno==EAGAIN)
			{
				reset_oneshot(epollfd, cfd);
				close(cfd);
				printf("read later\n");
			}
			break;
		}
		else
		{
			if(parse(buf, path)==-1)
			{
				printf("error during geting filepath.\n");
				break;
			}

			printf("request: %s\npath: %s", buf, path);
/*
			struct stat statbuf;
			if(stat(path, &statbuf)==-1)
			{
				printf("stat: %s\n", strerror(errno));
				break;
			}

			if(!S_ISREG(statbuf.st_mode))
			{
				if(error_page(cfd)==-1)
				{
					printf("error during writing error_page\n");
					close(cfd);
					exit(1);
				}
				break;
			}

			int	fd=open(path, O_RDONLY);
			if(fd==-1)
			{
				if(error_page(cfd)==-1)
				{
					printf("error during writing error_page\n");
				}
				close(fd);
				break;
			}

			if(write_page(cfd, fd, path)==-1)
			{
				printf("error during writing page\n");
				close(fd);
				break;
			}
				close(fd);
				*/
		}
	}
}
