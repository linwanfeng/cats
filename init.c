#include "common.h"

int init(struct sockaddr_in *sin, int *lfd, int *port, char *path)
{
	int tfd;
	configuration(port, path);

	bzero(sin, sizeof(struct sockaddr_in));

	sin->sin_family=AF_INET;
	sin->sin_addr.s_addr=INADDR_ANY;
	sin->sin_port=htons(*port);

	tfd=socket(AF_INET, SOCK_STREAM, 0);
	if(tfd==-1)
	{
		printf("socket: %s\n", strerror(errno));
		return -1;
	}

	int res=bind(tfd, (struct sockaddr*)sin, sizeof(struct sockaddr_in));
	if(res==-1)
	{
		printf("bind: %s\n", strerror(errno));
		return -1;
	}

	res=listen(tfd, 20);
	if(res==-1)
	{
		printf("listen: %s\n", strerror(errno));
		return -1;
	}

	*lfd=tfd;

	return 0;
}
