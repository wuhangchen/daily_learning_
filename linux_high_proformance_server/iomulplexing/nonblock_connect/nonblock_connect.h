/*
 * the socket is nonblocking and the connection cannot be completed immediatedly .
 * it is possible to select or poll for completion by selecion the socket for writing ,after 
 * select indicates writability ,use getsockopt to read the SO_ERROR option at level SQL_SOCKET  * to determine whether connecti completed successfully(SO_ERROR is zero )or unsuccessfully (SO_ * ERROR is one of the usual error codes listed here,explaining the reason for the failure.)
 */
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstdlib>
#include<assert.h>
#include<cstdio>
#include<ctime>
#include<errno.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<string>


#define BUFFER_SIZE 1023

//set the fd nonblocking 
int setnonblocking(int fd)
{
	int old_option = fcntl(fd,F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd,F_SETFL,new_option);
	return old_option；
}

//超时连接函数，参数分别是服务器的Ip地址，端口号，超时时间(毫秒)
//成功返回已经处于连接状态的socket,否则则返回-1；
int ubblock_connect(const char *ip,int port ,int time)
{
	int ret = 0;
	struct sockaddr_in address;
	bzero(&address,sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET,IP,&address.sin_addr);
	address.sin_port = htons(port);

	int sockfd = socket(PF_INET,SOCK_STREAM,0);
	int fdopt = setnonblocking(sockfd);

	ret = connect(sockfd,(struct sockaddr *)&address ,sizeof(address));

	//根据ret来判断连接结果
	if(ret == 0){
		//连接成功，则恢复sockfd 的属性，并立即返回
		printf("connect with server immediately\n");
		fcntl(sockfd,F_SETFL,fdopt);
		return sockfd;
	}else if(errno != EINPROGRESS){
		//如果连接没有立即建立，只有可能当errno还是EINPROGRESS时才可能表示连接还在进行
		
		printf("ubblock_connect not support\n");
		return -1;
	}

	fd_set readfds;
	fd_set writefds;
	struct timeval timeout;

	FD_ZERO(&readfds);
	FD_SET(sockfd,&writefds);

	timeout.tv_sec = time;
	timeout.tv_usec = 0;

	ret = select(socket+1,nullptr,&writefds,nullptr,&timeout);
	//select延时或者出错，则会立即返回
	if(ret<=0){
		printf("connection time out\n");
		close(sockfd);
		return -1;
	}
	if(!FD_ISSET(sockfd ,&writefds)){
		printf("no event on sockfd found\n");
		close(sockfd);
		return -1;
	}
	int error = 0;
	socklen_t length = sizeof(error);

	//调用getsockopt 来获取并清除sockfd 的错误
	if(getsockopt(sockfd,SOL_SOCKET,SO_ERROR,&error,&length)<0){
		printf("get socket option failed\n");
		close(sockfd);
		return -1;
	}

	//错误号不为0表示连接出错
	if(error != 0){
		printf("connection failed after select with the error:%d\n",error);
		close(sockfd);
		return -1;
	}

	//连接成功
	
	printf("connection ready after select with the sockft:%d\n",sockfd);
	fcntl(sockfd,F_SETFL,fdopt);

	return sockfd;
}
