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
	//�����׽���
	int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//���׽��ֺ�IP���˿ڰ�
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));  //ÿ���ֽڶ���0���
	serv_addr.sin_family = AF_INET;  //ʹ��IPv4��ַ
	
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //�����IP��ַ
	serv_addr.sin_port = htons(1234);  //�˿�
	bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	//�������״̬���ȴ��û���������
	listen(serv_sock, 20);

	printf("waitting client...\n");
	//���տͻ�������
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size = sizeof(clnt_addr);
	int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

	char buffer[BUF_SIZE] = { 0 };
	int nCount;
	while ((nCount=read(fd,buffer,BUF_SIZE))>0)
	{
		//��ͻ��˷�������
		write(clnt_sock, buffer, sizeof(buffer));
	}
	
	shutdown(clnt_sock,1);
	read(clnt_sock, buffer, BUF_SIZE);//��û�н��յ� client �˵����ݣ��� client �˵��� closesocket() ��server �˻��յ�FIN����read() �ͻ᷵�أ�����Ĵ������ִ�С�
	//�ر��׽���
	close(fd);
	close(clnt_sock);
	close(serv_sock);

	system("pause");
	return 0;
}