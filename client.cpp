#include <stdio.h>
#include <stdlib.h>
//#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
#define BUF_SIZE 100
int main() {
	//初始化DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);

	
	//向服务器发起请求
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "192.168.198.129", &sockAddr.sin_addr);
	sockAddr.sin_port = htons(1234);

	char bufSend[BUF_SIZE] = { 0 };
	char bufRecv[BUF_SIZE] = { 0 };
	while (true)
	{
		//创建套接字
		SOCKET cltSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		connect(cltSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
		
		//获取用户输入的字符串并发送給服务器
		std::cout << "Input a string:" << std::endl;
		gets_s(bufSend,BUF_SIZE);
		send(cltSock, bufSend, strlen(bufSend), 0);

		//接收服务器传回的数据
		recv(cltSock, bufRecv, BUF_SIZE, 0);
		//输出接收到的数据
		printf("Message form server: %s\n", bufRecv);

		memset(bufSend, 0, BUF_SIZE);
		memset(bufRecv, 0, BUF_SIZE);
		closesocket(cltSock);
	}
	

	WSACleanup();

	return 0;
}
