#pragma once
#ifndef FUNCS_H
#define FUNCS_H
	#include <iostream>
	#include <WinSock2.h>
	#include <WS2tcpip.h>
	#include <tchar.h>   // for _T
	#include <stdio.h>


	int comparing(const char* recv, const char* source);
	SOCKET Create_Socket();
	sockaddr_in Connecting_Client(int port, SOCKET clientSocket);
	int Receiving_Message(SOCKET clientSocket, char* received_Buffer, const int LEN_MESSG);
	int Send_Message(char* send_Buffer, const int LEN_MESSG, SOCKET clientSocket);


#endif  // FUNCS_H
