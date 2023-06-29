#pragma once

#include <iomanip>
#include "Model.h"
#include "FileHandler.h"

using std::setprecision, std::fixed, std::endl;
using KronosPrim::uint32;

enum EExportType : uint32
{
    EET_OBJ = 0,
    EET_FBX = 1,
    EET_DXF = 2,
    EET_DAE = 3
};

class Export
{
public:

    Export(Export const&) = delete;
    Export(Export&&) = delete;

    Export& operator=(Export const&) = delete;
    Export& operator=(Export&&) = delete;

    static void ExportModel(char const* IncPath, Model* InrModel, EExportType const IneExportType);
    static inline void ExportModel(string const& IncPath, Model* InrModel, EExportType const IneExportType);

    static Export* GetInstance();

protected:

    static void ExportAsObj(Model* InrModel);
    static void ExportAsFBX(Model* InrModel);
    static void ExportAsDXF(Model* InrModel);
    static void ExportAsDAE(Model* InrModel);

private:
    Export();

    static Export* rExport;

    static FileHandler rFile;
};


inline void Export::ExportModel(string const& InsPath, Model* InrModel, EExportType const IneExportType) { ExportModel(InsPath.c_str(), InrModel, IneExportType); }