#pragma once

#define __STDC_WANT_LIB_EXT1__ 1

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <filesystem>
#include <cstring>
#include <errno.h>
#include "Primitives.h"

using KronosPrim::int32, KronosPrim::uint32;
using std::cout, std::cerr;
using std::ios_base, std::fstream, std::string, std::getline, std::error_code, std::strerror;
using std::filesystem::create_directory, std::filesystem::exists, std::filesystem::space, std::filesystem::space_info;

enum ELogSeverity : uint32
{
	ELS_Info = 0,
	ELS_Warning = 1,
	ELS_Error = 2,
	ELS_Critical = 3
};

class Log
{
public:

	int32 iBitFlagMode = ios_base::in | ios_base::out | ios_base::app;

	string sFileName = "Log.txt";
	string sFilePath = "Log/";

	string sLogName = "LogDefault";

	Log();
	Log(string const& InsLogName);
	Log(string const& InsLogName, string const& InsFilePath, string const& InsFileName);
	Log(string const& InsLogName, string const& InsFilePath, string const& InsFileName, int32 IniBitFlagMode);
	Log(Log&& InrLog) noexcept;
	Log(Log const& InrLog);

	~Log();

	Log& operator=(Log const& InrLog) noexcept;
	Log& operator=(Log&& InrLog) noexcept;

	//Write to log file at specified file in construction
	//by default INFO severity level is used
	bool Write(string const& InsData);
	//version with custom severity
	bool Write(string const& InsData, ELogSeverity IneLogSeverity);

	//Write to log file at specified file in construction
	//by default INFO severity level is used
	//dislay to console the log after writing
	bool WriteAndDisplay(string const& InsData);
	//version with custom severity
	bool WriteAndDisplay(string const& InsData, ELogSeverity);

	//Read and return buffer string with log message
	string Read();

	//Display log message directly to console
	void Display();

	//Translate enum severity level to string
	void TranslateSeverity(ELogSeverity IneLogSeverity, string& InsTranslatedString);

	//Set
	inline void SetBitFlagMode(int32 IniBitFlagMode);
	inline void SetFileName(string const& InsFileName);
	inline void SetFilePath(string const& InsFileName);
	inline void SetLogName(string const& InsLogName);

	//Get
	inline int32 GetBitFlagMode() const;
	inline string GetFileName() const;
	inline string GetFilePath() const;
	inline string GetLogName() const;

protected:
	char cTimeBuffer[32] = "";

	#ifdef _WIN32
	char cErrorMsg[256] = "";
	#elif defined __linux__
	char* cErrorMsg;
	#endif
	

	uint32 iMinFileSizeBytes = 4194304;

	time_t rTime = 0;
	tm rTimeStruct = tm();

	bool CheckFile();

	void ShowErrorCode(string const& InsCustomErrorMessage);

private:
	fstream* rLogFile;
	error_code rErrorCode;

	void Initialization();
};


inline void Log::SetBitFlagMode(int32 IniBitFlagMode) { iBitFlagMode = IniBitFlagMode; }
inline void Log::SetFileName(string const& InsFileName) { sFileName = InsFileName; }
inline void Log::SetFilePath(string const& InsFilePath) { sFilePath = InsFilePath; }
inline void Log::SetLogName(string const& InsLogName) { sLogName = InsLogName; }

inline int32 Log::GetBitFlagMode() const { return iBitFlagMode; }
inline string Log::GetFileName() const { return sFileName; }
inline string Log::GetFilePath() const { return sFilePath; }
inline string Log::GetLogName() const { return sLogName; }