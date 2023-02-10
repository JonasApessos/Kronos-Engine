#pragma once

#include "Log.h"

Log::Log()
{
	//cTimeBuffer = "";
	//cErrorMsg = "";
}

Log::Log(
	const string& InsLogName,
	const string& InsFilePath,
	const string& InsFileName,
	int32 IniBitFlagMode) :
	sLogName(InsLogName),
	cTimeBuffer(""),
	cErrorMsg(""),
	iBitFlagMode(IniBitFlagMode),
	sFilePath(InsFilePath),
	sFileName(InsFileName)
	
{

	//If folder does not exists, create it
	if (!exists(sFilePath))
	{
		if (!create_directory(InsFilePath, rErrorCode))
			ShowErrorCode("Failed to create directory");
	}

	//if the file does not exists, create it
	if (!exists(sFilePath + sFileName))
	{
		LogFile.open(sFilePath + sFileName, iBitFlagMode);
		LogFile.close();
	}

	//custom check file to see if previous steps are ok
	if (CheckFile())
	{
		if (!LogFile)
			cerr << "File object handler failed to init " << LogFile.rdstate() << "\r\n";
	}
		

	rTime = time(0);
}

Log::Log(Log&& InrLog)
{

}

Log::Log(const Log& InrLog)
{

}

Log::~Log()
{
	//if at some point for some reason the file was not closed
	if (LogFile.is_open())
		LogFile.close();

	LogFile.clear();
}

bool Log::Write(const string& InsData)
{
	//if pass custom checks and input data is not empty
	if (CheckFile() && !InsData.empty())
	{
		errno_t iErrorCode = 1;
		tm rTimeStruct;
		string sSeverity;

		TranslateSeverity(ELogSeverity::ELS_Info, sSeverity);

		LogFile.open(sFilePath + sFileName, iBitFlagMode);

		//get time since eppoch using C function
		iErrorCode = localtime_s(&rTimeStruct, &rTime);

		//check if localtime_s returned an error code
		if (iErrorCode)
		{
			strerror_s(cErrorMsg, sizeof(cErrorMsg), iErrorCode);
			cerr << cErrorMsg << "\r\n";
		}

		//format the eppoch time to a string format with structure date and time
		strftime(cTimeBuffer, sizeof(cTimeBuffer), "%d/%m/%y - %T", &rTimeStruct);


		LogFile << "[" << sLogName << "] " << "[" << sSeverity << "] " << "[" << cTimeBuffer << "]: " << InsData << "\r\n";

		LogFile.close();

		return true;
	}
	else
		cerr << "Failed to write to file\r\n";

	return false;

}

bool Log::Write(const string& InsData, ELogSeverity IneLogSeverity)
{
	//if pass custom checks and input data is not empty
	if (CheckFile() && !InsData.empty())
	{
		errno_t iErrorCode = 1;
		tm rTimeStruct;
		string sSeverity;

		TranslateSeverity(IneLogSeverity, sSeverity);

		LogFile.open(sFilePath + sFileName, iBitFlagMode);

		//get time since eppoch using C function
		iErrorCode = localtime_s(&rTimeStruct, &rTime);

		//check if localtime_s returned an error code
		if (iErrorCode)
		{
			strerror_s(cErrorMsg, sizeof(cErrorMsg), iErrorCode);
			cerr << cErrorMsg << "\r\n";
		}
		
		//format the eppoch time to a string format with structure date and time
		strftime(cTimeBuffer, sizeof(cTimeBuffer), "%d/%m/%y - %T", &rTimeStruct);

		LogFile << "[" << sLogName << "] " << "[" << sSeverity << "] " << "[" << cTimeBuffer << "]: " << InsData << "\r\n";

		LogFile.close();

		return true;
	}
	else
		cerr << "Failed to write to file\r\n";

	return false;
}

