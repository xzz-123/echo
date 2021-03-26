#include <stdio.h>
#include <stdlib.h>
//#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
#define BUF_SIZE 1024
int main() {
	char filename[100] = { 0 };
	printf("input filename to save:");
	gets_s(filename);
	FILE *fp = nullptr;
	fopen_s(&fp,filename, "wb");
	if (fp == nullptr)
	{
		printf("Cannot open file,press any key to exit!\n");
		system("pause");
		exit(0);
	}
	//初始化DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);
	SOCKET clt_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	//向服务器发起请求
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "192.168.198.129", &sockAddr.sin_addr);
	sockAddr.sin_port = htons(1234);
	connect(clt_sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	char buffer[BUF_SIZE] = { 0 };
	int nCount;
	while ((nCount=recv(clt_sock,buffer,BUF_SIZE,0))>0)
	{
		fwrite(buffer, nCount, 1,fp);
	}
	puts("File transfer success");

	fclose(fp);
	closesocket(clt_sock);

	WSACleanup();
	system("pause");
	return 0;
}
