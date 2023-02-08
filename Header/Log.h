#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Primitives.h"

using KronosPrim::int32;
using std::cout, std::cerr, std::ios_base, std::fstream, std::string, std::getline;

class Log
{
public:
	Log(string InsFilePath);

	bool Write(string InsData);
	string Read();


protected:

	bool CheckFile();

private:
	fstream LogFile;
	string sFilePath;
};