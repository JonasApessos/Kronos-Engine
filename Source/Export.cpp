#include "Export.h"

Export* Export::rExport = nullptr;

FileHandler Export::rFile = FileHandler();

Export::Export() {}

Export* Export::GetInstance() 
{
    if(rExport == nullptr)
        rExport = new Export();

    return rExport;
}

void Export::ExportModel(char const* IncPath, Model* InrModel, EExportType const IneExportType)
{
    string sPath = IncPath;

    rFile.SetFileName(sPath.substr(sPath.find_last_of("/\\") + 1));
    rFile.SetFilePath(sPath.erase(sPath.find_last_of("/\\") + 1));
    rFile.SetBitFlagMode(ios_base::out | ios_base::app);

    switch(static_cast<uint32>(IneExportType))
    {
        case EExportType::EET_OBJ:
            ExportAsObj(InrModel);
            break;
        case EExportType::EET_FBX:
            //ExportAsFBX(IncPath, InrModel);
            break;
        case EExportType::EET_DXF:
            //ExportAsDXF(IncPath, InrModel);
            break;
        case EExportType::EET_DAE:
            //ExportAsDAE(IncPath, InrModel);
            break;
        default:
            ExportAsObj(InrModel);
    }
}


//TODO: Improve Exporter, add safety check for:
//file not open or access denied
//Data Structure Incomplete etc.
void Export::ExportAsObj(Model* InrModel)
{
    string sData = "";

    rFile.SetFileName(rFile.GetFileName().append(".obj"));

    uint32 iMeshListIndex = 0;
    uint32 iSubIndex = 0;

    vector<Mesh*> rMeshList = InrModel->GetMeshList();

    while(iMeshListIndex < rMeshList.size())
    {
        if(rMeshList[iMeshListIndex] != nullptr)
        {
            vector<SVector> rVectorList = rMeshList[iMeshListIndex]->GetVertices();
            vector<uint32> rIndicesList = rMeshList[iMeshListIndex]->GetIndices();
            
            sData.append("#Vector List\r\n");

            //Vertex List
            while(iSubIndex < rVectorList.size())
            {
                
                sData.append("v " + to_string(rVectorList[iSubIndex].Position.x) + " " + to_string(rVectorList[iSubIndex].Position.y) + " " + to_string(rVectorList[iSubIndex].Position.z) + " " + to_string(1.0f) + "\r\n"); 

                ++iSubIndex;
            }


            iSubIndex = 0;

            sData.append("#Texture Coord List\r\n");

            //Texture coord List
            while(iSubIndex < rVectorList.size())
            {
                sData.append("vt " + to_string(rVectorList[iSubIndex].TexCoords.x) + " " + to_string(rVectorList[iSubIndex].TexCoords.y) + "\r\n");
                ++iSubIndex;
            }

            iSubIndex = 0;

            sData.append("#Normal List\r\n");

            //Vertex Normal List
            while(iSubIndex < rVectorList.size())
            {                
                sData.append("vp " + to_string(rVectorList[iSubIndex].Normal.x) + " " + to_string(rVectorList[iSubIndex].Normal.y) + " " + to_string(rVectorList[iSubIndex].Normal.z) + "\r\n");
                ++iSubIndex;
            }

            iSubIndex = 0;

            sData.append("#Indices List\r\n");

            //Indices List
            while(iSubIndex < rIndicesList.size())
            {     
                if(!(iSubIndex % 3))
                    sData.append("\r\nf ");

                sData.append(" " + to_string(rIndicesList[iSubIndex] + 1));

                ++iSubIndex;
            }

            rFile.Write(sData);

            iSubIndex = 0;
        }

        ++iMeshListIndex;
    }

    iMeshListIndex = 0;
}


//TODO:Exporter for FBX format
void Export::ExportAsFBX(Model* InrModel)
{

}

//TODO:Exporter for DXF format
void Export::ExportAsDXF(Model* InrModel)
{

}

//TODO:Exporter for DAE format
void Export::ExportAsDAE(Model* InrModel)
{

}