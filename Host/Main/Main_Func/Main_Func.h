#pragma once

#ifndef MAINFUNC_H
#define MAINFUNC_H
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>   // for _T
#include <stdio.h>
#include "W:\Cpp\VS\TCP Server\Server\Server\Firewall\Firewall.h"


SOCKET Create_Socket();

sockaddr_in Bind_Socket(int port, SOCKET serverSocket);

int Listening(SOCKET serverSocket);

int Blocking_Connection(char* clientIP, SOCKET clientSocket);

int Accepting_Connection(const char* clientIP, SOCKET clientSocket);

int Receiving_Message(SOCKET clientSocket, char* received_Buffer, const int LEN_MESSG);

int Send_Message(char* send_Buffer, const int LEN_MESSG, SOCKET clientSocket);

SOCKET Accept_Area(SOCKET serverSocket, int Conns_nr);



void Firewall_Commands(Firewall FR);

#endif