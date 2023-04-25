#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"

class Vertex;

using KronosPrim::uint32;
using std::string, std::vector, std::to_string;

class MeshBase
{
public:
	vector<Vertex> rVertices;
	vector<uint32> rIndices;
	vector<Texture> rTextures;

	MeshBase();

	virtual ~MeshBase() = 0;

	virtual void Draw(Shader& InrShader) = 0;

protected:
	virtual void SetupMesh() = 0;

private:
	uint32 MeshID;
	uint32 VAO, VBO, EBO;

	
};

class Mesh
{
public:
	vector<Vertex> rVertices;
	vector<uint32> rIndices;
	vector<Texture*>* rTextures;

	Mesh(vector<Vertex>& InrVertices, vector<uint32> InrIndices, vector<Texture*>* InrTextures);
	void Draw(Shader& InrShader);

protected:
	Log rLog;

private:
	uint32 VAO, VBO, EBO;

	void SetupMesh();
};

