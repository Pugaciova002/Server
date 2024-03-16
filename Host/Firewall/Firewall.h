#pragma once
#ifndef FIREWALL_H
#define FIREWALL_H

#include <iostream>

#include <fstream>
#include <string>

class Firewall {

public:

	//  IP + PORT	Handling

	void AddBlocked_IP_Port();

	bool IsBlocked_Ip_Port(const char* _IP, const char* _PORT);

	void Deleting_Ip_Port();


	//  IP 	Handling

	void AddBlockedIP();

	bool IsBlockedIP(const char* _IP);

	void Deleting_IP();


	//  Port  Handling

	
	void AddBlocked_Port();

	bool IsBlockedPort(const char* _PORT);

	void Deleting_Port();
	
};

#endif // CLASS_H