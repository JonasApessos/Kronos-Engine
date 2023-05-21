#include "Log.h"

Log::Log() 
{
	rLogFile = new fstream();

	Initialization();
}

Log::Log(const string& InsLogName) : sLogName(InsLogName)
{
	rLogFile = new fstream();

	Initialization();
}

Log::Log(
	const string& InsLogName,
	const string& InsFilePath,
	const string& InsFileName) :
	sLogName(InsLogName),
	sFilePath(InsFilePath),
	sFileName(InsFileName)
{
	rLogFile = new fstream();

	Initialization();
}

Log::Log(
	const string& InsLogName,
	const string& InsFilePath,
	const string& InsFileName,
	int32 IniBitFlagMode) :
	sLogName(InsLogName),
	iBitFlagMode(IniBitFlagMode),
	sFilePath(InsFilePath),
	sFileName(InsFileName)	
{
	rLogFile = new fstream();
	Initialization();
}

Log::Log(Log&& InrLog) noexcept : 
	sLogName(InrLog.sLogName),
	sFileName(InrLog.sFileName),
	sFilePath(InrLog.sFilePath),
	iBitFlagMode(InrLog.iBitFlagMode)
{
	rLogFile = InrLog.rLogFile;

	InrLog.rLogFile = nullptr;
}

Log::Log(const Log& InrLog) :
	sLogName(InrLog.sLogName),
	sFilePath(InrLog.sFilePath),
	sFileName(InrLog.sFileName),
	iBitFlagMode(InrLog.iBitFlagMode)
{
	rLogFile = InrLog.rLogFile;
}

Log::~Log()
{
	if (rLogFile != nullptr)
	{
		delete rLogFile;

		rLogFile = nullptr;
	}
}

Log& Log::operator=(Log&& InrLog) noexcept
{
	if (this != &InrLog)
	{
		delete rLogFile;

		rLogFile = InrLog.rLogFile;
		sLogName = InrLog.sLogName;
		sFilePath = InrLog.sFilePath;
		sFileName = InrLog.sFileName;
		iBitFlagMode = InrLog.iBitFlagMode;

		InrLog.rLogFile = nullptr;
	}

	return *this;
}

Log& Log::operator=(const Log& InrLog) noexcept
{
	if (this != &InrLog)
	{
		rLogFile = InrLog.rLogFile;

		sLogName = InrLog.sLogName;
		sFilePath = InrLog.sFilePath;
		sFileName = InrLog.sFileName;
		iBitFlagMode = InrLog.iBitFlagMode;
	}

	return *this;
}

bool Log::Write(const string& InsData)
{
	//if pass custom checks and input data is not empty
	if (CheckFile() && !InsData.empty() && rLogFile != nullptr)
	{
		ERRORCODE iErrorCode = 0;
		tm* rTimeStruct;
		string sSeverity;

		TranslateSeverity(ELogSeverity::ELS_Info, sSeverity);

		rLogFile->open(sFilePath + sFileName, static_cast<ios_base::openmode>(iBitFlagMode));

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


		*rLogFile << "[" << sLogName << "] " << "[" << sSeverity << "] " << "[" << cTimeBuffer << "]: " << InsData << "\r\n";

		rLogFile->close();

		return true;
	}
	else
		cerr << "[LogException] " << "Failed to write to file\r\n";

	return false;

}

bool Log::Write(const string& InsData, ELogSeverity IneLogSeverity)
{
	//if pass custom checks and input data is not empty
	if (CheckFile() && !InsData.empty() && rLogFile != nullptr)
	{
		ERRORCODE iErrorCode = 0;
		tm* rTimeStruct;
		string sSeverity;

		TranslateSeverity(IneLogSeverity, sSeverity);

		rLogFile->open(sFilePath + sFileName, static_cast<ios_base::openmode>(iBitFlagMode));

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

		*rLogFile << "[" << sLogName << "] " << "[" << sSeverity << "] " << "[" << cTimeBuffer << "]: " << InsData << "\r\n";

		rLogFile->close();

		return true;
	}
	else
		cerr << "[LogException] " << "Failed to write to file\r\n";

	return false;
}

