#pragma once

#include "Log.h"

Log::Log(string InsFilePath, int32 IniBitFlagMode) : sFilePath(InsFilePath), iBitFlagMode(IniBitFlagMode)
{
	if (!LogFile)
		cerr << "Failed to open log file streams \n";

	rTime = time(0);
}

Log::~Log()
{
	if (LogFile.is_open())
		LogFile.close();

	LogFile.clear();
}

bool Log::Write(string InsData)
{
	if (CheckFile() && !InsData.empty())
	{
		tm rTimeStruct;
		LogFile.open(sFilePath, iBitFlagMode);

		localtime_s(&rTimeStruct, &rTime);
		strftime(cTimeBuffer, sizeof(cTimeBuffer), "%d/%m/%y - %T", &rTimeStruct);

		LogFile << "[" << cTimeBuffer << "]: " << InsData << "\n\r";

		LogFile.close();

		return true;
	}

	return false;

}

string Log::Read()
{
	string sReadData;
	string Line;

	if (CheckFile())
	{
		LogFile.open(sFilePath, iBitFlagMode);

		while (getline(LogFile, Line))
			sReadData.append("\n"+Line);

		LogFile.close();
	}

	return sReadData;
}

bool Log::CheckFile()
{
	if (!LogFile)
	{
		cerr << "File object handler failed to init " << LogFile.rdstate() << "\n";

		return false;
	}

	return true;
}