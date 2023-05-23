#pragma once

#include "Mesh.h"

class Model
{
public:
	Model();
	Model(const Model& InrModel);
	Model(Model&& InrModel);

	Model operator=(const Model& InrModel);
	Model& operator=(Model&& InrModel);

	~Model();

	void Destroy();

	void Draw(Shader& InrShader);

	void AddMesh(const Mesh& InrMesh);

	Mesh& GetMesh(uint32 IniID);
	Mesh& GetMesh(const string InsName);

	Texture& GetTexture(uint32 IniID);
	Texture& GetTexture(const string InsName);

	vector<Mesh> GetMeshList();
	vector<Texture*>& GetTextureList();

protected:
	Log* rLog = new Log("LogModel");

private:
	vector<Mesh> rMeshes;

	vector<Texture*>* rTextures = new vector<Texture*>();
};
