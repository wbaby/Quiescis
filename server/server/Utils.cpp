#include <iostream>
#include <windows.h>
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
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;

	return false;
}