//poll 和 epoll 的使用差别

int ret = poll(fds,MAX_EVENT_NUMBER,-1);
//必须遍历所有已注册文件描述符并找到其中的就绪者

for(int i=0;i<MAX_EVENT_NUMBER;++i){
	if(fds[i].revents & POLLIN){
		int sockfd = fds[i].fd;
		//处理sockfd
	}
	

}


//如何索引epoll返回的就绪文件描述符
int ret=epoll_wait(epollfd,events,MAX_EVENT_NUMBER,-1);
//仅仅遍历就绪的ret个文件描述符
for(int i=0;i<ret;++i){
	int sockfd = events[i].data.fd;
}

