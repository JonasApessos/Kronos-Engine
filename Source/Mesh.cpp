#include "Mesh.h"


Mesh::Mesh(vector<Vertex> InrVertices, vector<uint32> InrIndices, vector<Texture*>* InrTextures)
{
	rLog = Log("LogMesh");

	rVertices = InrVertices;
	rIndices = InrIndices;
	rTextures = InrTextures;

	SetupMesh();
}

void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, rVertices.size() * sizeof(Vertex), &rVertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, rIndices.size() * sizeof(GL_UNSIGNED_INT), &rIndices[0], GL_STATIC_DRAW);

	//Vertex Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::VertexData.Position));

	//Vertex Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::VertexData.Normal));

	//Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::VertexData.TexCoords));

	glBindVertexArray(0);
}

void Mesh::Draw(Shader& InrShader)
{
	uint32 DiffuseNr = 1;
	uint32 SpecularNr = 1;

	for (uint32 i = 0; i < rTextures->size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		string Number;
		
		if (rTextures->at(i)->GetTextureType() == ETextureType::ETT_Albedo)
			Number = to_string(DiffuseNr++);
		else if (rTextures->at(i)->GetTextureType() == ETextureType::ETT_Specular)
			Number = to_string(SpecularNr++);

		InrShader.SetInt(("Material." + to_string((int32)rTextures->at(i)->GetTextureType()) + "." + Number).c_str(), i);
		glBindTexture(static_cast<GLenum>(rTextures->at(i)->GetTextureDataType()), rTextures->at(i)->GetId());
	}

	glActiveTexture(GL_TEXTURE0);


	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(rIndices.size()), GL_UNSIGNED_INT, (void*)NULL);
	glBindVertexArray(0);
}