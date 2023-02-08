#pragma once

#include "Log.h"

Log::Log(string InsFilePath) : sFilePath(InsFilePath), LogFile(sFilePath, ios_base::in | ios_base::out | ios_base::app)
{
	if (!LogFile)
		cerr << "Failed to open log file streams \n";
}

bool Log::Write(string InsData)
{
	if (CheckFile())
	{
		LogFile << InsData;

		LogFile.close();

		return true;
	}

	return false;

}

string Log::Read()
{
	string sReadData;

	if (CheckFile())
	{

		while (!LogFile.eof())
		{
			LogFile >> sReadData;
		}

		LogFile.close();
	}

	return sReadData;
}

bool Log::CheckFile()
{
	if (!LogFile)
	{
		cerr << "File object handler failed to init \n";

		return false;
	}
	else
	{
		LogFile.open(sFilePath, ios_base::in | ios_base::out | ios_base::app);

		if (!LogFile.is_open())
		{
			cerr << "File failed to open, File - " << sFilePath << "\n";
			return false;
		}
	}

	return true;
}