bool Log::WriteAndDisplay(const string& InsData)
{
	//if pass custom checks and input data is not empty
	if (CheckFile() && !InsData.empty())
	{
		errno_t iErrorCode = 1;
		tm rTimeStruct;
		string sSeverity;

		TranslateSeverity(ELogSeverity::ELS_Info, sSeverity);

		LogFile.open(sFilePath + sFileName, iBitFlagMode);

		//get time since eppoch using C function
		iErrorCode = localtime_s(&rTimeStruct, &rTime);

		//check if localtime_s returned an error code
		if (iErrorCode)
		{
			strerror_s(cErrorMsg, sizeof(cErrorMsg), iErrorCode);
			cerr << cErrorMsg << "\r\n";
		}

		//format the eppoch time to a string format with structure date and time
		strftime(cTimeBuffer, sizeof(cTimeBuffer), "%d/%m/%y - %T", &rTimeStruct);


		LogFile << "[" << sLogName << "] " << "[" << sSeverity << "] " << "[" << cTimeBuffer << "]: " << InsData << "\r\n";
		cerr << "[" << sLogName << "] " << "[" << sSeverity << "] " << "[" << cTimeBuffer << "]: " << InsData << "\r\n";

		LogFile.close();

		return true;
	}
	else
		cerr << "Failed to write to file\r\n";

	return false;
}

bool Log::WriteAndDisplay(const string& InsData, ELogSeverity IneLogSeverity)
{
	//if pass custom checks and input data is not empty
	if (CheckFile() && !InsData.empty())
	{
		errno_t iErrorCode = 1;
		tm rTimeStruct;
		string sSeverity;

		TranslateSeverity(IneLogSeverity, sSeverity);

		LogFile.open(sFilePath + sFileName, iBitFlagMode);

		//get time since eppoch using C function
		iErrorCode = localtime_s(&rTimeStruct, &rTime);

		//check if localtime_s returned an error code
		if (iErrorCode)
		{
			strerror_s(cErrorMsg, sizeof(cErrorMsg), iErrorCode);
			cerr << cErrorMsg << "\r\n";
		}

		//format the eppoch time to a string format with structure date and time
		strftime(cTimeBuffer, sizeof(cTimeBuffer), "%d/%m/%y - %T", &rTimeStruct);

		LogFile << "[" << sLogName << "] " << "[" << sSeverity << "] " << "[" << cTimeBuffer << "]: " << InsData << "\r\n";
		cerr << "[" << sLogName << "] " << "[" << sSeverity << "] " << "[" << cTimeBuffer << "]: " << InsData << "\r\n";

		LogFile.close();

		return true;
	}
	else
		cerr << "Failed to write to file\r\n";

	return false;
}

string Log::Read()
{
	string sReadData;
	string Line;

	if (CheckFile())
	{
		LogFile.open(sFilePath + sFileName, iBitFlagMode);

		while (getline(LogFile, Line))
			sReadData.append("\r\n" + Line);

		LogFile.close();
	}
	else
		cerr << "Failed to read file\r\n";

	return sReadData;
}

void Log::Display()
{
	string Line;

	if (CheckFile())
	{
		LogFile.open(sFilePath + sFileName, iBitFlagMode);

		while (getline(LogFile, Line))
			cout << Line << "\r\n";

		LogFile.close();
	}
	else
		cerr << "Failed to read file\r\n";
}

void Log::TranslateSeverity(ELogSeverity IneLogSeverity, string& InsTranslatedSeverity)
{
	switch (IneLogSeverity)
	{
		case ELogSeverity::ELS_Info:
			{
				InsTranslatedSeverity = "INFO";
				break;
			}

		case ELogSeverity::ELS_Warning:
			{
				InsTranslatedSeverity = "WARNING";
				break;
			}

		case ELogSeverity::ELS_Error:
			{
				InsTranslatedSeverity = "ERROR";
				break;
			}

		case ELogSeverity::ELS_Critical :
			{
				InsTranslatedSeverity = "CRITICAL";
				break;
			}

		default:
			InsTranslatedSeverity = "INFO";
	}
}

bool Log::CheckFile()
{
	space_info DriveSpaceInfo = space(sFilePath, rErrorCode);

	if (rErrorCode.value() != 0)
		ShowErrorCode("Failed to request drive memory info");

	//check drive if it has enough space (min 4mb)
	if (DriveSpaceInfo.available > iMinFileSizeBytes)
	{
		if (exists(sFilePath + sFileName, rErrorCode))
			return true;
		else
			ShowErrorCode("File not found - Error Category");
	}
	else
		cerr << "Not enough space on current drive \r\n";

	return false;
}

void Log::ShowErrorCode(const string& InsCustomErrorMessage)
{
	cerr << InsCustomErrorMessage << ": Error Category" << rErrorCode.category().name() << ", Code : " << rErrorCode.value() << ", Error : " << rErrorCode.message() << "\r\n";
	rErrorCode.clear();
}