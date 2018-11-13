/*epolloneshot事件的使用
 *
 * 这个问题的原因：即使使用ET模式，一个socket上个某个事件还会可能触发多次。
 * 在线程并发模型中，在读取完sockfd上的数据后开始处理这些数据，而在数据的处理中该socket上有了
 * 新的数据可以读(epollin再次被触发)，此时另外一个线程被唤醒来读取这些新的数据，于是出现了2个线
 * 程同时操作一个socket的局面，这当然不是我们想要的，我们期望的reactor模式：一个socket在任意一个
 * 时刻只能被一个线程处理，这一点可以用epoll的EPOLLONESHOT事件来处理。
 *
 * 做法：
 * 对于注册了EPOLLONESHOT事件的fd,system最多触发其上注册的一个可读、可写、或者异常事件，
 * 且只能被触发一次，除非我门使用epoll_ctl函数重置该文件描述符上注册的EPOLLONESHOT事件，
 * 这样，当一个线程在
 * 某个socket时，其他线程是不可能操作该socket的，同时，注册了epolloneshot的事件，一旦被某个线程
 * 处理完毕，那么就应该重置这个socket上的EPOLLONESHOT事件，以确保这个socket下一次可读时，这个
 * epollin事件能够触发，进而让有其他工作线程有机会继续处理这个socket。
 */

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<pthread.h>


#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 1024

struct fds
{
	int epollfd;
	int sockfd;
};

int setnonblocking(int fd)
{
	int old_option = fcntl(fd,F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd,F_SETFL,new_option);
	return old_option;

}
//将fd上的epollin和epollet事件注册到epollfd指定的epoll内核事件表，
void addfd(int epollfd,int fd,bool oneshot)
{
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET;
	if(oneshot){
		event.events |= EPOLLONESHOT;
	}
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
	setnonblocking(fd);
}

//重置fd上的事件，这样操作之后，尽管fd上的epoll上的epolloneshot事件被注册，但是操作系统仍然会被
//触发fd上的epollin事件，且只会触发一次。
void reset_oneshot(int epollfd,int fd)
{
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLET | EPOLLET | EPOLLONESHOT;
	epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&event);
}

//工作线程。
void *worker(void *arg)
{
	int socket = ((fds*)arg)->sockfd;
	int epollfd = ((fds*)arg)->epollfd;
	printf("start new thread to receive data on fd:%d\n",sockfd);
	char buf[BUFFER_SIZE];
	memset(buf,'\0',BUFFER_SIZE);
	//循环读取sockfd上的数据，直到遇到EAGAIN错误。
	while(1){
		int ret = recv(sockfd,buf,BUFFER_SIZE-1,0);
		if(ret==0){
			close(sockfd);
			printf("foreiner closed the connection\n");
			break;
		}else if(ret<0){
			if(errno == EAGAIN){
				reset_oneshot(epollfd,sockfd);
				printf("read later\n");
				break;
			}
		}else {
			printf("get content:%s\n",buf);
			sleep(5);//休眠5秒

		}
	}
	printf("end thread receiving data on fd:%d\n",sockfd);

}

int main(int argc,char *argv[])
{
	if(argc<=2){
		printf("usage:%s ip_address port_number\n",basename(argv[0]));
		return 1;
	}
	const char *ip = argv[1];
	int port = atoi(argv[2]);

	int ret = 0;
	struct sockaddr_in address;
	bzero(&address,sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port = htons(port);

	int listenfd = socket(PF_INET,SOCK_STREAM,0);
	assert(listenfd >= 0);

	ret = bind(listenfd,(struct sockaddr*)&address,sizeof(address));
	assert(ret != -1);

	epoll_event events[MAX_EVENT_NUMBER];
	int epollfd = epoll_create(5);
	asset(epollfd != -1);

	addfd(epollfd,listenfd,false);

	while(1){
		int ret = epoll_wait(epollfd,events,MAX_EVENT_NUMBER,-1);
		if(ret < 0){
			printf("epoll failure\n");
			break;
		}
		for(int i=0;i<ret;++i){
			int sockfd = events[i].data.fd;
			if(sockfd == listenfd){
				struct sockaddr_in client_address;
				socklen_t client_addrlength = sizeof(client_address);
				int connfd = accept(listenfd,(struct sockaddr *)&client_address,&client_addrlength);
				addfd(epollfd,connfd,true);
			}else if(events[i].events & EPOLLET){
				pthread_t thread;
				fds fds_for_new_worker;
				fds_for_new_worker.epollfd = epollfd;
				fds_for_new_worker.sockfd = sockfd;
				pthread_create(&thread,NULL,worker,(void*)&fds_for_new_worker);

			}else {
				printf("something else happened\n");
			}
		}
	}
	close(listenfd);

	return 0;
}




