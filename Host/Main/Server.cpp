#pragma once
#include "Firewall\Firewall.h"
#include "Main_Funcs\Main_Func.h"
#define LEN_MESSG 50


// should've verify the protocol for validation. Client should've sent it to server (



int main() {

	int port = 55555;

	///////////////   SETTING FIREWALL

	Firewall Main_Firewall;

	Firewall_Commands(Main_Firewall);


	////////////////  Loading DLL

	std::cout << "======= W11 Sockets =======\n";
	std::cout << "========= Server ==========\n";
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
		std::cout << "The status:"<<wsaData.szSystemStatus<<'\n';
	}

	//////////////// Creating Socket

	SOCKET serverSocket = Create_Socket();			 

	/////////////////  Bind socket

	sockaddr_in service = Bind_Socket(port, serverSocket);
	if (service.sin_port = 0)
	{
		closesocket(serverSocket);
		WSACleanup();
		shutdown(serverSocket, 2);
	}

	///////////////////   Listen Time

	int Conns_nr = Listening(serverSocket);  
	if (Conns_nr == -1)
	{
		closesocket(serverSocket);
		WSACleanup();
		shutdown(serverSocket, 2);
	}

	//////////////////  Accept Socket

		SOCKET clientSocket = Accept_Area(serverSocket, Conns_nr);	  

	/////////////////        Getting the IP && Port address of the clients

		sockaddr_in clientAddr;
		int clientAddrSize = sizeof(clientAddr);

		if (getpeername(clientSocket, (SOCKADDR*)&clientAddr, &clientAddrSize) == SOCKET_ERROR)
		{
			std::cout << "[Checking]:Error peering socket - "<< WSAGetLastError() << '\n';
			closesocket(clientSocket);
			shutdown(serverSocket, 2);
		}

		char clientIP[INET_ADDRSTRLEN];// 15
		char clientPort[6];
		inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN);
		int client_port = ntohs(clientAddr.sin_port);
		sprintf(clientPort, "%d", client_port);

		std::cout <<"Client Port:" << clientPort<<'\n';

		std::cout << "Connection from: " << clientIP << '\n';


	
		
	//////////////  Checking if IP && port is blocked by Firewall

		if (Main_Firewall.IsBlockedIP(clientIP) || Main_Firewall.IsBlocked_Ip_Port(clientIP, clientPort) || Main_Firewall.IsBlockedPort(clientPort) )
		{
			if (Blocking_Connection(clientIP, clientSocket)) { closesocket(clientSocket);WSACleanup(); }  // if blocked, send message to client about that
			closesocket(clientSocket);
			shutdown(serverSocket, 2);
		}
		else
		{
			if (Accepting_Connection(clientIP, clientSocket)) { closesocket(clientSocket);WSACleanup(); } // Otherwise, send message of acceptance

	////////////////     Receive 

			std::cout << "\n=== Step 6 - Receiving Message ===\n";

			std::cout << "Enter your Messages after Client:\n";

			char received_Buffer[LEN_MESSG];
			char send_Buffer[LEN_MESSG];
			
			while (1)
			{
				if (Receiving_Message(clientSocket, received_Buffer, LEN_MESSG)) { closesocket(serverSocket);closesocket(clientSocket);WSACleanup(); return -1; }

				////////////////     Send 

				if (Send_Message(send_Buffer, LEN_MESSG, clientSocket)) { closesocket(serverSocket); closesocket(clientSocket);WSACleanup(); return -1; }
				
			}
			
		}
	
	////     Close Socket
	
	std::cout << "Server has been shutted out";

	WSACleanup();
	closesocket(clientSocket);
	closesocket(serverSocket);
	shutdown(serverSocket, 2);

	return 0;
}