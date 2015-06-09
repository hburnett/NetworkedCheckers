#include "WindowsIncludes.h"
#include "Game.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "RakPeerInterface.h"

#define MAX_CLIENTS 1
#define SERVER_PORT 60007

int main(int argc, char** argv)
{
	char str[512];
	RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
	bool isServer;
	RakNet::Packet *packet;

	printf("(C) or (S)erver?\n");
	gets(str);

	std::string title;

	if ((str[0] == 's') || (str[0] == 'S'))
	{
		RakNet::SocketDescriptor sd(SERVER_PORT, 0);
		peer->Startup(MAX_CLIENTS, &sd, 1);
		isServer = true;
		title = "Networked Checkers Server";
	}

	// Sets user to client by default
	else {
		RakNet::SocketDescriptor sd;
		peer->Startup(1, &sd, 1);
		isServer = false;
		title = "Networked Checkers Client";
	}

	if (isServer)
	{
		printf("Starting the server.\n");
		// We need to let the server accept incoming connections from the clients
		peer->SetMaximumIncomingConnections(MAX_CLIENTS);
	}

	else {
		printf("Enter server IP or hit enter for 127.0.0.1\n");
		gets(str);
		if (str[0] == 0)
		{
			strcpy(str, "127.0.0.1");
		}
		printf("Starting the client.\n");
		peer->Connect(str, SERVER_PORT, 0, 0);

	}

	Game *newGame = new Game(900, 900, title.c_str(), false, isServer, peer);

	newGame->RunGame();
	delete newGame;

	return 0;
}