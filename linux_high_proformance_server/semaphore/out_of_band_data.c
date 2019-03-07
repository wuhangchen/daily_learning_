//利用SIGURG信号来处理接受带外数据
//利用io复用系统调用报告的异常事件和sigUrg信号，但应用程序检测到带外数据到达之后，我们
//还需要进一步判断带外数据在数据流中的位置，才能够准确无误的读取带外数据。

#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<signal.h>
#include<fcntl.h>

#define BUF_SIZE 1024
static int connfd;

//SIGURG的信号处理函数
void sig_urg(int sig)
{
	int save_errno = errno;
	char buffer[BUF_SIZE];
	memset(buffer,'\0',BUF_SIZE);
	int ret = recv(connfd ,buffer,BUF_SIZE-1,MSG_OOB);
	printf("got %d bytes of foob data '%s'\n",ret,buffer);
	errno = save_errno;
}

void addsig(int sig,void (*sig_handler)(int))
{
	struct sigaction sa;
	memset(&sa,'\0',sizeof(sa));
	sa.sa_handler = sig_handler;
	sa.sa_flags |= SA_RESTART;
	sigfillset(&sa.sa_mask);
	assert(sigaction(sig,&sa,NULL)!=-1);
}

int main(int argc,char* argv[])
{
	if(argc<=2){
		printf("usage:%s ip_address port_number\n",basename(argv[0]));
		return 1;	
	}
	const char *ip = argv[1];
	int port = atoi(argv[2]);

	struct sockaddr_in address;
	bzero(&address,sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port = htons(port);

	int sock = sock(PF_INET,SOCK_STREAM,0);
	assert(sock>=0);

	int ret = bind(sock,(struct sockaddr*)&address,sizeof(address));
	assert(ret!=-1);

	ret  = listen(sock,5);
	assert(ret != -1);

	struct sockaddr_in client;
	socklen_t client_addrlength = sizeof(client);
	connfd = accept(sock,(struct sockaddr*)&client,&client_addrlength);
	if(connfd <0)
		printf("errno is:%d\n",errno);
	else{
		addsig(SIGURG,sig_urg);
		//使用sigurg信号之前，我们必须设置socket的宿主进程或者进程组
		fcntl(connfd,F_SETOWN,getpid());

		char buffer[BUF_SIZE-1];
		while(1)//接收普通数据
		{
			memset(buffer,'\0',BUF_SIZE-1);
			ret = recv(connfd,buffer,BUF_SIZE-1,0);
			if(ret<=0){
				break;
			}
			printf("got %d bytes of normal data '%s'\n",ret,buf);
		}
		close(connfd)
	}

	close(sock);
	return 0;
}
