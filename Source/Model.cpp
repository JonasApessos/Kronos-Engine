#include "Model.h"

Model::Model() : 
rLog(){}

Model::Model(vector<Mesh> const& InrMeshes) : 
rMeshes(InrMeshes) {}

Model::Model(Model const& InrModel) : 
rLog(InrModel.rLog),
rMeshes(InrModel.rMeshes) {}

Model::Model(Model&& InrModel)
{
    if(this != &InrModel)
    {
        rLog = InrModel.rLog;
        rMeshes = InrModel.rMeshes;

        InrModel.rMeshes.clear();
    }
}

Model::~Model() { Destroy(); }

void Model::Destroy() {}

Model Model::operator=(Model const& InrModel)
{
    rLog = InrModel.rLog;
    rMeshes = InrModel.rMeshes;

    return InrModel;
}

Model& Model::operator=(Model&& InrModel)
{
    if(this != &InrModel)
    {
        rLog = InrModel.rLog;
        rMeshes = InrModel.rMeshes;
    }

    return InrModel;
}

void Model::Draw(Shader& InrShader)
{
    vector<Mesh>::iterator rIt = rMeshes.begin();

    while(rIt != rMeshes.end())
    {
        static_cast<Mesh>(*rIt).Draw(InrShader);

        ++rIt;
    }
}

void Model::RemoveMesh(uint64 IniHash)
{
	vector<Mesh>::iterator rIt = rMeshes.begin();

	while(rIt != rMeshes.end())
	{
		if(static_cast<Mesh>(*rIt).GetHash() == IniHash)
		{
			rMeshes.erase(rIt);

			break;
		}

		++rIt;
	}
}

//Get Mesh from the Model by id
bool Model::GetMesh(uint64 IniHash, Mesh& InrMesh)
{
	vector<Mesh>::iterator rIt = rMeshes.begin();

	while(rIt != rMeshes.end())
	{
		if(static_cast<Mesh>(*rIt).GetHash() == IniHash)		
        {
			InrMesh = *rIt;

            return true;
        }

		++rIt;
	}

    return false;
}
