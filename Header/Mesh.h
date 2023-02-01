#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"

class Vertex;

using std::string;
using std::vector;

class MeshBase
{
public:
	vector<Vertex> rVertices;
	vector<unsigned int> rIndices;
	vector<Texture> rTextures;

	MeshBase();

	virtual ~MeshBase() = 0;

	virtual void Draw(Shader& InrShader) = 0;

protected:
	virtual void SetupMesh() = 0;

private:
	unsigned int MeshID;
	unsigned int VAO, VBO, EBO;

	
};

class Mesh
{
public:
	vector<Vertex> rVertices;
	vector<unsigned int> rIndices;
	vector<Texture> rTextures;

	Mesh(vector<Vertex> InrVertices, vector<unsigned int> InrIndices, vector<Texture> InrTextures);
	void Draw(Shader& InrShader);

private:
	unsigned int VAO, VBO, EBO;

	void SetupMesh();
};

