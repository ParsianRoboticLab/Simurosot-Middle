#pragma once
#include <winsock2.h>
#include <stdio.h> 
#pragma comment(lib,"ws2_32.lib")
class Client
{

	SOCKET SocketClient;
	Client(void);

public:
	~Client(void);
	static Client *getInstance();
	static Client *debugClient;
	void SendMessages(const char *data);

};
