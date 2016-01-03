#include<stdio.h>
#include<stdlib.h>
#include"mysql.h"
#include<time.h>
#include"common.h"
#define MAX_LEN 1024

MYSQL my_connection;
MYSQL_RES *res_ptr;
MYSQL_ROW sqlrow;
void display_row();

int store(const char *sockfd, const char *ip, const char *tid, const char *content)
{
	int res;

	if(mysql_real_connect(&my_connection, "localhost", "yough", "dlwxdlwx", "ws", 3306, NULL, 0))
	{
		printf("connection success.\n");
		char str[MAX_LEN]={0};
		sprintf(str, "insert into access(sockfd, ip, tid, content) values('%s', '%s', '%s', '%s')", sockfd, ip, tid, content);
		//printf("%s\n", str);

		res=mysql_query(&my_connection, str);
		if(res)
		{
			printf("select error: %s\n", mysql_error(&my_connection));
		}
		else
		{
			res_ptr=mysql_use_result(&my_connection);
			if(res_ptr)
			{
				while((sqlrow=mysql_fetch_row(res_ptr)))
				{
					printf("fetched data...\n");
					display_row();
				}
				if(mysql_errno(&my_connection))
				{
					printf("retrive error: %s\n", mysql_error(&my_connection));
				}
				mysql_free_result(res_ptr);
			}
		}
		mysql_close(&my_connection);
	}
	else
	{
		fprintf(stderr, "connection failed.\n");
		if(mysql_errno(&my_connection))
		{
			fprintf(stderr, "connection error %d: %s\n", mysql_errno(&my_connection), mysql_error(&my_connection));
		}
	}
	return 0;
}

void display_row()
{
	unsigned int field_count;
	field_count=0;

	while(field_count<mysql_field_count(&my_connection))
	{
		printf("%s ", sqlrow[field_count]);
		field_count++;
	}
	printf("\n");
}
