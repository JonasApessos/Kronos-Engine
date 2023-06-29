#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <filesystem>
#include <cstring>
#include <errno.h>
#include "Primitives.h"

using std::fstream, std::ios_base;
using KronosPrim::uint32;

using KronosPrim::int32, KronosPrim::uint32;
using std::cout, std::cerr;
using std::ios_base, std::ostream, std::fstream, std::string, std::getline, std::error_code, std::strerror;
using std::filesystem::create_directory, std::filesystem::exists, std::filesystem::space, std::filesystem::space_info;


class FileHandler
{
public:
    int32 iBitFlagMode = ios_base::in | ios_base::out | ios_base::app;

    FileHandler();
    FileHandler(char const* IncPath, char const* IncFileName, ios_base::openmode IniFlagType);
    FileHandler(string const& InsPath, string const& InsFileName, ios_base::openmode IniFlagType);
    FileHandler(FileHandler const& InrFileHandler);
    FileHandler(FileHandler && InrFileHandler);

    FileHandler operator=(FileHandler const& InrFileHandler);
    FileHandler operator=(FileHandler && InrFileHandler);

    void Init();

    //Set
    inline void SetBitFlagMode(int32 IniBitFlagMode);
	inline void SetFileName(string const& InsFileName);
	inline void SetFilePath(string const& InsFileName);
    inline void SetPrecision(uint32 IniPrecision);

    //Get
	inline int32 GetBitFlagMode() const;
	inline string GetFileName() const;
	inline string GetFilePath() const;

    //Read and return buffer string with log message
    string Read();

    void Write(string const& InsData);

protected:
    string sFileName;
	string sFilePath;

    uint32 iMinFileSizeBytes = 4194304;

    void ShowErrorCode(string const& InsCustomErrorMessage);

    bool Check();
    bool CheckState();

private:
    fstream rFile;

	error_code rErrorCode;
};

inline void FileHandler::SetBitFlagMode(int32 IniBitFlagMode) { iBitFlagMode = IniBitFlagMode; }
inline void FileHandler::SetFileName(string const& InsFileName) { sFileName = InsFileName; }
inline void FileHandler::SetFilePath(string const& InsFilePath) { sFilePath = InsFilePath; }
inline void FileHandler::SetPrecision(uint32 IniPrecision) { rFile.precision(IniPrecision); }

inline int32 FileHandler::GetBitFlagMode() const { return iBitFlagMode; }
inline string FileHandler::GetFileName() const { return sFileName; }
inline string FileHandler::GetFilePath() const { return sFilePath; }