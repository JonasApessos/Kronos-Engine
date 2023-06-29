#include "Log.h"

Log::Log() : 
rLogFile("Log/","Log.txt", ios_base::in | ios_base::out | ios_base::app) { Initialization(); }

Log::Log(string const& InsLogName) : 
rLogFile("Log/","Log.txt", ios_base::in | ios_base::out | ios_base::app),
sLogName(InsLogName) { Initialization(); }

Log::Log(
	string const& InsLogName,
	string const& InsFilePath,
	string const& InsFileName) :
	sLogName(InsLogName),
	rLogFile(InsFilePath, InsFileName, ios_base::in | ios_base::out | ios_base::app) { Initialization(); }

Log::Log(
	string const& InsLogName,
	string const& InsFilePath,
	string const& InsFileName,
	int32 IniBitFlagMode) :
	sLogName(InsLogName),
	rLogFile(InsFilePath, InsFileName, ios_base::in | ios_base::out | ios_base::app) { Initialization(); }

Log::Log(Log&& InrLog) noexcept : 
	sLogName(InrLog.sLogName) { rLogFile = InrLog.rLogFile; }

Log::Log(Log const& InrLog) :
	sLogName(InrLog.sLogName) { rLogFile = InrLog.rLogFile; }

Log::~Log() {}

Log& Log::operator=(Log&& InrLog) noexcept
{
	if (this != &InrLog)
	{
		rLogFile = InrLog.rLogFile;
		sLogName = InrLog.sLogName;
	}

	return *this;
}

Log& Log::operator=(Log const& InrLog) noexcept
{
	rLogFile = InrLog.rLogFile;

	sLogName = InrLog.sLogName;

	return *this;
}

bool Log::Write(string const& InsData)
{
	//if pass custom checks and input data is not empty
	if (!InsData.empty())
	{
		ERRORCODE iErrorCode = 0;
		tm* rTimeStruct;
		string sSeverity = "";
		string sMsg = "";

		TranslateSeverity(ELogSeverity::ELS_Info, sSeverity);

		//get time since eppoch using C function
		rTimeStruct = localtime(&rTime);

		//check if localtime_s returned an error code
		#ifdef _WIN32
		if (iErrorCode)
		{
			strerror_s(cErrorMsg, sizeof(cErrorMsg), iErrorCode);
			cerr << "[LogException] " << cErrorMsg << "\r\n";
		}
		#elif defined __linux__
		//check if localtime_s returned an error code
		if (iErrorCode)
		{
			cErrorMsg = strerror(iErrorCode);
			cerr << "[LogException] " << cErrorMsg << "\r\n";
		}
		#endif

		//format the eppoch time to a string format with structure date and time
		strftime(cTimeBuffer, sizeof(cTimeBuffer), "%d/%m/%y - %T", rTimeStruct);

		sMsg.append("[" + sLogName + "]" + "[" + sSeverity + "]" + "[" + cTimeBuffer + "]: " + InsData + "\r\n");

		rLogFile.Write(sMsg);

		return true;
	}
	else
		cerr << "[LogException] Failed to write Log\r\n";

	return false;

}

