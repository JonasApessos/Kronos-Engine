#include "Model.h"


Model::Model(char* IncPath)
{
    LoadModel(IncPath);
}

Model::Model(const char* IncPath)
{
    LoadModel(IncPath);
}

void Model::Draw(Shader& InrShader)
{
    for (unsigned int i = 0; i < rMeshes.size(); i++)
    {
        rMeshes[i].Draw(InrShader);
    }
}

void Model::LoadModel(string InsPath)
{
    rScene = rImporter.ReadFile(InsPath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!rScene || rScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !rScene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << rImporter.GetErrorString() << endl;

        return;
    }

    sDirectory = InsPath.substr(0, InsPath.find_last_of("/"));

    //cout << rScene->mRootNode->mNumChildren << endl;

    ProcessNode(rScene->mRootNode, rScene);
}

void Model::ProcessNode(aiNode* InrNode, const aiScene* InrScene)
{
    //cout << "In Process Node" << endl;

    //cout << "Num of Meshes: " << InrNode->mNumMeshes << endl;
    for (unsigned int i = 0; i < InrNode->mNumMeshes; i++)
    {
        aiMesh* rMesh = InrScene->mMeshes[InrNode->mMeshes[i]];
        rMeshes.push_back(ProcessMesh(rMesh, InrScene));
    }

    //cout << "Num Of Children: " << InrNode->mNumChildren << endl;
    for (unsigned int i = 0; i < InrNode->mNumChildren; i++)
    {
        ProcessNode(InrNode->mChildren[i], InrScene);

        cout << i << endl;
    }
}

Mesh Model::ProcessMesh(aiMesh* InrMesh, const aiScene* InrScene)
{
    vector<Vertex> rVertices;
    vector<unsigned int> rIndices;
    vector<Texture> rTextures;

    for (unsigned int i = 0; i < InrMesh->mNumVertices; i++)
    {
        Vertex rVertex;

        
        rVertex.VertexData.Position.x = InrMesh->mVertices[i].x;
        rVertex.VertexData.Position.y = InrMesh->mVertices[i].y;
        rVertex.VertexData.Position.z = InrMesh->mVertices[i].z;

        //cout << "Pos - X: " << rVertex.Position.x << " Y: " << rVertex.Position.y << " Z: " << rVertex.Position.z << endl;

        rVertex.VertexData.Normal.x = InrMesh->mNormals[i].x;
        rVertex.VertexData.Normal.y = InrMesh->mNormals[i].y;
        rVertex.VertexData.Normal.z = InrMesh->mNormals[i].z;

        //cout << "Norm - X: " << rVertex.Normal.x << " Y: " << rVertex.Normal.y << " Z: " << rVertex.Normal.z << endl;

        if (InrMesh->mTextureCoords[0])
        {
            rVertex.VertexData.TexCoords.x = InrMesh->mTextureCoords[0][i].x;
            rVertex.VertexData.TexCoords.y = InrMesh->mTextureCoords[0][i].y;
        }
        else
            rVertex.VertexData.TexCoords = vec2(0.0f, 0.0f);

        //cout << "UV - X: " << rVertex.TexCoords.x << " Y: " << rVertex.TexCoords.y << endl;

        

        rVertices.push_back(rVertex);
    }

    for (unsigned int i = 0; i < InrMesh->mNumFaces; i++)
    {
        aiFace rFace = InrMesh->mFaces[i];

        for (unsigned int j = 0; j < rFace.mNumIndices; j++)
        {
            rIndices.push_back(rFace.mIndices[j]);
        }
    }

    if (InrMesh->mMaterialIndex >= 0)
    {
        cout << "Num Materials: " << InrScene->mNumMaterials << endl;

        aiMaterial* rMaterial = InrScene->mMaterials[InrMesh->mMaterialIndex];

        vector<Texture> rDiffuseMaps = LoadMaterialTextures(rMaterial, aiTextureType_DIFFUSE);
        rTextures.insert(rTextures.end(), rDiffuseMaps.begin(), rDiffuseMaps.end());

        vector<Texture> rSpecularMaps = LoadMaterialTextures(rMaterial, aiTextureType_SPECULAR);
        rTextures.insert(rTextures.end(), rSpecularMaps.begin(), rSpecularMaps.end());

       // cout << " Tex loaded" << endl;
    }

    return Mesh(rVertices, rIndices, rTextures);
}

vector<Texture> Model::LoadMaterialTextures(aiMaterial* InrMat, aiTextureType InrType)
{
    vector<Texture> TempTextures;

    const uint32_t TexCount = InrMat->GetTextureCount(InrType);

    aiString sStr;

    string TempPath = "";

    for (uint32_t i = 0; i < TexCount; i++)
    {
        cout << "TexCount: " << TexCount << endl;
        //cout << "Counter: " << i << endl;

        InrMat->GetTexture(InrType, i, &sStr);

        TempPath = "";

        TempPath.append(sDirectory);
        TempPath.append("/");
        TempPath.append(sStr.C_Str());

        for (unsigned int j = 0; j < rTextures.size(); j++)
        {
            if (rTextures[j].sPath == TempPath)
                continue;
        }

        //cout << TempPath << endl;

        Texture NewTexture(TempPath.c_str(), InrType, ETextureDataType::ETDT_Texture2D, ETextureSlot::ETS_Slot0);

        TempTextures.push_back(NewTexture);

        //bool skip = false;

        /*for (unsigned int j = 0; j < rTextures.size(); j++)
        {
            if (std::strcmp(rTextures[j].sPath.c_str(), sStr.C_Str()) == 0)
            {
                TempTextures.push_back(rTextures[j]);
                cout << rTextures[j].GetId() << endl;

                skip = true;
                break;
            }
        }*/
        /*if (!skip)
        {
            aiString TempPath;

            TempPath.Append(sDirectory.c_str());
            TempPath.Append("/");
            TempPath.Append(sStr.C_Str());

            Texture TempTexture(TempPath.C_Str(), ETextureType::ETT_Albedo, ETextureDataType::ETDT_Texture2D, ETextureSlot::ETS_Slot0);

            TempTexture.SetTextureWrap(ETextureWrap::ETW_Repeat);
            TempTexture.SetTextureMinFilter(ETextureMinFilter::ETMF_LinearMipMapLinear);
            TempTexture.SetTextureMagFilter(ETextureMagFilter::ETMF_Linear);


            TempTextures.push_back(TempTexture);
            rTextures.push_back(TempTexture);
        }*/
    }

    return TempTextures;
}
