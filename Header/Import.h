#pragma once


#include <vector>
#include <string>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Vector.h"
#include "Mesh.h"
#include "Texture.h"
#include "Model.h"

using std::string, std::vector;

using Assimp::Importer;

using KronosPrim::uint32;


/** @class Import
*   @brief Singleton importer class.
*    
*   The singleton class imports object from files.
*/
//Load Object
class Import
{
public:
    Import(Import const&) = delete;
    Import(Import&&) = delete;

    Import& operator=(Import const&) = delete;
    Import& operator=(Import&&) = delete;


    //Load Object
    static void LoadModel(char const* InsPath, Model& InrModel);
    static inline void LoadModel(string& InsPath, Model& InrModel);

    static Import* GetInstance();

protected:

    static Log rLog;

private:

    static Import* rImport;

    Import();
    ~Import();
	
    //Process scene nodes
	static void ProcessNode(string const& InsDirectory, aiNode* InrNode, aiScene const* InrScene, vector<Mesh>& InrMeshes);
    //Load mesh object
	static Mesh ProcessMesh(string const& InsDirectory, aiMesh* InrMesh, aiScene const* InrScene);
    //Load texture for material linking
	static vector<Texture> LoadMaterialTextures(string const& InsDirectory, aiMaterial* InrMat, aiTextureType InrType);

};

inline void Import::LoadModel(string& InsPath, Model& InrModel) { LoadModel(InsPath.c_str(), InrModel); }

