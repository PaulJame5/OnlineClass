#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<stdio.h>
#include<winsock2.h>
#include <iostream>
#include <thread>
#include <string>
#include "PacketData.h"
#include "PlayerStateHandlers.h"
#include "TransformSystem.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library
//
#define SERVER "127.0.0.1"	
#define BUFLEN 512	//Max length of buffer
#define PORT 2000	//The port on which to listen for incoming data


class ClientUDP
{
public:
	ClientUDP();

	~ClientUDP();

	void sendMessage(const char* msg);
	void receive();
	void setup(const char* ip, USHORT port);

	std::thread thread_1;

	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];
	WSADATA wsa;

private:
	bool serverWasClosed();
	bool gotInput();
	bool syncPosition();
};



inline ClientUDP::ClientUDP()
{
}


inline void ClientUDP::setup(const char* ip, USHORT port)
{

	//setup address structure
	memset((char*)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(port);
	si_other.sin_addr.S_un.S_addr = inet_addr(ip);

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	if (sendto(s, CONNECTED_PACKET, strlen(CONNECTED_PACKET), 0, (struct sockaddr*) & si_other, slen) == SOCKET_ERROR)
	{
		printf("Server Not Available");
		return;
	}
}
inline ClientUDP::~ClientUDP()
{
	// Send Exit Packet
	sendto(s, EXIT_PACKET, strlen(EXIT_PACKET), 0, (struct sockaddr*) & si_other, slen);
	closesocket(s);
	WSACleanup();
}

inline void ClientUDP::sendMessage(const char* msg)
{
	//send the message
	if (sendto(s, msg, strlen(msg), 0, (struct sockaddr*) & si_other, slen) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
}

inline void ClientUDP::receive()
{
	while (1)
	{
		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);

		//try to receive some data, this is a blocking call
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr*) & si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		if (serverWasClosed())
		{
			this->~ClientUDP();
		}
		if (syncPosition())
		{
			continue;
		}

		if (gotInput())
		{
			continue;
		}

		puts(buf);
	}
}

inline bool ClientUDP::serverWasClosed()
{
	std::string msg = buf;
	if (msg == SERVER_CLOSED)
	{
		return true;
	}
	return false;
}

inline bool ClientUDP::gotInput()
{
	std::string msg = buf;
	if (msg == UP_PACKET)
	{
		PlayerStateHandler::lastInputOtherPlayer = UP;
		return true;
	}
	if (msg == DOWN_PACKET)
	{
		PlayerStateHandler::lastInputOtherPlayer = DOWN;
		return true;
	}
	if (msg == LEFT_PACKET)
	{
		PlayerStateHandler::lastInputOtherPlayer = LEFT;
		return true;
	}
	if (msg == RIGHT_PACKET)
	{
		PlayerStateHandler::lastInputOtherPlayer = RIGHT;
		return true;
	}
	return false;
}

inline bool ClientUDP::syncPosition()
{
	std::string msgs = "";
	msgs.push_back(buf[0]);
	msgs.push_back(buf[1]);

	ge::Vector2i otherPos;
	if (msgs[0] == SYNC_POSITION_NOTIFICATION[0] && msgs[1] == SYNC_POSITION_NOTIFICATION[1])
	{
		std::string posString = "";
		for (int i = 3; i < BUFLEN; i++)
		{
			posString += buf[i];
		}
		ge::Vector2i pos; 
		pos.parse(posString);
		TransformSystem::syncOtherPosition(pos);

		return true;
	}
	return false;
}
