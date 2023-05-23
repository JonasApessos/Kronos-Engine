#pragma once
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

using Assimp::Importer;

//TODO:Create necessary methods for the importer to work!
class Import
{
public:

    Import(char* IncPath);
    Import(const char* IncPath);

protected:

private:
    string sDirectory;

    const aiScene* rScene;

	void LoadModel(string InsPath);
	void ProcessNode(aiNode* InrNode, const aiScene* InrScene);
	Mesh ProcessMesh(aiMesh* InrMesh, const aiScene* InrScene);
	vector<Texture> LoadMaterialTextures(aiMaterial* InrMat, aiTextureType InrType);

};