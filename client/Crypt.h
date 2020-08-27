#ifndef CRYPT_H
#define CRYPT_H

#include <string>


std::string CryptFile(std::string path, int key);
std::string CryptDir(std::string path, int key);

#endif