#pragma once
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Mesh.h"

using Assimp::Importer;

using std::string;

//TODO:Create necessary methods for the importer to work!
class Import
{
public:

    Import(char* IncPath);
    Import(const char* IncPath);

protected:

    Log* rLog = new Log("LogImport");

private:
    string sDirectory;

    const aiScene* rScene;

    vector<Mesh> rMeshes;

    vector<Texture*>* rTextures;

	void LoadModel(string InsPath);
	void ProcessNode(aiNode* InrNode, const aiScene* InrScene);
	Mesh ProcessMesh(aiMesh* InrMesh, const aiScene* InrScene);
	vector<Texture> LoadMaterialTextures(aiMaterial* InrMat, aiTextureType InrType);

};