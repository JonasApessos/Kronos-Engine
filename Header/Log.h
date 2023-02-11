#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <filesystem>
#include "Primitives.h"

using KronosPrim::uint8, KronosPrim::int32, KronosPrim::uint32;
using std::cout, std::cerr;
using std::ios_base, std::fstream, std::string, std::getline, std::error_code;
using std::filesystem::create_directory, std::filesystem::exists, std::filesystem::space, std::filesystem::space_info;

enum ELogSeverity : uint8
{
	ELS_Info = 0,
	ELS_Warning = 1,
	ELS_Error = 2,
	ELS_Critical = 3
};

class Log
{
public:
	string sLogName = "";

	Log();
	Log(const string& InsLogName, const string& InsFilePath, const string& InsFileName);
	Log(const string& InsLogName, const string& InsFilePath, const string& InsFileName, int32 IniBitFlagMode);
	Log(Log&& InrLog) noexcept;
	Log(const Log& InrLog);

	~Log();

	Log& operator=(Log&& InrLog) noexcept;

	//Write to log file at specified file in construction
	//by default INFO seveoity level is used
	bool Write(const string& InsData);
	//version with custom severity
	bool Write(const string& InsData, ELogSeverity IneLogSeverity);

	//Write to log file at specified file in construction
	//by default INFO seveoity level is used
	//dislay to console the log after writing
	bool WriteAndDisplay(const string& InsData);
	//version with custom severity
	bool WriteAndDisplay(const string& InsData, ELogSeverity);

	//Read and return buffer string with log message
	string Read();

	//Display log message directly to console
	void Display();

	//Translate enum severity level to string
	void TranslateSeverity(ELogSeverity IneLogSeverity, string& InsTranslatedString);

protected:
	char cTimeBuffer[32] = "";
	char cErrorMsg[256] = "";

	int32 iBitFlagMode = ios_base::in | ios_base::out | ios_base::app;

	uint32 iMinFileSizeBytes = 4194304;

	time_t rTime = 0;
	tm rTimeStruct = tm();

	bool CheckFile();

	void ShowErrorCode(const string& InsCustomErrorMessage);

private:
	fstream* rLogFile;
	string sFileName;
	string sFilePath;
	error_code rErrorCode;

	void Initialization();
};