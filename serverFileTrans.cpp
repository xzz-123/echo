#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUF_SIZE 1024
int main() {
	char *filename = "/home/xzz/Documents/MDA.pdf";
	int fd=open(filename, O_RDONLY);
	if (fd==-1)
	{
		printf("Cannot open file,press any key to exit!\n");
		system("pause");
		exit(0);
	}
	//创建套接字
	int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//将套接字和IP、端口绑定
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
	serv_addr.sin_family = AF_INET;  //使用IPv4地址
	
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //具体的IP地址
	serv_addr.sin_port = htons(1234);  //端口
	bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	//进入监听状态，等待用户发起请求
	listen(serv_sock, 20);

	printf("waitting client...\n");
	//接收客户端请求
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size = sizeof(clnt_addr);
	int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

	char buffer[BUF_SIZE] = { 0 };
	int nCount;
	while ((nCount=read(fd,buffer,BUF_SIZE))>0)
	{
		//向客户端发送数据
		write(clnt_sock, buffer, sizeof(buffer));
	}
	
	shutdown(clnt_sock,1);
	read(clnt_sock, buffer, BUF_SIZE);//并没有接收到 client 端的数据，当 client 端调用 closesocket() 后，server 端会收到FIN包，read() 就会返回，后面的代码继续执行。
	//关闭套接字
	close(fd);
	close(clnt_sock);
	close(serv_sock);

	system("pause");
	return 0;
}