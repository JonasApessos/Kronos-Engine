#include "Import.h"

Import::Import(char* IncPath)
{
    LoadModel(IncPath);
}

Import::Import(const char* IncPath)
{
    LoadModel(IncPath);
}

void Import::LoadModel(string InsPath)
{
    Importer rImporter;

    rScene = rImporter.ReadFile(InsPath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!rScene || rScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !rScene->mRootNode)
    {
        string ErrorMsg = "ERROR::ASSIMP::";

        if(rLog != nullptr)
            rLog->WriteAndDisplay(ErrorMsg.append(rImporter.GetErrorString()));

        return;
    }

    sDirectory = InsPath.substr(0, InsPath.find_last_of("/"));

    ProcessNode(rScene->mRootNode, rScene);
}

void Import::ProcessNode(aiNode* InrNode, const aiScene* InrScene)
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

Mesh Import::ProcessMesh(aiMesh* InrMesh, const aiScene* InrScene)
{
    vector<FVector> rVertices;
    vector<uint32> rIndices;
    vector<Texture> rTempTextures;

    for (uint32 i = 0; i < InrMesh->mNumVertices; i++)
    {
        FVector rVertex;

        
        rVertex.Position.x = InrMesh->mVertices[i].x;
        rVertex.Position.y = InrMesh->mVertices[i].y;
        rVertex.Position.z = InrMesh->mVertices[i].z;

        rVertex.Normal.x = InrMesh->mNormals[i].x;
        rVertex.Normal.y = InrMesh->mNormals[i].y;
        rVertex.Normal.z = InrMesh->mNormals[i].z;

        if (InrMesh->mTextureCoords[0])
        {
            rVertex.TexCoords.x = InrMesh->mTextureCoords[0][i].x;
            rVertex.TexCoords.y = InrMesh->mTextureCoords[0][i].y;
        }
        else
            rVertex.TexCoords = vec2(0.0f, 0.0f);

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
        //rTextures->insert(rTempTextures.end(), rDiffuseMaps.begin(), rDiffuseMaps.end());

        vector<Texture> rSpecularMaps = LoadMaterialTextures(rMaterial, aiTextureType_SPECULAR);
        //rTextures->insert(rTempTextures.end(), rSpecularMaps.begin(), rSpecularMaps.end());
    }

    return Mesh(rVertices, rIndices, rTextures);
}

vector<Texture> Import::LoadMaterialTextures(aiMaterial* InrMat, aiTextureType InrType)
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
                cout << rTextures->at(j)->sPath << std::endl;
        }

        Texture NewTexture(TempPath.c_str(), InrType, ETextureDataType::ETDT_Texture2D, ETextureSlot::ETS_Slot0);

        TempTextures.push_back(NewTexture);
    }

    return TempTextures;
}