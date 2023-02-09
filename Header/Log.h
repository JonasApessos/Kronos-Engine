#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "Primitives.h"

using KronosPrim::int32;
using std::cout, std::cerr, std::ios_base, std::fstream, std::string, std::getline;

class Log
{
public:
	Log(string InsFilePath, int32 IniBitFlagMode);
	~Log();

	bool Write(string InsData);
	string Read();


protected:

	bool CheckFile();

	char cTimeBuffer[64];

	int32 iBitFlagMode = 0;

	time_t rTime;
	tm rTimeStruct;

private:
	fstream LogFile;
	string sFilePath;
};