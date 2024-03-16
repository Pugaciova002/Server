#include "Firewall.h"



std::string Get_Port(std::string line_, int i, std::string Uport);
std::string Get_IP(std::string line_, int i, std::string Uip);
void PORT_IP_VALIDATION(std::string port, std::string ip, std::ofstream& WIF);
std::string IP_VALIDATION(std::string ip, uint8_t count_digits, uint8_t validated_numbers, uint8_t FATAL_ERROR, char* Ip_2byte, uint8_t point, int result[]);
void PORT_VALIDATION(std::string port, std::ofstream& WIF);


/////////////////////////////////////////////////////////////////////////////////////////    ADDING IP && PORTS

void Firewall:: AddBlocked_IP_Port()
{
	std::ofstream WIF("Blocked_IP_Ports.txt", std::ofstream::app);
	std::string ip;
	std::string port;
	char Ip_2byte[4] = "000";
	uint8_t point = 0;		// max == 3
	uint8_t count_digits = 0;   // max == 3
	//uint8_t flag_validation = 1;
	uint8_t validated_numbers = 0;  // max == 4

	uint8_t FATAL_ERROR = 0;  // stops execution if the rules did break
	//  0 - no rules have been broken
	//  1 - broken rules
	int result[2] = {0,0};

	if (WIF.is_open())
	{
		std::cout << "File is open\n";

		if (WIF.good())
		{
			
			ip = IP_VALIDATION(ip, count_digits, validated_numbers, FATAL_ERROR, Ip_2byte, point, result);

			if ((result[0] != 4) || result[1])
			{
				std::cout << "Ati introdus IPv4 gresit.IP-ul trebuie sa contine numere/cifre <256 si 4 puncte ce le delimita.";
			}
			else
			{
				PORT_IP_VALIDATION(port, ip, WIF);
			}
		}
		else
		{
			std::cout << "Nu a fost posibila deschiderea File-ului";
		}
		point = 0;
	}
	WIF.close();

}

void Firewall::AddBlockedIP()
{


	std::ofstream WIF("BLOCKED_ip.txt", std::ofstream::app);
	std::string ip;
	char Ip_2byte[4] = "000";
	uint8_t point = 0;		// max == 3
	uint8_t count_digits = 0;   // max == 3
	//uint8_t flag_validation = 1;
	uint8_t validated_numbers = 0;  // max == 4

	uint8_t FATAL_ERROR = 0;  // stops execution if the rules did break
	//  0 - no rules have been broken
	//  1 - broken rules
	int result[2] = {0,0};

	if (WIF.is_open())
	{
		std::cout << "File is open\n";

		if (WIF.good())
		{
			
			ip = IP_VALIDATION(ip, count_digits, validated_numbers, FATAL_ERROR, Ip_2byte, point, result);

			if ((result[0] != 4) || result[1])
			{
				std::cout << "Ati introdus IPv4 gresit.IP-ul trebuie sa contine numere/cifre <256 si 4 puncte ce le delimita.";
			}
			else
			{
				WIF << ip << "|\n";
			}
		}
		else
		{
			std::cout << "Nu a fost posibila deschiderea File-ului";
		}
		point = 0;
	}
	WIF.close();

}

