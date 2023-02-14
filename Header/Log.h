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

	int32 iBitFlagMode = ios_base::in | ios_base::out | ios_base::app;

	string sFileName = "Log.txt";
	string sFilePath = "Log/";

	string sLogName = "LogDefault";

	Log();
	Log(const string& InsLogName);
	Log(const string& InsLogName, const string& InsFilePath, const string& InsFileName);
	Log(const string& InsLogName, const string& InsFilePath, const string& InsFileName, int32 IniBitFlagMode);
	Log(Log&& InrLog) noexcept;
	Log(const Log& InrLog);

	~Log();

	Log& operator=(const Log& InrLog) noexcept;
	Log& operator=(Log&& InrLog) noexcept;

	//Write to log file at specified file in construction
	//by default INFO severity level is used
	bool Write(const string& InsData);
	//version with custom severity
	bool Write(const string& InsData, ELogSeverity IneLogSeverity);

	//Write to log file at specified file in construction
	//by default INFO severity level is used
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

	//Set
	inline void SetBitFlagMode(int32 IniBitFlagMode);
	inline void SetFileName(const string& InsFileName);
	inline void SetFilePath(const string& InsFileName);
	inline void SetLogName(const string& InsLogName);

	//Get
	inline int32 GetBitFlagMode() const;
	inline string GetFileName() const;
	inline string GetFilePath() const;
	inline string GetLogName() const;

protected:
	char cTimeBuffer[32] = "";
	char cErrorMsg[256] = "";

	uint32 iMinFileSizeBytes = 4194304;

	time_t rTime = 0;
	tm rTimeStruct = tm();

	bool CheckFile();

	void ShowErrorCode(const string& InsCustomErrorMessage);

private:
	fstream* rLogFile;
	error_code rErrorCode;

	void Initialization();
};


inline void Log::SetBitFlagMode(int32 IniBitFlagMode) { iBitFlagMode = IniBitFlagMode; }
inline void Log::SetFileName(const string& InsFileName) { sFileName = InsFileName; }
inline void Log::SetFilePath(const string& InsFilePath) { sFilePath = InsFilePath; }
inline void Log::SetLogName(const string& InsLogName) { sLogName = InsLogName; }

inline int32 Log::GetBitFlagMode() const { return iBitFlagMode; }
inline string Log::GetFileName() const { return sFileName; }
inline string Log::GetFilePath() const { return sFilePath; }
inline string Log::GetLogName() const { return sLogName; }