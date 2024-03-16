#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>   // for _T
#include <iostream>
#include "Main_funcs\FUNCS.h"

#define LEN_MESSG 50


int main() {

	int port = 55555;

	////////////////  Loading DLL

	std::cout << "======= W11 Sockets =======\n";
	std::cout << "========= Client ==========\n";
	std::cout << "=== Step 1 - Set up DLL ===\n\n";

	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);

	if (wsaerr != 0) 
	{
		std::cout << "The Winsock dll not found!" << '\n';
		return 0;
	}
	else 
	{
		std::cout << "The Winsock dll found!\n";
		std::cout << "The status:" << wsaData.szSystemStatus << '\n';
	}

	//////////////// Creating Socket

	SOCKET clientSocket = Create_Socket();

	//////////////// Connect to server
	std::cout << "Type the port to connect to:";
	std::cin >> port;
	sockaddr_in clientService = Connecting_Client(port, clientSocket);
	if (clientService.sin_port = 0)
	{
		closesocket(clientSocket);
		WSACleanup();
	}
	
	////////////////   Checking if we have bypassed server firewall

	char FWreceived_buffer[LEN_MESSG];
	int FWrbytecount = recv(clientSocket, FWreceived_buffer, LEN_MESSG, 0);

	std::cout <<"Received Firewall_Buffer :"<< FWreceived_buffer;

	if (FWrbytecount < 0)
	{
		printf("\nClient:error%ld.\n", WSAGetLastError());
		return 0;
	}
	else if (  comparing(FWreceived_buffer,"BLOCKED")  )  
	{
		printf("You've been blocked from the server :(. Quitting the program ...");
		closesocket(clientSocket);
		shutdown(clientSocket, 2);
	}
	else if (  comparing(FWreceived_buffer, "ACCEPTED")  )
	{

		////////////////     Send Example TCP

		char send_Buffer[LEN_MESSG];
		char received_Buffer[LEN_MESSG];

		while (1) 
		{

			if (Send_Message(send_Buffer, LEN_MESSG, clientSocket)) {closesocket(clientSocket);WSACleanup(); return -1; }

			////////////////     Receive Example TCP

			if (Receiving_Message(clientSocket, received_Buffer, LEN_MESSG)) {closesocket(clientSocket);WSACleanup(); return 0; }
		}
	}

	//////////////  Close Socket

	std::cout << "\n{Client's connection program has stopped working}";

	WSACleanup();
	closesocket(clientSocket);
	shutdown(clientSocket,2);
	return 0;
}