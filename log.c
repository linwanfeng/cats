#include "common.h"

int Log(char *str)
{
	time_t t;
	if(time(&t)==-1)
	{
		perror("fail to time");
		return -1;
	}

	struct tm *cal;
	cal=localtime(&t);
	char buf[MAX_LINE];
	int m=sprintf(buf, "[%d-%02d-%02d %02d:%02d:%02d] %s\n", cal->tm_year+1900, cal->tm_mon+1, cal->tm_mday, cal->tm_hour, cal->tm_min, cal->tm_sec, str);
	buf[m]='\0';

	int fd=open("./ws.log", O_WRONLY|O_APPEND|O_CREAT);
	if(fd==-1)
	{
		printf("open: %s", strerror(errno));
		return -1;
	}

	int n=write(fd, buf, m);
	if(n==-1)
	{
		printf("write: %s", strerror(errno));
		return -1;
		return -1;
	}
	close(fd);

	return 0;
}

