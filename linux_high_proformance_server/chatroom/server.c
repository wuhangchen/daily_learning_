//服务端程序使用poll来监听socket和连接socket。
//

#define _GNU_SOURCE 1
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<poll.h>

#define USER_LIMIT 5   //最大用户总量
#define BUFFER_SIZE 64  //读缓冲区的空间
#define FD_LIMIT 65535    //文件描述符的数量限制

//客户端数据，客户端socket地址，代写到客户段的数据的位置，从客户端读入的数据
struct client_data{
	sockaddr_in address;
	char *write_buf;
	char buf[BUFFER_SIZE];
};

int set_nonblocking(int fd){
	int old_option = fcntl(fd,F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd,F_SETFL,new_option);
	return old_option;
}


int main(int argc,char **argv){
	
	if(argc<=2){
		printf("ussage:%s ip_address port_number\n",basename(argv[0]));
		return 1;
	}
	const char* ip = argv[1];
	int port = atoi(argv[2]);

	int ret = 0;
	struct sockaddr_in address;
	bzero(&sockaddr_in,sizeof(sockaddr_in));
	address.sin_family = AF_INET;
	inet_pton(AF_INET,IP,&sockaddr_in.sin_addr);
	address.sin_port = htons(port);

	int listenfd = socket(PF_INET,SOCK_STREAM,0);
	assert(listenfd >= 0);

	ret = bind(listenfd,(struct sockaddr*)&address,sizeof(address));
	assert(ret != -1);

	ret = listen(listenfd,5);
	assert(ret != -1);

	//创建users数组，分配FD_LIMIT个client_data对象，可以预期，每个可能的socket连接都可以
	//获得一个这样的对象，并且socket的值是可以直接用来索引(作为数组的下标)socket连接对应的
	//client_data对象，这是将客户数据关联的简单而高效的方式。
	//总结起来就是一个连接占用一个fd，而一个fd与client_data对象关联起来的。
	
	client_data *users = new client_data[FD_LIMIT];
	struct pollfd fds[USER_LIMIT+1];
       	int user_counter = 0;
	
	for(int i=1;i<=USER_LIMIT;++i){
		fds[i].fd = -1;
		fds[i].events = 0;
	}	
	fds[0].fd = listenfd;
	fds[0].events = POLLIN | POLLERR;
	fds[0].revents = 0;

	while(1){
		ret = poll(fds,user_counter+1,-1);
		if(ret<0){
			printf("poll failure\n");
			break;
		}

		for(int i=0;i<user_counter+1;++i){
			if((fd[i].fd == listenfd) && (fds[i].revents & POLLIN)){
				struct sockaddr_in client_address;
				socklen_t client_addrlength = sizeof(client_address);
				int connfd = accept(listenfd,(struct sockaddr *)&client_address,&client_addrlength);
				if(connfd<0){
					printf("errno is: %d\n",errno);
					continue;
				}
				//请求过多，则关闭新的连接
				if(user_counter >= USER_LIMIT){
					const char* info = "too many users\n";
					printf("%s\n",info);
					send(connfd,info,strlen(info),0);
					close(connfd);
					continue;
				}
				//对于新的连接，需要同时修改fds和user数组，users[connfd]对应性连接文件描述符的connfd的客户数据
				user_counter++;
				users[connfd].address = client_addrlength;
				set_nonblocking(connfd);
				fds[user_counter].fd = connfd;
				fds[user_counter].events = POLLIN | POLLERR | POLLRDHUP;
				fds[user_counter].revents = 0;
				printf("comes a new user,now have %d users\n",user_counter);
			}
			//错误的情况发生
			else if(fds[i].revents & POLLERR){
				printf("get an error from %d\n",fds[i].fd);
				char errors[100];
				memset(errors,'\0',100);
				socklen_t length = sizeof(errors);
				if(getsockopt(fds[i].fd,SQL_SOCKET,SO_ERROR,&errors,&length)<0){
				printf("get socket option failed \n");
				}
				continue;
			}
			else if(fds[i].revents & POLLRDHUP){
				//如果客户端关闭连接，则服务端也关闭连接，并将用户数减1
				users[fds[i].fd]] = users[fds[user_counter].fd];
				close(fds[i].fd);
				fds[i]=fds[user_counter];
				i--;
				user_counter--;
				printf("a client left\n");
			}
			else if(fds[i].revents & POLLIN){
				int connfd = fds[i].fd;
				memset(users[connfd].buf,'\0',BUFFER_SIZE);
				ret = recv(connfd,users[connfd].buf,BUFFER_SIZE-1,0);
				printf("get %d bytes of client data %s form %d\n",ret,users[connfd].buf,connfd);
				if(ret<0){
					//如果连接出现错误，则应该进行处理
					if(errno != EAGAIN){
						close(connfd);
						users[fds[i].fd]= users[fds[user_counter].fd];
						fds[i]=fds[user_counter];
						i--;
						user_counter--;
					}
					
				}else if(ret == 0 ){
					
				}
			}
				
		}
	}
	return 0;
}
