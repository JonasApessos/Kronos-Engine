#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "Vector.h"
#include "Texture.h"
#include "Shader.h"

using KronosPrim::uint32;
using std::string, std::vector, std::to_string;

class MeshBase
{
public:
	vector<FVector> rVertices;
	vector<uint32> rIndices;
	vector<Texture*>* rTextures = nullptr;

	MeshBase(vector<FVector>& InrVertices, vector<uint32> InrIndices, vector<Texture*>* InrTextures);

	virtual ~MeshBase() = 0;

	virtual void Draw(Shader& InrShader) = 0;

protected:
	virtual void SetupMesh() = 0;

	uint32 MeshID;
	uint32 VAO, VBO, EBO;

private:
	

	
};

class Mesh  : MeshBase
{
public:
	Mesh(vector<FVector>& InrVertices, vector<uint32> InrIndices, vector<Texture*>* InrTextures);
	void Draw(Shader& InrShader);

protected:
	Log* rLog = new Log("LogMesh");

private:
	void SetupMesh();
};