bool Log::Write(string const& InsData, ELogSeverity IneLogSeverity)
{
	//if pass custom checks and input data is not empty
	if (!InsData.empty())
	{
		ERRORCODE iErrorCode = 0;
		tm* rTimeStruct;
		string sSeverity = "";
		string sMsg = "";

		TranslateSeverity(IneLogSeverity, sSeverity);

		//rLogFile->open(sFilePath + sFileName, static_cast<ios_base::openmode>(iBitFlagMode));

		//get time since eppoch using C function
		rTimeStruct = localtime(&rTime);

		//check if localtime_s returned an error code
		#ifdef _WIN32
		if (iErrorCode)
		{
			strerror_s(cErrorMsg, sizeof(cErrorMsg), iErrorCode);
			cerr << "[LogException] " << cErrorMsg << "\r\n";
		}
		#elif defined __linux__
		//check if localtime_s returned an error code
		if (iErrorCode)
		{
			cErrorMsg = strerror(iErrorCode);
			cerr << "[LogException] " << cErrorMsg << "\r\n";
		}
		#endif
		
		//format the eppoch time to a string format with structure date and time
		strftime(cTimeBuffer, sizeof(cTimeBuffer), "%d/%m/%y - %T", rTimeStruct);

		sMsg.append("[" + sLogName + "]" + "[" + sSeverity + "]" + "[" + cTimeBuffer + "]: " + InsData + "\r\n");

		rLogFile.Write(sMsg);

		return true;
	}
	else
		cerr << "[LogException] Failed to write Log\r\n";

	return false;
}

bool Log::WriteAndDisplay(string const& InsData)
{
	//if pass custom checks and input data is not empty
	if (!InsData.empty())
	{
		ERRORCODE iErrorCode = 0;
		tm* rTimeStruct;
		string sSeverity = "";
		string sMsg = "";

		TranslateSeverity(ELogSeverity::ELS_Info, sSeverity);

		//get time since eppoch using C function
		rTimeStruct = localtime(&rTime);

		//check if localtime_s returned an error code
		#ifdef _WIN32
		if (iErrorCode)
		{
			strerror_s(cErrorMsg, sizeof(cErrorMsg), iErrorCode);
			cerr << "[LogException] " << cErrorMsg << "\r\n";
		}
		#elif defined __linux__
		//check if localtime_s returned an error codes
		if (iErrorCode)
		{
			cErrorMsg = strerror(iErrorCode);
			cerr << "[LogException] " << cErrorMsg << "\r\n";
		}
		#endif
		
		//format the eppoch time to a string format with structure date and time
		strftime(cTimeBuffer, sizeof(cTimeBuffer), "%d/%m/%y - %T", rTimeStruct);

		sMsg.append("[" + sLogName + "]" + "[" + sSeverity + "]" + "[" + cTimeBuffer + "]: " + InsData + "\r\n");

		rLogFile.Write(sMsg);

		cerr << sMsg;

		return true;
	}
	else
		cerr << "[LogException] Failed to write Log\r\n";

	return false;
}

bool Log::WriteAndDisplay(string const& InsData, ELogSeverity IneLogSeverity)
{
	//if pass custom checks and input data is not empty
	if (!InsData.empty())
	{
		ERRORCODE iErrorCode = 0;
		tm* rTimeStruct;
		string sSeverity = "";
		string sMsg = "";

		TranslateSeverity(IneLogSeverity, sSeverity);

		//get time since eppoch using C function
		rTimeStruct = localtime(&rTime);

		//check if localtime_s returned an error code
		#ifdef _WIN32
		if (iErrorCode)
		{
			strerror_s(cErrorMsg, sizeof(cErrorMsg), iErrorCode);
			cerr << "[LogException] " << cErrorMsg << "\r\n";
		}
		#elif defined __linux__
		//check if localtime_s returned an error code
		if (iErrorCode)
		{
			cErrorMsg = strerror(iErrorCode);
			cerr << "[LogException] " << cErrorMsg << "\r\n";
		}
		#endif

		//format the eppoch time to a string format with structure date and time
		strftime(cTimeBuffer, sizeof(cTimeBuffer), "%d/%m/%y - %T", rTimeStruct);

		sMsg.append("[" + sLogName + "]" + "[" + sSeverity + "]" + "[" + cTimeBuffer + "]: " + InsData + "\r\n");

		rLogFile.Write(sMsg);

		cerr << sMsg;

		return true;
	}
	else
		cerr << "[LogException] Failed to write to file\r\n";

	return false;
}

void Log::Display()
{
	cout << rLogFile.Read();
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

void Log::Initialization(){ rTime = time(0);}