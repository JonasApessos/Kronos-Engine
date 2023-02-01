#include "Mesh.h"


Mesh::Mesh(vector<Vertex> InrVertices, vector<unsigned int> InrIndices, vector<Texture> InrTextures)
{
	rVertices = InrVertices;
	rIndices = InrIndices;
	rTextures = InrTextures;

	SetupMesh();
}

void Mesh::SetupMesh()
{
	cout << sizeof(Vertex) << "\n Pos Size: " << sizeof(Vertex::VertexData.Position) << "\n Norm Size: " << sizeof(Vertex::VertexData.Normal) << "\n Tex Size: " << sizeof(Vertex::VertexData.TexCoords) << "\n";
	cout << offsetof(Vertex, Vertex::VertexData.Position) << "\n";
	cout << offsetof(Vertex, Vertex::VertexData.Normal) << "\n";
	cout << offsetof(Vertex, Vertex::VertexData.TexCoords) << "\n";

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
	unsigned int DiffuseNr = 1;
	unsigned int SpecularNr = 1;

	for (unsigned int i = 0; i < rTextures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		string Number;
		
		if (rTextures[i].GetTextureType() == ETextureType::ETT_Albedo)
			Number = to_string(DiffuseNr++);
		else if (rTextures[i].GetTextureType() == ETextureType::ETT_Specular)
			Number = to_string(SpecularNr++);

		InrShader.SetInt(("Material." + to_string((GLint)rTextures[i].GetTextureType()) + "." + Number).c_str(), i);
		glBindTexture((GLenum)rTextures[i].GetTextureDataType(), rTextures[i].GetId());
	}

	glActiveTexture(GL_TEXTURE0);


	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, rIndices.size(), GL_UNSIGNED_INT, (void*)NULL);
	glBindVertexArray(0);
}