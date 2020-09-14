#ifndef UTILS_H
#define UTILS_H

#include <vector>

// Transformations
std::string wstring_to_string(std::wstring s);
std::wstring string_to_wstring(std::string& s);

// Getting the PID of a process
DWORD GetProcessID(const char* lpNameProcess);
// Getting a list of files and directories in a directory
std::vector<std::string> scandir(std::string p);

inline bool dirExists(const std::string& dirName_in);

#endif // UTILS_H