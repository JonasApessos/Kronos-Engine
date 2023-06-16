#include "Mesh.h"

uint64 MeshBase::iNumMeshes = 0;

MeshBase::MeshBase(vector<SVector>& InrVertices, vector<uint32>& InrIndices, vector<Texture*>& InrTextures) :
rVertices(InrVertices),
rIndices(InrIndices),
rTextures(InrTextures) { iHash = static_cast<uint64>(hash<std::string>{}(to_string(iID = ++iNumMeshes))); }

MeshBase::MeshBase(MeshBase const& InrMeshBase) : 
VAO(InrMeshBase.VAO),
VBO(InrMeshBase.VBO),
EBO(InrMeshBase.EBO),
rVertices(InrMeshBase.rVertices),
rIndices(InrMeshBase.rIndices),
rTextures(InrMeshBase.rTextures),
iID(InrMeshBase.iID),
iHash(InrMeshBase.iHash) {}

MeshBase::MeshBase(MeshBase&& InrMeshBase) :
VAO(InrMeshBase.VAO),
VBO(InrMeshBase.VBO),
EBO(InrMeshBase.EBO),
rVertices(InrMeshBase.rVertices),
rIndices(InrMeshBase.rIndices),
rTextures(InrMeshBase.rTextures),
iID(InrMeshBase.iID),
iHash(InrMeshBase.iHash) {}

MeshBase::~MeshBase() {}

Mesh::Mesh(vector<SVector>& InrVertices, vector<uint32>& InrIndices, vector<Texture*>& InrTextures) : 
MeshBase(InrVertices, InrIndices, InrTextures) { SetupMesh(); }

Mesh::Mesh(const Mesh& InrMesh) : 
MeshBase(InrMesh) { SetupMesh(); }

Mesh::Mesh(Mesh&& InrMesh) : 
MeshBase(InrMesh) {}

Mesh::~Mesh() { Destroy(); }

void Mesh::Destroy()
{
	if(rLog != nullptr)
		delete rLog;
}

void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, rVertices.size() * sizeof(SVector), &rVertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, rIndices.size() * sizeof(GL_UNSIGNED_INT), &rIndices[0], GL_STATIC_DRAW);

	//Vertex Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SVector), (void*)offsetof(SVector, SVector::Position));

	//Vertex Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SVector), (void*)offsetof(SVector, SVector::Normal));

	//Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SVector), (void*)offsetof(SVector, SVector::TexCoords));

	glBindVertexArray(0);
}

void Mesh::Draw(Shader& InrShader)
{
	uint32 DiffuseNr = 1;
	uint32 SpecularNr = 1;

	if (!rTextures.empty())
	{
		uint32 DrawLoop = 0;

		string Number = "";

		while(DrawLoop < rTextures.size())
		{
			glActiveTexture(GL_TEXTURE0 + DrawLoop);

			if(rTextures[DrawLoop] != nullptr)
			{
				if (rTextures[DrawLoop]->GetTextureType() == ETextureType::ETT_Albedo)
					Number = to_string(DiffuseNr++);
				else if (rTextures[DrawLoop]->GetTextureType() == ETextureType::ETT_Specular)
					Number = to_string(SpecularNr++);

				InrShader.SetInt(
					("Material." + to_string(static_cast<int32>(rTextures[DrawLoop]->GetTextureType())) + "." + Number).c_str(),
					 DrawLoop);
					 
				glBindTexture(static_cast<GLenum>(rTextures[DrawLoop]->GetTextureDataType()), rTextures[DrawLoop]->GetId());

				Number = "";
			}

			++DrawLoop;
		}

	}
	glActiveTexture(GL_TEXTURE0);


	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(rIndices.size()), GL_UNSIGNED_INT, (void*)NULL);
	glBindVertexArray(0);
}