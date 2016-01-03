#include"common.h"
#include<iostream>

void * worker(void * arg)
{
	int cfd=((fds*)arg)->sockfd;
	int epollfd=((fds*)arg)->epollfd;

	char path[MAX_LINE];
	int port;
	configuration(&port, path); 
	char buf[MAX_LINE];
	memset(buf, '\0', MAX_LINE);

	int ret=read(cfd, buf, MAX_LINE);
	if(ret>0)
	{
		if(parse(buf, path)==-1)
		{
			printf("error during geting filepath.\n");
			return NULL;
		}
		printf("request: %s\r\npath: %s\r\n", buf, path);

		struct stat statbuf;
		if(stat(path, &statbuf)==-1)
		{
			printf("stat: %s\n", strerror(errno));
			return NULL;
		}

		if(!S_ISREG(statbuf.st_mode))
		{
			if(error_page(cfd)==-1)
			{
				printf("error during writing error_page.\n");
				close(cfd);
				return NULL;
			}
			close(cfd);
			return NULL;
		}

		int	fd=open(path, O_RDONLY);
		if(fd==-1)
		{
			if(error_page(cfd)==-1)
			{
				printf("error during open target file.\n");
				close(cfd);
				return NULL;
			}
			close(cfd);
			return NULL;
		}

		if(write_page(cfd, fd, path)==-1)
		{
			printf("error during writing page.\n");
			return NULL;
		}
		close(fd);
		close(cfd);
		return NULL;
	}
	else
	{
		close(cfd);
		return NULL;
	}
}
