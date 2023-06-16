#pragma once

#include <vector>
#include "Mesh.h"

using std::vector;

class Model
{
public:
	Model();
	Model(vector<Mesh*>& InrMeshes);
	Model(Model const& InrModel);
	Model(Model&& InrModel);
	

	Model operator=(Model const& InrModel);
	Model& operator=(Model&& InrModel);

	~Model();

	void Destroy();

	void Draw(Shader& InrShader);

	void Merge(Model const& InrModel);

	inline void SetMeshList(vector<Mesh*> const& InrMeshes);

	inline void AddMesh(Mesh* InrMesh);

	void RemoveMesh(uint64 IniHash);

	Mesh* GetMesh(uint64 IniHash);

	inline vector<Mesh*> GetMeshList();

protected:
	Log* rLog;

private:
	vector<Mesh*> rMeshes;
};

//Add Mesh in the Model
inline void Model::AddMesh(Mesh* InrMesh) { rMeshes.push_back(InrMesh); }

inline void Model::SetMeshList(vector<Mesh*> const& InrMeshes) { rMeshes = InrMeshes; }

//Get Mesh list from the Model
inline vector<Mesh*> Model::GetMeshList() { return rMeshes; }