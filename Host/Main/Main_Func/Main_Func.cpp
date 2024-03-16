#include "Main_Func.h"

SOCKET Create_Socket()
{
	std::cout << "\n=== Step 2 - Set up Server Socket === \n";

	SOCKET serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)
	{
		std::cout << "Server :Error at socket():" << WSAGetLastError() << '\n';
		WSACleanup();
		return 0;
	}
	else
	{
		std::cout << "\nServer :socket() is OK!\n";
		return serverSocket;
	}
}

sockaddr_in Bind_Socket(int port, SOCKET serverSocket)
{

	std::cout << "\n=== Step 3 - Bind Socket ===\n";

	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr); // 55555
	service.sin_port = htons(port);
	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		sockaddr_in ERROR_SOCK;
		ERROR_SOCK.sin_port = 0;
		std::cout << "\nServer :bind() failed: " << WSAGetLastError() << '\n';
		return ERROR_SOCK;
	}
	else
	{
		std::cout << "\nServer :bind() is OK!\n";
		return service;
	}
}


int Listening(SOCKET serverSocket)
{
	int Conns_nr = 1;

	std::cout << "\n=== Step 4 - Initiate Listen ===\n";

	if (listen(serverSocket, Conns_nr) == SOCKET_ERROR)
	{
		std::cout << "\nlisten():Error listening socket" << WSAGetLastError() << '\n';
		return -1;
	}
	else
	{
		std::cout << "\nlisten() is OK, I'm waiting for connections... \n";
		return Conns_nr;
	}
}


SOCKET Accept_Area(SOCKET serverSocket, int Conns_nr)
{
	std::cout << "\n=== Step 5 - Accept Connections ===\n";


	std::cout << "\nAccepting connections...";
	SOCKET clientSocket;
	clientSocket = accept(serverSocket, NULL, NULL);

	--Conns_nr;

	if (clientSocket == INVALID_SOCKET)
	{
		std::cout << "\nAccept failed: " << WSAGetLastError() << '\n';
		WSACleanup();
		return 0;
	}
	std::cout << "\nAccepted connection\n";
	return clientSocket;
}


int Blocking_Connection(char * clientIP, SOCKET clientSocket) 
{
	std::cout << "Blocked connection from: " << clientIP << '\n';
	const char* BLock_Message = "BLOCKED";
	int BLsbytesCount = send(clientSocket, BLock_Message, 8, 0);

	if (BLsbytesCount == SOCKET_ERROR)
	{
		printf("\nServer send error :%ld.\n", WSAGetLastError());
		return 1;
	}
	else
	{
		printf("Server sent message to blocked IP: %s successfully ", clientIP);
		return 0;
	}
}


int Accepting_Connection(const char* clientIP, SOCKET clientSocket) 
{
	std::cout << "Accepted connection from: " << clientIP << '\n';

	const char* ACock_Message = "ACCEPTED";

	int ACsbytesCount = send(clientSocket, ACock_Message, 9, 0);

	if (ACsbytesCount == SOCKET_ERROR)
	{
		printf("\nServer send error :%ld.\n", WSAGetLastError());
		return 1;
	}
	else
	{
		printf("Server sent message to accepted IP: %s successfully ", clientIP);
		return 0;
	}

};


int Receiving_Message(SOCKET clientSocket, char* received_Buffer, const int LEN_MESSG)
{
	int rbyteCount = recv(clientSocket, received_Buffer, LEN_MESSG, 0);

	if (rbyteCount < 0)
	{
		printf("\nClient:error%ld.\n", WSAGetLastError());
		return 1;
	}
	else
	{
		//printf("\nReceived data: %s \n", received_Buffer);
		printf("Client: %s\n", received_Buffer);
		return 0;
	}
}

int Send_Message(char * send_Buffer, const int LEN_MESSG, SOCKET clientSocket)
{
	printf("Server : ");
	std::cin.getline(send_Buffer, LEN_MESSG);
	int sbytesCount = send(clientSocket, send_Buffer, LEN_MESSG, 0);

	if (sbytesCount == SOCKET_ERROR)
	{
		printf("\nServer send error :%ld.\n", WSAGetLastError());
		return 1;
	}
	return 0;
}

void Firewall_Commands(Firewall FR)
{
	std::cout << "Setarile Firewall-ului:\n";
	std::cout << "[1].Adaugare IP+Port\n[2].Adaugare IP\n[3].Adaugare Port\n[4].Stergere IP+Port\n[5].Stergere IP\n[6].Stergere Port\n[7].Iesire Setari Firewall\n";
	char optiune = '8';


	while (optiune != '7')
	{
		std::cout << "\nDati optiunea dorita: "; std::cin >> optiune;

		switch (optiune)
		{
			case '1':
			{
				FR.AddBlocked_IP_Port();break;
			}
			case '2':
			{
				FR.AddBlockedIP();break;
			}
			case '3':
			{
				FR.AddBlocked_Port();break;
			}
			case '4':
			{
				
				FR.Deleting_Ip_Port();
				break;
			}
			case '5':
			{
				FR.Deleting_IP();
				break;
			}
			case '6':
			{
				FR.Deleting_Port();
				break;
			}

			case '7':
			{
				std::cout << "\nAti iesit din setarile Firewall-ului\n";
				break;
			}
			case '8': break;

			default: {std::cout << "\nAti introdus optiunea gresita!!\n";break;}


		}
	}
}