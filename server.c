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
	int lfd = 0;
	int cfd = 0;
	char buf[BUFSIZ],clientIP[BUFSIZ];

	lfd = socket(AF_INET,SOCK_STREAM,0);
	if(lfd==-1)
		sys_err("socket error!\n");

	struct sockaddr_in server_addr,client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port=htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(lfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	if(ret==-1)
		sys_err("bind error!\n");

	ret = listen(lfd,128);
	if(ret == -1)
		sys_err("listen error!\n");
	
	cfd = accept(lfd,(struct sockaddr*)&client_addr,&client_addr_len);
	if(cfd == -1)
		sys_err("accept error!\n");

	printf("client IP:%s, client port:%d\n",inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,clientIP,sizeof(clientIP)),ntohs(client_addr.sin_port));

	while(1)
	{
		ret = read(cfd,buf,sizeof(buf));
		write(STDOUT_FILENO,buf,ret);
		int i;
		for(i=0;i<ret;i++)
		{
			buf[i] = toupper(buf[i]);
		}
		write(cfd,buf,ret);
	}
	
	close(lfd);
	close(cfd);	

	return 0;
}
