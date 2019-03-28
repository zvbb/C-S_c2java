#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <iostream>
void ErrorHandling(char* message);
DWORD WINAPI ClientMain(LPVOID lpParamter);
int createClient();

int main(int argc, char* argv[])
{	
	char chars[] = "ÖÐ¹ú";
	std::cout << chars << std::endl;
	WSADATA	wsaData;
	SOCKET hServSock, hClntSock;		
	SOCKADDR_IN servAddr, clntAddr;		

	int szClntAddr;
	char message[]="Hello World!";

	if(argc!=2) 
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
  
	if(WSAStartup(0x0202, &wsaData)!=0)
		ErrorHandling("WSAStartup() error!"); 
	
	hServSock=socket(PF_INET, SOCK_STREAM, 0);
	if(hServSock==INVALID_SOCKET)
		ErrorHandling("socket() error");
  
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servAddr.sin_port=htons(atoi(argv[1]));
	
	if(bind(hServSock, (SOCKADDR*) &servAddr, sizeof(servAddr))==SOCKET_ERROR)
		ErrorHandling("bind() error");  
	
	if(listen(hServSock, 5)==SOCKET_ERROR)
		ErrorHandling("listen() error");

	szClntAddr=sizeof(clntAddr);    	
	createClient();
	hClntSock=accept(hServSock, (SOCKADDR*)&clntAddr,&szClntAddr);
	if(hClntSock==INVALID_SOCKET)
		ErrorHandling("accept() error");  
	
	send(hClntSock, message, sizeof(message), 0);
	closesocket(hClntSock);
	closesocket(hServSock);
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

int createClient()
{
    HANDLE hThread = CreateThread(NULL, 0, ClientMain, "127.0.0.1", 0, NULL);
    CloseHandle(hThread);
	return 0;
}
