#pragma once
#include <winsock2.h>
#include <stdio.h> 

#include <Ws2tcpip.h> // needed for ip_mreq definition for multicast
#include <Windows.h>
#include <string.h>
#include <stdlib.h>

#pragma comment(lib,"ws2_32.lib")


class Server {
public:
	Server(const char* _ip, int _port) : group(_ip), port(_port){
		//
		// Initialize Windows Socket API with given VERSION.
		//
		WSADATA wsaData;
		if (WSAStartup(0x0101, &wsaData)) {
			perror("WSAStartup");
		}


		// create what looks like an ordinary UDP socket
		//
		fd = socket(AF_INET, SOCK_DGRAM, 0);
		if (fd < 0) {
			perror("socket");
		}

		// set up destination address
		//
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr(group);
		addr.sin_port = htons(port);

	}
	~Server() {
		//
		// Program never actually gets here due to infinite loop that has to be
		// canceled, but since people on the internet wind up using examples
		// they find at random in their own code it's good to show what shutting
		// down cleanly would look like.
		//
		WSACleanup();

	}

	bool send(const char* message, int size) {
		char ch = 0;
		int nbytes = sendto(
			fd,
			message,
			size,
			0,
			(struct sockaddr*) &addr,
			sizeof(addr)
		);
		if (nbytes < 0) {
			perror("sendto");
			return 1;
		}

	}

private:
	struct sockaddr_in addr;
	const char* group; // e.g. 239.255.255.250 for SSDP
	int port; // 0 if error, which is an invalid port
	int fd;
};
