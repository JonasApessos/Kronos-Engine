#pragma once

#define __STDC_WANT_LIB_EXT1__ 1

#include <iostream>
#include "Primitives.h"
#include "FileHandler.h"

using KronosPrim::int32, KronosPrim::uint32;
using std::cout, std::cerr;

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
	inline void SetLogName(string const& InsLogName);

	//Get
	inline string GetLogName() const;

protected:
	char cTimeBuffer[32] = "";

	#ifdef _WIN32
	char cErrorMsg[256] = "";
	#elif defined __linux__
	char* cErrorMsg;
	#endif
	

	time_t rTime = 0;
	tm rTimeStruct = tm();

private:
	FileHandler rLogFile;

	void Initialization();
};



inline void Log::SetLogName(string const& InsLogName) { sLogName = InsLogName; }


inline string Log::GetLogName() const { return sLogName; }