void Firewall::AddBlocked_Port()
{

	std::ofstream WIF("BLOCKED_PORTS.txt", std::ofstream::app);
	std::string port;
	
	if (WIF.is_open())
	{
		std::cout << "File is open\n";

		if (WIF.good())
		{

			PORT_VALIDATION(port,WIF);
		}
		else
		{
			std::cout << "Nu a fost posibila deschiderea File-ului";
		}
	}
	WIF.close();
}

		/**////////////////////////////////////////////////////////////////////////////////////////  IP && PORT FIREWALL VALIDATION  FOR ADDING

		void PORT_IP_VALIDATION(std::string port, std::string ip, std::ofstream& WIF)
		{

			// Port Validation
			std::cout << "Port:";
			std::cin >> port;
			// used try/catch because stoi is throwing exception = invalid_argument class
			try {

				if (std::stoi(port, 0))
				{
					WIF << ip << "  " << port << "|\n";  // getline doesn't get into account '\n' character? . I can't make the condition with it 
				}
			}
			catch (...)
			{
				std::cerr << "Port introdus invalid";
			}

		}


		// IF something doesn't work properly | to check the uint8_t result[] parameter
		std::string IP_VALIDATION(std::string ip, uint8_t count_digits, uint8_t validated_numbers, uint8_t FATAL_ERROR, char* Ip_2byte, uint8_t point, int result[] )
		{

			std::cout << "Ip:";
			std::cin >> ip;

			//		IP	Validation  

			uint8_t ipIt = 0;

			// first num. validation

			count_digits = 0;
			while (ip[ipIt] != '.')
			{


				if (!isdigit(ip[ipIt]) || count_digits > 4)
				{
					FATAL_ERROR = 1;
					break;
				}
				else
				{
					Ip_2byte[count_digits++] = ip[ipIt++];
				}
			}

			if (!FATAL_ERROR)
			{
				Ip_2byte[count_digits] = '\0';


				if (strtoul(Ip_2byte, nullptr, 0) < 256) { validated_numbers++; ++point; }
			}

			// first - verify if is less < 256 {} second , if all characters are digits => number {} third , if there are max 3 digits.
			// could use stoi, dummy



		// middle && last nums. validation


			ipIt++;  // jumps to next '.'
			uint8_t point_It = ipIt;


			if (validated_numbers && !FATAL_ERROR)
			{
				// .234.234.234

				while (ip[point_It])
				{
					if (ip[point_It] == '.')
						point++;
					++point_It;
				}
				if (point != 3) { FATAL_ERROR = 1; }


				while (ip[ipIt] && point < 4 && !FATAL_ERROR) // != '\0'
				{
					count_digits = 0;

					while (ip[ipIt] != '.' && ip[ipIt] != '\0')
					{
						if (!isdigit(ip[ipIt]) || count_digits > 3)
						{
							FATAL_ERROR = 1;
							break;
						}
						else
						{
							Ip_2byte[count_digits++] = ip[ipIt++];
						}
					}

					if (ip[ipIt] != '\0') { ++ipIt; }		// jumps to next '.'

					if (!FATAL_ERROR)
					{
						Ip_2byte[count_digits] = '\0';

						if (strtoul(Ip_2byte, nullptr, 0) < 256)
						{
							validated_numbers++;
						}
					}
					else
					{
						break;
					}
				}
			}
			result[0] = validated_numbers;
			result[1] = FATAL_ERROR;
			return ip;
		}


		void PORT_VALIDATION(std::string port, std::ofstream& WIF)
		{
			std::cout << "Port:";
			std::cin >> port;
			// used try/catch because stoi is throwing exception = invalid_argument class
			try {

				if (std::stoi(port, 0))
				{
					WIF << port << "|\n";  // getline doesn't get into account '\n' character? . I can't make the condition with it 
				}
			}
			catch (...)
			{
				std::cerr << "Port introdus invalid";
			}
		}

////////////////////////////////////////////////////////////////////////////////////////          DELETING ALL CONTENTS

void Firewall::Deleting_IP()
{
	int optiunea;
	std::cout << "Alegeti optiunea : \n[1].Toate IP-urile\n[2].IP-ul dorit\nOptiunea :";
	std::cin >> optiunea;

	switch (optiunea) {

		case(1): 
		{
			std::ofstream WIF("BLOCKED_ip.txt", std::ifstream::out | std::ofstream::trunc);  // switch will return error because of WIF if not put in braces

			if (!WIF.is_open())
			{
				std::cout << "error opening file";
			}

			WIF.close();
			break;
		}
		case(2):
		{

			char ip[22];
			std::cout << "\nDati ip-ul dorit sters:";
			std::cin >> ip;std::cout << '\n';
			std::string inputFileName = "BLOCKED_ip.txt";
			std::string tempFileName = "temp.txt";

			std::ifstream InputFile(inputFileName);
			std::ofstream TempFile(tempFileName);
			int Flag_Output = 0;

			if (!InputFile.is_open() && !TempFile.is_open())
			{
				std::cerr << "Unable to open required files \n";
			}

			std::string line_;
			while (std::getline(InputFile, line_))
			{
				Flag_Output = 1;
				if (line_.find(ip) == -1)
				{
					TempFile << line_ << '\n';
				}
			}
			InputFile.close();
			TempFile.close();

			if (remove(inputFileName.c_str()) != 0)
			{
				std::cerr << "Eroare la deschidere file-ului original";
			}

			if (rename(tempFileName.c_str(), inputFileName.c_str()) != 0)
			{
				std::cerr << "Eroare la deschidere file-ului temp";
			}


			if (!Flag_Output) { std::cout << "Fisierul nu contine date!!!"; }
		}
	}
}

void Firewall::Deleting_Port()
{
	int optiunea;
	std::cout << "Alegeti optiunea : \n[1].Toate Porturile\n[2].Portul dorit\nOptiunea :";
	std::cin >> optiunea;

	switch (optiunea) {

		case(1):
		{
			std::ofstream WIF("BLOCKED_PORTS.txt", std::ifstream::out | std::ofstream::trunc);  // switch will return error because of WIF if not put in braces

			if (!WIF.is_open())
			{
				std::cout << "error opening file";
			}

			WIF.close();
			break;
		}
		case(2):
		{
			char port[6];
			std::cout << "\nDati Portul dorit sters:";
			std::cin >> port;std::cout << '\n';

			std::string inputFileName = "BLOCKED_PORTS.txt";
			std::string tempFileName = "temp.txt";

			std::ifstream InputFile(inputFileName);
			std::ofstream TempFile(tempFileName);
			int Flag_Output = 0;

			if (!InputFile.is_open() && !TempFile.is_open())
			{
				std::cerr << "Unable to open required files \n";
			}

			std::string line_;
			while (std::getline(InputFile, line_))
			{
				Flag_Output = 1;
				if (line_.find(port) == -1)
				{
					TempFile << line_ << '\n';
				}
			}
			InputFile.close();
			TempFile.close();

			if (remove(inputFileName.c_str()) != 0)
			{
				std::cerr << "Error deleting original file";
			}

			if (rename(tempFileName.c_str(), inputFileName.c_str()) != 0)
			{
				std::cerr << "Error renaming temporary files";
			}


			if (!Flag_Output) { std::cout << "Fisierul nu contine date!!!"; }
		}
	}
}

