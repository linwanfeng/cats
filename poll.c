#include"common.h"

int setnonblocking(int fd)
{
	int old_option=fcntl(fd, F_GETFL);
	int new_option=old_option|O_NONBLOCK;
	fcntl(fd, F_SETFL, new_option);
	return old_option;
}

void addfd(int epollfd, int fd, bool oneshot)
{
	epoll_event event;
	event.data.fd=fd;
	event.events=EPOLLIN|EPOLLET;
	if(oneshot)
	{
		event.events|=EPOLLONESHOT;
	}
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	setnonblocking(fd);
}

void reset_oneshot(int epollfd, int fd)
{
	epoll_event event;
	event.data.fd=fd;
	event.events=EPOLLIN|EPOLLET|EPOLLONESHOT;
	epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}
