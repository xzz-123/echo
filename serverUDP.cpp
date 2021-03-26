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

#define BUF_SIZE 100

int main() {
	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(1234);
	bind(sock, (struct sockaddr*)&servAddr, sizeof(servAddr));
	
	struct sockaddr_in clntAddr;
	socklen_t nSize = sizeof(clntAddr);
	char buffer[BUF_SIZE];
	while (true)
	{
		int strlen = recvfrom(sock, buffer, BUF_SIZE, 0, (struct sockaddr*)&clntAddr, &nSize);
		sendto(sock, buffer, strlen, 0, (struct sockaddr*)&clntAddr, nSize);
	}
	close(sock);
	return 0;
}