#include "Model.h"


Model::Model(char* IncPath)
{
    LoadModel(IncPath);

    rLog = Log("LogModel");
}

Model::Model(const char* IncPath)
{
    LoadModel(IncPath);

    rLog = Log("LogModel");
}

void Model::Draw(Shader& InrShader)
{
    for (uint32 i = 0; i < rMeshes.size(); i++)
    {
        rMeshes[i].Draw(InrShader);
    }
}

void Model::LoadModel(string InsPath)
{
    rScene = rImporter.ReadFile(InsPath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!rScene || rScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !rScene->mRootNode)
    {
        string ErrorMsg = "ERROR::ASSIMP::";

        rLog.WriteAndDisplay(ErrorMsg.append(rImporter.GetErrorString()));

        return;
    }

    sDirectory = InsPath.substr(0, InsPath.find_last_of("/"));

    ProcessNode(rScene->mRootNode, rScene);
}

void Model::ProcessNode(aiNode* InrNode, const aiScene* InrScene)
{
    for (uint32 i = 0; i < InrNode->mNumMeshes; i++)
    {
        aiMesh* rMesh = InrScene->mMeshes[InrNode->mMeshes[i]];
        rMeshes.push_back(ProcessMesh(rMesh, InrScene));
    }

    for (uint32 i = 0; i < InrNode->mNumChildren; i++)
    {
        ProcessNode(InrNode->mChildren[i], InrScene);
    }
}

Mesh Model::ProcessMesh(aiMesh* InrMesh, const aiScene* InrScene)
{
    vector<Vertex> rVertices;
    vector<uint32> rIndices;
    vector<Texture> rTempTextures;

    for (uint32 i = 0; i < InrMesh->mNumVertices; i++)
    {
        Vertex rVertex;

        
        rVertex.VertexData.Position.x = InrMesh->mVertices[i].x;
        rVertex.VertexData.Position.y = InrMesh->mVertices[i].y;
        rVertex.VertexData.Position.z = InrMesh->mVertices[i].z;

        rVertex.VertexData.Normal.x = InrMesh->mNormals[i].x;
        rVertex.VertexData.Normal.y = InrMesh->mNormals[i].y;
        rVertex.VertexData.Normal.z = InrMesh->mNormals[i].z;

        if (InrMesh->mTextureCoords[0])
        {
            rVertex.VertexData.TexCoords.x = InrMesh->mTextureCoords[0][i].x;
            rVertex.VertexData.TexCoords.y = InrMesh->mTextureCoords[0][i].y;
        }
        else
            rVertex.VertexData.TexCoords = vec2(0.0f, 0.0f);

        rVertices.push_back(rVertex);
    }

    for (uint32 i = 0; i < InrMesh->mNumFaces; i++)
    {
        aiFace rFace = InrMesh->mFaces[i];

        for (uint32 j = 0; j < rFace.mNumIndices; j++)
        {
            rIndices.push_back(rFace.mIndices[j]);
        }
    }

    if (InrMesh->mMaterialIndex >= 0)
    {
        aiMaterial* rMaterial = InrScene->mMaterials[InrMesh->mMaterialIndex];

        vector<Texture> rDiffuseMaps = LoadMaterialTextures(rMaterial, aiTextureType_DIFFUSE);
        rTempTextures.insert(rTempTextures.end(), rDiffuseMaps.begin(), rDiffuseMaps.end());

        vector<Texture> rSpecularMaps = LoadMaterialTextures(rMaterial, aiTextureType_SPECULAR);
        rTempTextures.insert(rTempTextures.end(), rSpecularMaps.begin(), rSpecularMaps.end());
    }

    return Mesh(rVertices, rIndices, rTextures);
}

vector<Texture> Model::LoadMaterialTextures(aiMaterial* InrMat, aiTextureType InrType)
{
    vector<Texture> TempTextures;

    const uint32 TexCount = InrMat->GetTextureCount(InrType);

    aiString sStr;

    string TempPath = "";

    for (uint32 i = 0; i < TexCount; i++)
    {
        InrMat->GetTexture(InrType, i, &sStr);

        TempPath = "";

        TempPath.append(sDirectory);
        TempPath.append("/");
        TempPath.append(sStr.C_Str());

        for (uint32 j = 0; j < rTextures->size(); j++)
        {
            if (rTextures->at(j)->sPath == TempPath)
                continue;
        }

        Texture NewTexture(TempPath.c_str(), InrType, ETextureDataType::ETDT_Texture2D, ETextureSlot::ETS_Slot0);

        TempTextures.push_back(NewTexture);
    }

    return TempTextures;
}
