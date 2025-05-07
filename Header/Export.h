#pragma once

#include <iomanip>

#include "Model.h"
#include "FileHandler.h"

using std::setprecision, std::fixed, std::endl;
using KronosPrim::uint32;

/** @enum EExportType
* 	@brief Object type of export*/
enum class EExportType : uint32
{
    EET_OBJ = 0,
    EET_FBX = 1,
    EET_DXF = 2,
    EET_DAE = 3
};

/** @class Export
* 	@brief Export singleton class for object export*/
class Export
{
public:

    Export(Export const&) = delete;
    Export(Export&&) = delete;

    Export& operator=(Export const&) = delete;
    Export& operator=(Export&&) = delete;

    /** @param IncPath
    *   @param InrModel
    *   @param IneExportType
    *   @brief Export geometry mesh to file*/
    static void ExportModel(char const* IncPath, Model& InrModel, EExportType const IneExportType);

    /** @param InsPath
    *   @param InrModel
    *   @param IneExportType
    *   @brief Export geometry mesh to file*/
    static inline void ExportModel(string const& InsPath, Model& InrModel, EExportType const IneExportType);

    static Export* GetInstance(); /*!< @return Export* @brief Get Singleton as a instance*/

protected:

    static void ExportAsObj(Model& InrModel); /*!< @param InrModel @brief Export object by type .obj @todo complete the obj export*/
    static void ExportAsFBX(Model& InrModel); /*!< @param InrModel @brief Export object by type .FBX @todo Create export logic for fbx*/
    static void ExportAsDXF(Model& InrModel); /*!< @param InrModel @brief Export object by type .DXF @todo Create export logic for DXF*/
    static void ExportAsDAE(Model& InrModel); /*!< @param InrModel @brief Export object by type .DAE @todo Create export logic for DAE*/

private:
    Export();

    static Export* rExport;

    static FileHandler rFile;
};


inline void Export::ExportModel(string const& InsPath, Model& InrModel, EExportType const IneExportType) { ExportModel(InsPath.c_str(), InrModel, IneExportType); }