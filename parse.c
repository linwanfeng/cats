#include "common.h"

int parse(char *buf, char *path)
{
	if(strstr(buf, "GET")!=buf)
	{
		printf("wrong request, it couldn't be parsed.\n");
		return -1;
	}

	if((buf[4]=='/')&&(buf[5]==' '))
		strcat(path, "/index.html");
	else
	{
		strtok(&buf[4], " ");
		strcat(path, &buf[4]);
    }
	return 0;
}



