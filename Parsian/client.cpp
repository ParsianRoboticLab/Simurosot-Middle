#include "StdAfx.h"
#include "client.h"
#include <iostream>
#define debugger

Client* Client::debugClient = Client::getInstance();

Client* Client::getInstance()
{
	if (debugClient == 0)
		return new Client();
	else
		return debugClient;
}
Client::Client(void)
{
#ifdef debugger
	//char buffer[1000];
	// Initialise Winsock
	WSADATA WsaDat;
	if (WSAStartup(MAKEWORD(2, 2), &WsaDat) != 0)
	{
		std::cout << "Winsock error - Winsock initialization failed\r\n";
		WSACleanup();
		system("PAUSE");
		exit(1);
	}

	// Create our socket
	SocketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SocketClient == INVALID_SOCKET)
	{
		std::cout << "Winsock error - Socket creation Failed!\r\n";
		WSACleanup();
		system("PAUSE");
		exit(1);
	}

	// Resolve IP address for hostname
	struct hostent *host;
	if ((host = gethostbyname("localhost")) == NULL)
	{
		std::cout << "Failed to resolve hostname.\r\n";
		WSACleanup();
		system("PAUSE");
		exit(1);
	}

	// Setup our socket address structure
	SOCKADDR_IN SockAddr;
	SockAddr.sin_port = htons(8888);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

	// Attempt to connect to server
	if (connect(SocketClient, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0)
	{
		std::cout << "Failed to establish connection with server\r\n";
		WSACleanup();
		system("PAUSE");
		exit(1);
	}
#endif
}

void Client::SendMessages(const char *data)
{
#ifdef debugger
	send(SocketClient, data, strlen(data), 0);
	if (strcmp(data, "close") == 0)
	{

		// Shutdown our socket
		shutdown(SocketClient, SD_SEND);

		// Close our socket entirely
		closesocket(SocketClient);

		// Cleanup Winsock
		WSACleanup();
		system("PAUSE");
		exit(1);
	}
#endif
}
Client::~Client()
{
}