void Firewall::Deleting_Ip_Port()
{
	int optiunea;
	std::cout << "Alegeti optiunea : \n[1].Toate Porturile\n[2].Portul dorit\nOptiunea :";
	std::cin >> optiunea;
	std::string IP_PORT;



	switch (optiunea) {

	case(1):
	{
		std::ofstream WIF("Blocked_IP_Ports.txt", std::ifstream::out | std::ofstream::trunc);  // switch will return error because of WIF if not put in braces

		if (!WIF.is_open())
		{
			std::cout << "error opening file";
		}

		WIF.close();
		break;
	}
	case(2):
		{

			char ip[22], port[6];
			std::cout << "\nDati ip-ul dorit sters:";
			std::cin >> ip;std::cout << '\n';
			std::cout << "\nDati Portul dorit sters:";
			std::cin >> port;std::cout << '\n';

			IP_PORT += ip;
			IP_PORT += "  ";
			IP_PORT += port;


			std::string inputFileName = "Blocked_IP_Ports.txt";
			std::string tempFileName = "temp.txt";

			std::ifstream InputFile(inputFileName);
			std::ofstream TempFile(tempFileName);
			int Flag_Output = 0;

			if (!InputFile.is_open() && !TempFile.is_open())
			{
				std::cerr << "Unable to open required files \n";
			}

			std::string line_;
			while (std::getline(InputFile, line_))
			{
				Flag_Output = 1;
				if (line_.find(IP_PORT) == -1)
				{
					TempFile << line_ << '\n';
				}
			}
			InputFile.close();
			TempFile.close();

			if (remove(inputFileName.c_str()) != 0)
			{
				std::cerr << "Error deleting original file";
			}

			if (rename(tempFileName.c_str(), inputFileName.c_str()) != 0)
			{
				std::cerr << "Error renaming temporary files";
			}


			if (!Flag_Output) { std::cout << "Fisierul nu contine date!!!"; }
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////  IP && PORT FIREWALL VALIDATION

//  BASED ON THIS MAGIC EXPRESSION      return (blockedIPs.find(ipAddress) != -1);    LOVE IT ;3

bool Firewall::IsBlocked_Ip_Port(const char* _IP, const char* _PORT)
{
	std::ifstream RFF("Blocked_IP_Ports.txt");
	std::string Uip, Uport;
	std::string line_;

	//192.43.23.43  43
	int  i = 0;

	if (RFF.is_open()) {

		while (std::getline(RFF, line_))
		{
			Uip = Get_IP(line_, i, Uip);
			i += 2;				// jump over 2 spaces,and reach the port nr.
			Uport = Get_Port(line_, i, Uport);
			i = 0;
		}
	}
	else
		std::cout << "not opened";
	RFF.close();

	return ((Uport.find(_PORT) != -1) || (Uip.find(_IP) != -1));
}

bool Firewall::IsBlockedPort(const char* _PORT)
{
	std::ifstream RFF("BLOCKED_PORTS.txt");
	std::string Uport;
	std::string line_;
	int  i = 0;

	if (RFF.is_open()) {

		while (std::getline(RFF, line_))
		{
			Uport = Get_Port(line_, i, Uport);
			i = 0;
		}
	}
	else
		std::cout << "not opened";
	RFF.close();
	return (Uport.find(_PORT) != -1);

}

bool Firewall::IsBlockedIP(const char* _IP)
{
	std::ifstream RFF("BLOCKED_ip.txt");
	std::string Uip;
	std::string line_;
	int  i = 0;

	if (RFF.is_open()) {

		while (std::getline(RFF, line_))
		{
			Uip = Get_IP(line_, i, Uip);
			i = 0;
		}
	}
	else
		std::cout << "not opened";
	RFF.close();
	return (Uip.find(_IP) != -1);
}


std::string Get_Port(std::string line_, int i, std::string Uport)
{
	while (line_[i] != '|')
	{
		Uport += line_[i++];
	}
	Uport += '\0';
	return Uport;
}

std::string Get_IP(std::string line_, int i, std::string Uip)
{
	while (line_[i] != '|')
	{
		Uip += line_[i++];
	}
	Uip += '\0';
	return Uip;
}

/////////////////////////////////////////////////////////////////////////////////////////     COMMANDS FOR HANDLING IT