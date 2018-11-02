/*
 *测试非阻塞的connect
 *
 *
 */

#include"./nonblock_connect.h"

using namespace std;

int main(int argc,char ** argv)
{
	if(argc<=2){
		printf("usage:%s ip_address port_number \n",basename(argv[0]));
		return 1;
	}
	const char ip = argv[1];
	int port = atoi(argv[2]);

	int sockfd = unblock_connect(ip,port,10);
	if(sockfd<0){
		return 1;
	}
	close(sockfd);

	return 0;
	
}
