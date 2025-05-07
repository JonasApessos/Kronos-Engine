#include "FileHandler.h"

FileHandler::FileHandler() {}

FileHandler::FileHandler(char const* IncPath, char const* IncFileName, ios_base::openmode IniFlagType) :
iBitFlagMode(IniFlagType),
sFileName(IncFileName),
sFilePath(IncPath) { Init(); }

FileHandler::FileHandler(string const& InsPath, string const& InsFileName, ios_base::openmode IniFlagType) :
iBitFlagMode(IniFlagType),
sFileName(InsFileName),
sFilePath(InsPath) { Init(); }

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
	rFile.precision(2);

	if(!CreateDirectory())
		cerr << "Failed to create directory";

	if(!CreateFile())
		cerr << "Failed to create file";
}

bool FileHandler::CreateFile()
{
	//if the file does not exists, create it
	if (!exists(sFilePath + sFileName))
	{
		rFile.open(sFilePath + sFileName, ios_base::out);

		//custom check file to see if previous steps are ok
		if (!Check())
		{
			cerr << "[FileHandlerException]: Failed to open file\r\n";

			return false;
		}

		rFile.close();

		if (!CheckState())
			cerr << "[FileHandlerException]: Failed to close file\r\n";
		
		rFile.clear();
	}

	return true;
}

bool FileHandler::CreateDirectory()
{
	if (!exists(sFilePath) && !create_directory(sFilePath, rErrorCode))
	{
		ShowErrorCode("Failed to create directory");
		return false;
	}

	return true;
}

void FileHandler::SetFullPath(string const& InsPath)
{
	if(!InsPath.empty())
	{
		SetFileName(InsPath.substr(InsPath.find_last_of('/') + 1));
		SetFilePath(InsPath.substr(0, (InsPath.find_last_of('/') + 1)));
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
		cerr << "[FileHandlerException]: Not enough space on current drive \r\n";

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
		cerr << "[FileHandlerException]: failbit detected\r\n";
		break;
	case ios_base::badbit:
		cerr << "[FileHandlerException]: badbit detected\r\n";
		break;
	default:
		cout << "[FileHandlerException]: No state detected\r\n";
	}

	return false;
}

string FileHandler::Read()
{
	stringstream rStreamData;

	rFile.open(sFilePath + sFileName, ios_base::in);

	if (Check())
		rStreamData << rFile.rdbuf();
	else
		cerr << "[FileHandlerException]: Failed to open file\r\n";

	rFile.close();

	if(!CheckState())
		cerr << "[FileHnadlerException]: failed to close file\r\n";

	return rStreamData.str();
}

string FileHandler::ReadCustom()
{
	stringstream rStreamData;

	rFile.open(sFilePath + sFileName, static_cast<ios_base::openmode>(iBitFlagMode));

	if (Check())
		rStreamData << rFile.rdbuf();
	else
		cerr << "[FileHandlerException]: Failed to open file\r\n";

	rFile.close();

	if(!CheckState())
		cerr << "[FileHnadlerException]: failed to close file\r\n";

	return rStreamData.str();
}

bool FileHandler::Write(string const& InsData)
{
	rFile.open(sFilePath + sFileName, ios_base::out | ios_base::app);

	if(Check())
		rFile << InsData;
	else
	{
		cerr << "[FileHnadlerException]: Failed to open file\r\n";

		return false;
	}

	rFile.close();

	if(!CheckState())
		cerr << "[FileHnadlerException]: failed to close file\r\n";

	return true;
}

bool FileHandler::WriteCustom(string const& InsData)
{
	rFile.open(sFilePath + sFileName, static_cast<ios_base::openmode>(iBitFlagMode));

	if(Check())
		rFile << InsData;
	else
	{
		cerr << "[FileHnadlerException]: Failed to open file\r\n";

		return false;
	}

	rFile.close();

	if(!CheckState())
		cerr << "[FileHnadlerException]: failed to close file\r\n";

	return true;
}

void FileHandler::ShowErrorCode(string const& InsCustomErrorMessage)
{
	cerr << "[FileHandlerException]:" << " Error Category - " << rErrorCode.category().name() << ", Code: " << rErrorCode.value() << ", Error: " << rErrorCode.message() << " - " << InsCustomErrorMessage << "\r\n";
	rErrorCode.clear();
}