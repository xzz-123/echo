#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

#define BUF_SIZE 100
int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	inet_pton(AF_INET,  "192.168.198.129", &servAddr.sin_addr);
	
	servAddr.sin_port = htons(1234);

	sockaddr fromAddr;
	int addrLen = sizeof(fromAddr);
	while (true)
	{
		char buffer[BUF_SIZE] = { 0 };
		printf("Input a string");
		gets_s(buffer);
		sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&servAddr, sizeof(servAddr));
		int strlen = recvfrom(sock, buffer, BUF_SIZE, 0, &fromAddr, &addrLen);
		buffer[strlen] = 0;
		printf("Message from server: %s\n", buffer);

	}
	closesocket(sock);
	WSACleanup();
	return 0;
}