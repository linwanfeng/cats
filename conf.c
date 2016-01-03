#include "common.h"

int configuration(int * port, char * path)
{
	char buf[50];
	FILE *fp=fopen("./config.ini", "r");
	if(fp==NULL)
	{
		printf("fopen: %s\n", strerror(errno));
		return -1;
	}

	while(fgets(buf, 50, fp)!=NULL)
	{
		if(buf[strlen(buf)-1]!='\n')
		{
			printf("error in config.ini\n");
			return -1;
		}
		else 
			buf[strlen(buf)-1]='\0';

		if(strstr(buf, "port")==buf)
		{
			char * p=strchr(buf, ':');
			if(p==NULL)
			{
				printf("config.ini expect ':'\n");
				return -1;
			}

			*port=atoi(p+2);
			if(*port<=0)
			{
				printf("error port\n");
				return -1;
			}
		}
		else if(strstr(buf, "root-path")==buf)
		{
			char * p=strchr(buf, ':');
			if(p==NULL)
			{
				printf("config.ini expect ':'\n");
				return -1;
			}
			p=p+2;

			strcpy(path, p);
		}
		else
		{
			printf("error in config\n");
			return -1;
		}
	}

	return 0;
}
