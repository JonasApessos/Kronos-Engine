#pragma once
#include "Mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

using Assimp::Importer;

class Model
{
public:
	Model(char* IncPath);
	Model(const char* IncPath);

	void Draw(Shader& InrShader);

protected:
	Log rLog;

private:
	vector<Mesh> rMeshes;
	string sDirectory;

	Importer rImporter;

	vector<Texture*>* rTextures;

	const aiScene* rScene;

	void LoadModel(string InsPath);
	void ProcessNode(aiNode* InrNode, const aiScene* InrScene);
	Mesh ProcessMesh(aiMesh* InrMesh, const aiScene* InrScene);
	vector<Texture> LoadMaterialTextures(aiMaterial* InrMat, aiTextureType InrType);
};
