#ifndef __linux__
	#include <windows.h>
#else
	#include <dirent.h>
#endif

#include <iostream>
#include <fstream>
#include <string>

void throw_error(const char* error_text) {
#ifndef __linux__
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "error: ";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << error_text << std::endl;
#else
	std::cout << red << "error: " << st_end << error_text << std::endl;
#endif
	exit(1);
}

bool dirExists(const std::string& dirName_in) {
#ifdef __linux__
	DIR* dir = opendir(dirName_in.c_str());
	if (dir) {
		closedir(dir);
		return true;
	} else return false;
#else
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;
	return false;
#endif
}