bool Log::WriteAndDisplay(const string& InsData)
{
	//if pass custom checks and input data is not empty
	if (CheckFile() && !InsData.empty() && rLogFile != nullptr)
	{
		ERRORCODE iErrorCode = 0;
		tm* rTimeStruct;
		string sSeverity;

		TranslateSeverity(ELogSeverity::ELS_Info, sSeverity);

		rLogFile->open(sFilePath + sFileName, static_cast<ios_base::openmode>(iBitFlagMode));
		
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


		*rLogFile << "[" << sLogName << "] " << "[" << sSeverity << "] " << "[" << cTimeBuffer << "]: " << InsData << "\r\n";
		cerr << "[" << sLogName << "] " << "[" << sSeverity << "] " << "[" << cTimeBuffer << "]: " << InsData << "\r\n";

		rLogFile->close();

		return true;
	}
	else
		cerr << "[LogException] " << "Failed to write to file\r\n";

	return false;
}

bool Log::WriteAndDisplay(const string& InsData, ELogSeverity IneLogSeverity)
{
	//if pass custom checks and input data is not empty
	if (CheckFile() && !InsData.empty() && rLogFile != nullptr)
	{
		ERRORCODE iErrorCode = 0;
		tm* rTimeStruct;
		string sSeverity;

		TranslateSeverity(IneLogSeverity, sSeverity);

		rLogFile->open(sFilePath + sFileName, static_cast<ios_base::openmode>(iBitFlagMode));

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

		*rLogFile << "[" << sLogName << "] " << "[" << sSeverity << "] " << "[" << cTimeBuffer << "]: " << InsData << "\r\n";
		cerr << "[" << sLogName << "] " << "[" << sSeverity << "] " << "[" << cTimeBuffer << "]: " << InsData << "\r\n";

		rLogFile->close();

		return true;
	}
	else
		cerr << "[LogException] " << "Failed to write to file\r\n";

	return false;
}

string Log::Read()
{
	string sReadData;
	string Line;

	if (CheckFile() && rLogFile != nullptr)
	{
		rLogFile->open(sFilePath + sFileName, static_cast<ios_base::openmode>(iBitFlagMode));

		while (getline(*rLogFile, Line))
			sReadData.append("\r\n" + Line);

		rLogFile->close();
	}
	else
		cerr << "[LogException] " << "Failed to read file\r\n";

	return sReadData;
}

void Log::Display()
{
	string Line;

	if (CheckFile() && rLogFile != nullptr)
	{
		rLogFile->open(sFilePath + sFileName, static_cast<ios_base::openmode>(iBitFlagMode));

		while (getline(*rLogFile, Line))
			cout << Line << "\r\n";

		rLogFile->close();
	}
	else
		cerr << "[LogException] " << "Failed to read file\r\n";
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
		if (exists(sFilePath + sFileName, rErrorCode) && rLogFile != nullptr)
		{
			switch (rLogFile->rdstate())
			{
			case ios_base::goodbit:
			case ios_base::eofbit:
				return true;
			case ios_base::failbit:
				cerr << "failbit detected\r\n";
				break;
			case ios_base::badbit:
				cerr << "badbit detected\r\n";
				break;
			case ios_base::failbit | ios_base::badbit:
				cerr << "failbit and badbit detected\r\n";
				break;
			default:
				cout << "No state detected\r\n";
			}
		}
		else
			ShowErrorCode("File not found - Error Category");
	}
	else
		cerr << "[LogException] " << "Not enough space on current drive \r\n";

	return false;
}

void Log::ShowErrorCode(const string& InsCustomErrorMessage)
{
	cerr << "[LogException] " << InsCustomErrorMessage << ": Error Category" << rErrorCode.category().name() << ", Code : " << rErrorCode.value() << ", Error : " << rErrorCode.message() << "\r\n";
	rErrorCode.clear();
}

void Log::Initialization()
{
	rLogFile->exceptions(ios_base::failbit | ios_base::badbit);

	if (rLogFile != nullptr)
	{
		//If folder does not exists, create it
		if (!exists(sFilePath))
		{
			if (!create_directory(sFilePath, rErrorCode))
				ShowErrorCode("Failed to create directory");
		}

		//if the file does not exists, create it
		if (!exists(sFilePath + sFileName))
		{
			rLogFile->open(sFilePath + sFileName, static_cast<ios_base::openmode>(iBitFlagMode));
			rLogFile->close();
			rLogFile->clear();
		}

		//custom check file to see if previous steps are ok
		if (!CheckFile())
			cerr << "[LogException] " << "Failed to create file\r\n";

		rTime = time(0);
	}
	else
		cerr << "[LogException] " << "File object handler failed to init \r\n";
}