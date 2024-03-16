#include "FUNCS.h"
#include <string.h>


int comparing(const char* recv, const char* source)
{
	int flag = 1;
	for (int i = 0; source[i] != '\0'; i++)
	{
		if (recv[i] != source[i])
		{
			flag = 0;
		}
	}
	return flag;
};

SOCKET Create_Socket()
{
	std::cout << "\n=== Step 2 - Set up Server Socket === \n";

	SOCKET clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET)
	{
		std::cout << "Client :Error at socket():" << WSAGetLastError() << '\n';
		WSACleanup();
		return 0;
	}
	else
	{
		std::cout << "\nClient :socket() is OK!\n";
		return clientSocket;
	}
}


sockaddr_in Connecting_Client(int port, SOCKET clientSocket)
{
	std::cout << "\n=== Step 3 - Connect to the Server ===\n";


	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port); // 55555

	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
	{
		std::cout << "\nClient: connect() - Failed to connect.\n";
		sockaddr_in ERROR_SOCK;
		ERROR_SOCK.sin_port = 0;
		return ERROR_SOCK;
	}
	else
	{
		std::cout << "\nClient: connect() is OK \n";
		std::cout << "\nClient: Can start sending and receiving data... \n";
		return clientService;
	}

}

int Receiving_Message(SOCKET clientSocket, char* received_Buffer, const int LEN_MESSG) {

	int rbyteCount = recv(clientSocket, received_Buffer, LEN_MESSG, 0);

	if (rbyteCount < 0)
	{
		printf("\nClient:error%ld.\n", WSAGetLastError());
		return 1;
	}
	else
	{
		//printf("\nReceived data: %s \n", received_Buffer);
		printf("Server: %s\n", received_Buffer);
		return 0;
	}
}

int Send_Message(char* send_Buffer, const int LEN_MESSG, SOCKET clientSocket)
{
	printf("\nClient : ");
	std::cin.getline(send_Buffer, LEN_MESSG);
	int sbytesCount = send(clientSocket, send_Buffer, LEN_MESSG, 0);

	if (sbytesCount == SOCKET_ERROR)
	{
		printf("\nServer send error :%ld.\n", WSAGetLastError());
		return 1;
	}
	return 0;
}