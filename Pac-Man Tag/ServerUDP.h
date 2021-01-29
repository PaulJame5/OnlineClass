#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<stdio.h>
#include<winsock2.h>
#include <vector>
#include <iostream>
#include <string>
#include "PacketData.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define BUFLEN 512	//Max length of buffer
#define PORT 2000	//The port on which to listen for incoming data

class ServerUDP
{
public:
	ServerUDP();
	~ServerUDP();

	void run();
	void setup();
	struct std::vector<sockaddr_in> others;
	static int numberOfClients;
private:
	SOCKET s;
	struct sockaddr_in server, si_other;
	int slen, recv_len;
	WSADATA wsa;

	char buf[BUFLEN];

	bool isNewConnection();
	bool isExit();
	void sendMessageToOthers();
	bool closeServer();
};


inline ServerUDP::ServerUDP()
{
	//setup();
}


inline ServerUDP::~ServerUDP()
{
	int size = others.size();
	bool selfSent = false;
	for (int i = 0; i < size; i++)
	{
		//send closing data to all clients
		while (sendto(s, SERVER_CLOSED, sizeof(SERVER_CLOSED), 0, (struct sockaddr*) & others.at(i), slen) == SOCKET_ERROR)
		{

		}
	}
	closesocket(s);
	WSACleanup();
}

inline void ServerUDP::run()
{
	//keep listening for data
	while (1)
	{
		fflush(stdout);

		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);

		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr*) & si_other, &slen)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}


		if (closeServer())
		{
			this->~ServerUDP();
			return;
		}

		if (isNewConnection())
		{
			continue;
		}
		if (isExit())
		{
			continue;
		}
		sendMessageToOthers();


	}
}

inline bool ServerUDP::isNewConnection()
{
	std::string msg = buf;
	std::string msgPass = CONNECTED_PACKET;
	if (msg == msgPass)
	{
		numberOfClients++;
		others.push_back(si_other);
		return true;
	}
	return false;
}

inline bool ServerUDP::isExit()
{
	std::string msg = buf;
	std::string msgExit = EXIT_PACKET;

	if (msg == msgExit)
	{
		int size = others.size();
		for (int i = 0; i < size; i++)
		{
			std::string othersString = inet_ntoa(others.at(i).sin_addr) + std::to_string(ntohs(others.at(i).sin_port));
			std::string si_otherString = inet_ntoa(si_other.sin_addr) + std::to_string(ntohs(si_other.sin_port));
			if (othersString == si_otherString)
			{
				others.erase(others.begin() + i);
				return true;
			}
		}
	}
	return false;
}

inline void ServerUDP::sendMessageToOthers()
{
	int size = others.size();
	bool selfSent = false;
	for (int i = 0; i < size; i++)
	{
		std::string othersString = inet_ntoa(others.at(i).sin_addr) + std::to_string(ntohs(others.at(i).sin_port));
		std::string si_otherString = inet_ntoa(si_other.sin_addr) + std::to_string(ntohs(si_other.sin_port));
		if (othersString == si_otherString)
		{
			continue;
		}

		//now reply the other client with the same data
		if (sendto(s, buf, recv_len, 0, (struct sockaddr*) & others.at(i), slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}
}

inline bool ServerUDP::closeServer()
{
	std::string msg = buf;
	std::string closeServer = SERVER_CLOSED;
	std::cout << msg << std::endl;
	if (msg == closeServer)
	{
		return true;
	}
	return false;
}

inline void ServerUDP::setup()
{
	others = std::vector<sockaddr_in>();
	slen = sizeof(si_other);

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}
	printf("Socket created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT);

	//Bind
	if (bind(s, (struct sockaddr*) & server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	puts("Bind done");
}
