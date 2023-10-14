#include "Mesh.h"

uint64 MeshBase::iNumMeshes = 0;

MeshBase::MeshBase(vector<SVector>& InrVertices, vector<uint32>& InrIndices, vector<Texture>& InrTextures) :
rVertices(InrVertices),
rIndices(InrIndices),
rTextures(InrTextures) { iHash = static_cast<uint64>(hash<std::string>{}(to_string(iID = ++iNumMeshes))); }

MeshBase::MeshBase(MeshBase const& InrMeshBase) : 
iID(InrMeshBase.iID),
iHash(InrMeshBase.iHash),
VAO(InrMeshBase.VAO),
VBO(InrMeshBase.VBO),
EBO(InrMeshBase.EBO),
rVertices(InrMeshBase.rVertices),
rIndices(InrMeshBase.rIndices),
rTextures(InrMeshBase.rTextures),
eDrawMode(InrMeshBase.eDrawMode) {}

MeshBase::MeshBase(MeshBase&& InrMeshBase)
{
	if(this != &InrMeshBase)
	{
		VAO = InrMeshBase.VAO;
		VBO = InrMeshBase.VBO;
		EBO = InrMeshBase.EBO;
		rVertices = InrMeshBase.rVertices;
		rIndices = InrMeshBase.rIndices;
		rTextures = InrMeshBase.rTextures;
		eDrawMode = InrMeshBase.eDrawMode;
		iID = InrMeshBase.iID;
		iHash = InrMeshBase.iHash; 
	}
}

MeshBase::~MeshBase() {}

Mesh::Mesh(vector<SVector>& InrVertices, vector<uint32>& InrIndices, vector<Texture>& InrTextures) : 
MeshBase(InrVertices, InrIndices, InrTextures) { SetupMesh(); }

Mesh::Mesh(const Mesh& InrMesh) : 
MeshBase(InrMesh) { SetupMesh(); }

Mesh::Mesh(Mesh&& InrMesh) : 
MeshBase(InrMesh) {}

Mesh Mesh::operator=(Mesh const& InrMesh)
{
	VAO = InrMesh.VAO;
	VBO = InrMesh.VBO;
	EBO = InrMesh.EBO;
	rVertices = InrMesh.rVertices;
	rIndices = InrMesh.rIndices;
	rTextures = InrMesh.rTextures;
	eDrawMode = InrMesh.eDrawMode;
	iID = InrMesh.iID;
	iHash = InrMesh.iHash; 

	return InrMesh;
}

Mesh Mesh::operator=(Mesh&& InrMesh)
{
	if(this != &InrMesh)
	{
		VAO = InrMesh.VAO;
		VBO = InrMesh.VBO;
		EBO = InrMesh.EBO;
		rVertices = InrMesh.rVertices;
		rIndices = InrMesh.rIndices;
		rTextures = InrMesh.rTextures;
		eDrawMode = InrMesh.eDrawMode;
		iID = InrMesh.iID;
		iHash = InrMesh.iHash;
	}

	return *this;
}

Mesh::~Mesh() { Destroy(); }

void Mesh::Destroy() {}

void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(static_cast<GLenum>(EGLBufferTarget::EGLBDT_ArrayBuffer), VBO);

	glBufferData(static_cast<GLenum>(EGLBufferTarget::EGLBDT_ArrayBuffer), rVertices.size() * sizeof(SVector), &rVertices[0], static_cast<GLenum>(EGLBufferTUsage::EGLBDU_StaticDraw));

	glBindBuffer(static_cast<GLenum>(EGLBufferTarget::EGLBDT_ElementArrayBuffer), EBO);
	glBufferData(static_cast<GLenum>(EGLBufferTarget::EGLBDT_ElementArrayBuffer), rIndices.size() * sizeof(GL_UNSIGNED_INT), &rIndices[0], static_cast<GLenum>(EGLBufferTUsage::EGLBDU_StaticDraw));

	//Vertex Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SVector), (void*) offsetof(SVector, Position));

	//Vertex Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SVector), (void*) offsetof(SVector, Normal));

	//Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SVector), (void*) offsetof(SVector, TexCoords));

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
			glActiveTexture(static_cast<GLenum>(EGLTextureSlot::EGLTS_Slot0) + DrawLoop);

			if (rTextures[DrawLoop].GetTextureType() == ETextureType::ETT_Albedo)
				Number = to_string(DiffuseNr++);
			else if (rTextures[DrawLoop].GetTextureType() == ETextureType::ETT_Specular)
				Number = to_string(SpecularNr++);

			InrShader.SetInt(
				("Material." + to_string(static_cast<int32>(rTextures[DrawLoop].GetTextureType())) + "." + Number).c_str(),
					static_cast<int32>(DrawLoop));
					
			glBindTexture(static_cast<GLenum>(rTextures[DrawLoop].GetTextureDataType()), rTextures[DrawLoop].GetId());

			Number = "";

			++DrawLoop;
		}

		glActiveTexture(static_cast<GLenum>(EGLTextureSlot::EGLTS_Slot0));
	}
	


	glBindVertexArray(VAO);
	glDrawElements(static_cast<GLenum>(eDrawMode), static_cast<GLsizei>(rIndices.size()), GL_UNSIGNED_INT, (void*)NULL);
	glBindVertexArray(0);
}