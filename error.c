#include "common.h"

int error_page(int sock_fd)
{
	char err_str[1024];

#ifdef BUG
	sprintf(err_str, "HTTP/1.1 404 %s\r\n", strerror(errno));
#else
	sprintf(err_str, "HTTP/1.1 404 Not Exist\r\n");
#endif

	if(write(sock_fd, err_str, strlen(err_str))==-1)
		return -1;

	sprintf(err_str, "Content-Type: text/html\r\n\r\n");
	if(write(sock_fd, err_str, strlen(err_str))==-1)
		return -1;

	sprintf(err_str, "<html><body>the file does not exist</body></html>");
	if(write(sock_fd, err_str, strlen(err_str))==-1)
		return -1;

	return 0;
}

