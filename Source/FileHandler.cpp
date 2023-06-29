#include "FileHandler.h"

FileHandler::FileHandler() { Init(); }

FileHandler::FileHandler(char const* IncPath, char const* IncFileName, ios_base::openmode IniFlagType) :
sFilePath(IncPath),
sFileName(IncFileName),
iBitFlagMode(IniFlagType) { Init(); }

FileHandler::FileHandler(string const& InsPath, string const& InsFileName, ios_base::openmode IniFlagType) :
sFilePath(InsPath),
sFileName(InsFileName),
iBitFlagMode(IniFlagType) { Init(); }

FileHandler::FileHandler(FileHandler const& InrFileHandler)
{
	sFilePath = InrFileHandler.sFileName;
	sFilePath = InrFileHandler.sFilePath;
	iBitFlagMode = InrFileHandler.iBitFlagMode;
}

FileHandler::FileHandler(FileHandler && InrFileHandler)
{
	if(this != &InrFileHandler)
	{
		sFilePath = InrFileHandler.sFileName;
		sFilePath = InrFileHandler.sFilePath;
		iBitFlagMode = InrFileHandler.iBitFlagMode;
	}
}

FileHandler FileHandler::operator=(FileHandler const& InrFileHandler)
{
	sFilePath = InrFileHandler.sFileName;
	sFilePath = InrFileHandler.sFilePath;
	iBitFlagMode = InrFileHandler.iBitFlagMode;

	return InrFileHandler;
}

FileHandler FileHandler::operator=(FileHandler && InrFileHandler)
{
	if(this != &InrFileHandler)
	{
		sFilePath = InrFileHandler.sFileName;
		sFilePath = InrFileHandler.sFilePath;
		iBitFlagMode = InrFileHandler.iBitFlagMode;
	}

	return InrFileHandler;
}

void FileHandler::Init()
{
	rFile.fixed;
	rFile.precision(2);

	if (!exists(sFilePath))
	{
		if (!create_directory(sFilePath, rErrorCode))
			ShowErrorCode("Failed to create directory");
	}

	//if the file does not exists, create it
	if (!exists(sFilePath + sFileName))
	{
		rFile.open(sFilePath + sFileName, static_cast<ios_base::openmode>(iBitFlagMode));

		//custom check file to see if previous steps are ok
		if (!Check())
			cerr << "[FileHandlerException] Failed to create file\r\n";

		rFile.close();

		if (!CheckState())
			cerr << "[FileHandlerException] Failed to close file\r\n";
		
		rFile.clear();
	}

	
}

bool FileHandler::Check()
{
	space_info DriveSpaceInfo = space(sFilePath, rErrorCode);

	if (rErrorCode.value() != 0)
		ShowErrorCode("Failed to request drive memory info");

	//check drive if it has enough space (min 4mb)
	if (DriveSpaceInfo.available > iMinFileSizeBytes)
	{
		if (exists(sFilePath + sFileName, rErrorCode) && CheckState())
			return true;
		else
			ShowErrorCode("File not found - Error Category");
	}
	else
		cerr << "[FileHandlerException] Not enough space on current drive \r\n";

	return false;
}

bool FileHandler::CheckState()
{
	switch (rFile.rdstate())
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
	default:
		cout << "No state detected\r\n";
	}

	return false;
}

string FileHandler::Read()
{
	string sReadData = "";
	string Line = "";

	rFile.open(sFilePath + sFileName, static_cast<ios_base::openmode>(iBitFlagMode));

	if (Check())
	{
		while (getline(rFile, Line))
			sReadData.append("\r\n" + Line);
	}
	else
		cerr << "[FileHandlerException] Failed to open file\r\n";

	rFile.close();

	if(!CheckState())
		cerr << "[FileHnadlerException] failed to close file\r\n";

	return sReadData;
}

void FileHandler::Write(string const& InsData)
{
	rFile.open(sFilePath + sFileName, static_cast<ios_base::openmode>(iBitFlagMode));

	if(Check())
		rFile << InsData;
	else
		cerr << "[FileHnadlerException] Failed to open file\r\n";

	rFile.close();

	if(!CheckState())
		cerr << "[FileHnadlerException] failed to close file\r\n";
}

void FileHandler::ShowErrorCode(string const& InsCustomErrorMessage)
{
	cerr << "[FileHandlerException] " << InsCustomErrorMessage << ": Error Category - " << rErrorCode.category().name() << ", Code: " << rErrorCode.value() << ", Error: " << rErrorCode.message() << "\r\n";
	rErrorCode.clear();
}