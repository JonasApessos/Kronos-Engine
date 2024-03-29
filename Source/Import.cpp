#include "Import.h"

Log Import::rLog("LogImport");

Import* Import::rImport = nullptr;

Import::Import() {}

void Import::LoadModel(char const* InsPath, Model& InrModel)
{
    Importer rImporter;

    vector<Mesh> rMeshes;

    string const sDirectory = string(InsPath).substr(0, string(InsPath).find_last_of("/"));

    aiScene const* rScene = rImporter.ReadFile(InsPath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!rScene || rScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !rScene->mRootNode)
    {
        string ErrorMsg = "ERROR::ASSIMP::";

        rLog.WriteAndDisplay(ErrorMsg.append(rImporter.GetErrorString()), ELogSeverity::ELS_Error);
    }

    ProcessNode(sDirectory, rScene->mRootNode, rScene, rMeshes);

    InrModel.SetMeshList(rMeshes);
}

Import* Import::GetInstance()
{ 
    if(rImport == nullptr)
        rImport = new Import();
        
    return rImport; 
}

//Process scene nodes
void Import::ProcessNode(string const& InsDirectory, aiNode* InrNode, aiScene const* InrScene, vector<Mesh>& InrMeshes)
{
    uint64 iMeshIndex = 0;

    while(iMeshIndex < InrNode->mNumMeshes)
    {
        aiMesh* rMesh = InrScene->mMeshes[InrNode->mMeshes[iMeshIndex]];
        InrMeshes.push_back(ProcessMesh(InsDirectory, rMesh, InrScene));

        ++iMeshIndex;
    }

    iMeshIndex = 0;

    while(iMeshIndex < InrNode->mNumChildren)
    {
        ProcessNode(InsDirectory, InrNode->mChildren[iMeshIndex], InrScene, InrMeshes);

        ++iMeshIndex;
    }
}

//Load mesh object
Mesh Import::ProcessMesh(string const& InsDirectory, aiMesh* InrMesh, aiScene const* InrScene)
{
    vector<SVector> rVertices;
    vector<uint32> rIndices;
    vector<Texture> rTempTextures;

    uint32 iIndex = 0;
    uint32 iSubIndex = 0;

    SVector rVertex;
    aiFace rFace;

    //Get Vertices, rNormal and UV from mesh
    while(iIndex < InrMesh->mNumVertices)
    {
        rVertex.rPosition.x = InrMesh->mVertices[iIndex].x;
        rVertex.rPosition.y = InrMesh->mVertices[iIndex].y;
        rVertex.rPosition.z = InrMesh->mVertices[iIndex].z;

        rVertex.rNormal.x = InrMesh->mNormals[iIndex].x;
        rVertex.rNormal.y = InrMesh->mNormals[iIndex].y;
        rVertex.rNormal.z = InrMesh->mNormals[iIndex].z;

        if (InrMesh->mTextureCoords[0] != nullptr)
        {
            rVertex.rTexCoords.x = InrMesh->mTextureCoords[0][iIndex].x;
            rVertex.rTexCoords.y = InrMesh->mTextureCoords[0][iIndex].y;
        }
        else
            rVertex.rTexCoords = vec2(0.0f, 0.0f);

        rVertices.push_back(rVertex);

        ++iIndex;
    }

    iIndex = 0;

    //Get Faces from mesh
    while(iIndex < InrMesh->mNumFaces)
    {
        rFace = InrMesh->mFaces[iIndex];

        while(iSubIndex < rFace.mNumIndices)
        {
            rIndices.push_back(rFace.mIndices[iSubIndex]);

            ++iSubIndex;
        }

        iSubIndex = 0;

        ++iIndex;
    }

    //Detect materials and load necessary linked textures to materials
    if (InrMesh->mMaterialIndex > 0)
    {
        aiMaterial* rMaterial = InrScene->mMaterials[InrMesh->mMaterialIndex];

        vector<Texture> rDiffuseMaps = LoadMaterialTextures(InsDirectory, rMaterial, aiTextureType_DIFFUSE);
        rTempTextures.insert(rTempTextures.end(), rDiffuseMaps.begin(), rDiffuseMaps.end());

        vector<Texture> rSpecularMaps = LoadMaterialTextures(InsDirectory, rMaterial, aiTextureType_SPECULAR);
        rTempTextures.insert(rTempTextures.end(), rSpecularMaps.begin(), rSpecularMaps.end());
    }

    return Mesh(rVertices, rIndices, rTempTextures);
}

//Load texture for material linking
vector<Texture> Import::LoadMaterialTextures(string const& InsDirectory, aiMaterial* InrMat, aiTextureType InrType)
{
    vector<Texture> rTempTextures;

    uint32 const iTexCount = InrMat->GetTextureCount(InrType);

    aiString sStr;

    string TempPath = "";

    uint32 iIndex = 0;
    uint32 iSubIndex = 0;

    while(iIndex < iTexCount)
    {
        InrMat->GetTexture(InrType, iIndex, &sStr);

        TempPath = "";

        TempPath.append(InsDirectory);
        TempPath.append("/");
        TempPath.append(sStr.C_Str());

        while(iSubIndex < rTempTextures.size())
        {
            if (rTempTextures[iSubIndex].sPath == TempPath)
                cout << rTempTextures[iSubIndex].sPath << "\r\n";

            ++iSubIndex;
        }

        iSubIndex = 0;

        rTempTextures.push_back(Texture(TempPath.c_str(), InrType, EGLTextureDataType::EGLTDT_Texture2D, EGLTextureSlot::EGLTS_Slot0));

        ++iIndex;
    }

    return rTempTextures;
}