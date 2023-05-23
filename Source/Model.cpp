#include "Model.h"

Model::Model()
{

}

Model::Model(const Model& InrModel)
{
    rLog = InrModel.rLog;
    rTextures = InrModel.rTextures;
}

Model::Model(Model&& InrModel)
{
    if(this != &InrModel)
    {
        rLog = InrModel.rLog;
        rTextures = InrModel.rTextures;

        InrModel.rLog = nullptr;
        InrModel.rTextures = nullptr;
    }
}

Model::~Model()
{
    if(rTextures != nullptr)
    {
        delete rTextures;
    }
}

Model Model::operator=(const Model& InrModel)
{
    rLog = InrModel.rLog;
    rTextures = InrModel.rTextures;

    return InrModel;
}

Model& Model::operator=(Model&& InrModel)
{
    if(this != &InrModel)
    {
        rLog = InrModel.rLog;
        rTextures = InrModel.rTextures;

        InrModel.rLog = nullptr;
        InrModel.rTextures = nullptr;
    }

    return InrModel;
}

void Model::Draw(Shader& InrShader)
{
    for (uint32 i = 0; i < rMeshes.size(); i++)
    {
        rMeshes[i].Draw(InrShader);
    }
}

//TODO:Add Mesh in the Model
void Model::AddMesh(const Mesh& InrMesh)
{

}

//TODO:Get Mesh from the Model by id
Mesh& Model::GetMesh(uint32 IniID)
{

}

//TODO:Get Mesh from the Model by name
Mesh& Model::GetMesh(const string InsName)
{

}

//TODO:Get Texture from the Model by id
Texture& Model::GetTexture(uint32 IniID)
{

}

//TODO:Get Texture from the Model by name
Texture& Model::GetTexture(const string InsName)
{

}

//TODO:Get Mesh list from the Model
vector<Mesh> Model::GetMeshList()
{

}

//TODO:Get Texture list from the Model
vector<Texture*>& Model::GetTextureList()
{

}
