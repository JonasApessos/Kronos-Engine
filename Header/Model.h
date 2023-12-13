#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Object.h"
#include "Mesh.h"

using std::vector;
using glm::vec3, glm::mat4;

/** @class Model
*   @brief class than manages meshes nodes*/
class Model : public Object3D
{
public:
	Model();
	Model(vector<Mesh> const& InrMeshes);
	Model(Model const& InrModel);
	Model(Model&& InrModel);
	

	Model operator=(Model const& InrModel);
	Model& operator=(Model&& InrModel);

	~Model();

	inline void SetMeshList(vector<Mesh> const& InrMeshes);

	bool GetMesh(uint64 IniHash, Mesh& InrMesh);
	inline vector<Mesh> GetMeshList();
	inline mat4 GetTransformMatrix() const;

	void Destroy();

	inline void AddMesh(Mesh const& InrMesh);

	void RemoveMesh(uint64 IniHash);

	inline void Transform(vec3 const& InrTranslate, float fDegrees, vec3 const& InrRotate, vec3 const& InrScale);

	inline void Translate(vec3 const& InrTranslate);
	inline void Rotate(float fDegrees, vec3 const& InrRotate);
	inline void Scale(vec3 const& InrScale);

	void Draw(Shader& InrShader);

	void Merge(Model const& InrModel);

protected:
	Log rLog = Log("LogModel");

private:
	vector<Mesh> rMeshes;
	mat4 rTransform = mat4(1.0f);
};

inline void Model::SetMeshList(vector<Mesh> const& InrMeshes) { rMeshes = InrMeshes; }

//Get Mesh list from the Model
inline vector<Mesh> Model::GetMeshList() { return rMeshes; }

inline mat4 Model::GetTransformMatrix() const { return rTransform; }

inline void Model::Transform(vec3 const& InrTranslate, float fDegrees, vec3 const& InrRotate, vec3 const& InrScale)
{
	Scale(InrScale);
	Rotate(fDegrees, InrRotate);
	Translate(InrTranslate);
}

inline void Model::Translate(vec3 const& InrTranslate) { rTransform = glm::translate(rTransform, InrTranslate); }
inline void Model::Rotate(float fDegrees, vec3 const& InrRotate) { rTransform = glm::rotate(rTransform, glm::radians(fDegrees), InrRotate); }
inline void Model::Scale(vec3 const& InrScale) { rTransform = glm::scale(rTransform, InrScale); }

//Add Mesh in the Model
inline void Model::AddMesh(Mesh const& InrMesh) { rMeshes.push_back(InrMesh); }