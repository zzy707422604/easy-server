#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#define SERVER_PORT 9998
void sys_err(const char *str)
{
	perror(str);
	exit(1);
}

int main(int argc, char *argv[])
{
	int cfd = 0;
	char buf[BUFSIZ];

	cfd = socket(AF_INET,SOCK_STREAM,0);
	if(cfd==-1)
		sys_err("socket error!\n");

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port=htons(SERVER_PORT);
	inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr.s_addr);

	int ret = connect(cfd,(struct sockaddr*)&server_addr,sizeof(server_addr));	

	while(1)
	{
		write(cfd,"hello\n",6);
		ret = read(cfd,buf,sizeof(buf));
		write(STDOUT_FILENO,buf,ret);
		sleep(1);
	}
	
	close(cfd);	

	return 0;
}
