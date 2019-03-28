#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
void ErrorHandling(char* message);

DWORD WINAPI ClientMain(LPVOID lpParamter)
{
	char * arg = (char*)lpParamter;
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;

	char message[30];
	int strLen;

	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");  
	
	hSocket=socket(PF_INET, SOCK_STREAM, 0);
	if(hSocket==INVALID_SOCKET)
		ErrorHandling("socket() error");
	
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servAddr.sin_port=htons(atoi("8000"));
	
	if(connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr))==SOCKET_ERROR)
		ErrorHandling("connect() error!");
 
	int index = 0;
	int messageLen=0;
	while (recv(hSocket,&message[index++],1,0))
	{
		messageLen++;
		if (message[index-1]=='\n')
		{
			break;
		}
	}
	if(messageLen==-1)
		ErrorHandling("read() error!");
	printf("Message from server: %s \n", message);  
	printf("message length: %d", messageLen);
	closesocket(hSocket);
	WSACleanup();
	return 0L;
}

