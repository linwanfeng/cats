#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<signal.h>
#include<errno.h>
#include<strings.h>
#include<time.h>
#include<sys/epoll.h>
#include<pthread.h>

#define MAX_LINE 1024
#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 10

struct fds
{
	int epollfd;
	int sockfd;
};

extern int init(struct sockaddr_in * sin, int * lfd, int * port, char *path);
extern int error_page(int sock_fd);
extern int parse(char *buf, char * path);
extern int write_page(int cfd, int fd, char * path);
extern int configuration(int * port, char * path);
extern int Log(char *str);
extern void * worker(void * arg);
extern int setnonblocking(int fd);
extern void addfd(int epollfd, int fd, bool oneshot);
extern void reset_oneshot(int epollfd, int fd);
