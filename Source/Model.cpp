#include "Model.h"

Model::Model() : 
rLog(new Log("LogModel")){}

Model::Model(vector<Mesh*>& InrMeshes) : 
rLog(new Log("LogModel")),
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

        InrModel.rLog = nullptr;
        InrModel.rMeshes.clear();
    }
}

Model::~Model() { Destroy(); }

void Model::Destroy()
{ 
    vector<Mesh*>::iterator rIt = rMeshes.begin();

    while(rIt != rMeshes.end())
    {
        delete *rIt;

        ++rIt;
    }

    if(rLog != nullptr)
        delete rLog;
}

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

        InrModel.rLog = nullptr;
    }

    return InrModel;
}

void Model::Draw(Shader& InrShader)
{
    vector<Mesh*>::iterator rIt = rMeshes.begin();

    while(rIt != rMeshes.end())
    {
        static_cast<Mesh*>(*rIt)->Draw(InrShader);

        ++rIt;
    }
}

void Model::RemoveMesh(uint64 IniHash)
{
	vector<Mesh*>::iterator rIt = rMeshes.begin();

	while(rIt != rMeshes.end())
	{
		if(*rIt != nullptr && static_cast<Mesh*>(*rIt)->GetHash() == IniHash)
		{	
			delete *rIt;

			rMeshes.erase(rIt);

			break;
		}

		++rIt;
	}
}

//Get Mesh from the Model by id
Mesh* Model::GetMesh(uint64 IniHash)
{
	vector<Mesh*>::iterator rIt = rMeshes.begin();

	while(rIt != rMeshes.end())
	{
		if(*rIt != nullptr && static_cast<Mesh*>(*rIt)->GetHash() == IniHash)		
			return *rIt;

		++rIt;
	}

	return nullptr;
}
