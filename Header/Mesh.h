#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <unordered_set>
#include "Vector.h"
#include "Texture.h"
#include "Shader.h"

using KronosPrim::uint32, KronosPrim::uint64;
using std::string, std::vector, std::to_string, std::hash;

class MeshBase
{
public:
	MeshBase(vector<SVector>& InrVertices, vector<uint32>& InrIndices, vector<Texture*>& InrTextures);
	MeshBase(MeshBase const& InrBaseMesh);
	MeshBase(MeshBase&& InrMaseMesh);
	
	virtual ~MeshBase() = 0;

	virtual void Draw(Shader& InrShader) = 0;

	constexpr inline uint32 GetVAO() const;
	constexpr inline uint32 GetVBO() const;
	constexpr inline uint32 GetEBO() const;

	constexpr inline uint64 GetHash() const;

	inline vector<SVector> GetVertices() const;
	inline vector<uint32> GetIndices() const;
	inline vector<Texture*> GetTextures() const;

protected:
	uint64 iID;
	uint64 iHash;

	uint32 VAO, VBO, EBO;

	vector<SVector> rVertices;
	vector<uint32> rIndices;
	vector<Texture*> rTextures;

	virtual void SetupMesh() = 0;

private:
	static uint64 iNumMeshes;
};

constexpr inline uint32 MeshBase::GetVAO() const { return VAO; }
constexpr inline uint32 MeshBase::GetVBO() const { return VBO; }
constexpr inline uint32 MeshBase::GetEBO() const { return EBO; }

constexpr inline uint64 MeshBase::GetHash() const { return iHash; }

inline vector<SVector> MeshBase::GetVertices() const { return rVertices; }
inline vector<uint32> MeshBase::GetIndices() const { return rIndices; }
inline vector<Texture*> MeshBase::GetTextures() const { return rTextures; }


class Mesh : public MeshBase 
{
public:
	Mesh(vector<SVector>& InrVertices, vector<uint32>& InrIndices, vector<Texture*>& InrTextures);
	Mesh(Mesh const& InrMesh);
	Mesh(Mesh&& InrMesh);

	void Draw(Shader& InrShader);

	~Mesh();

	void Destroy();
protected:
	Log* rLog = new Log("LogMesh");

	virtual void SetupMesh() override;
private:
	
};
