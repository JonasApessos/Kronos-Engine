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

void Export::ExportModel(char const* IncPath, Model& InrModel, EExportType const IneExportType)
{
    string sPath = IncPath;

    rFile.SetFileName(sPath.substr(sPath.find_last_of("/\\") + 1));
    rFile.SetFilePath(sPath.erase(sPath.find_last_of("/\\") + 1));
    rFile.SetBitFlagMode(ios_base::out | ios_base::app);

    switch(static_cast<uint32>(IneExportType))
    {
        case static_cast<uint32>(EExportType::EET_OBJ):
            ExportAsObj(InrModel);
            break;
        case static_cast<uint32>(EExportType::EET_FBX):
            //ExportAsFBX(IncPath, InrModel);
            break;
        case static_cast<uint32>(EExportType::EET_DXF):
            //ExportAsDXF(IncPath, InrModel);
            break;
        case static_cast<uint32>(EExportType::EET_DAE):
            //ExportAsDAE(IncPath, InrModel);
            break;
        default:
            ExportAsObj(InrModel);
    }
}


//TODO: Improve Exporter, add safety check for:
//file not open or access denied
//Data Structure Incomplete etc.
void Export::ExportAsObj(Model& InrModel)
{
    string sData = "";

    rFile.SetFileName(rFile.GetFileName().append(".obj"));

    uint32 iMeshListIndex = 0;
    uint32 iSubIndex = 0;

    vector<Mesh> rMeshList = InrModel.GetMeshList();

    while(iMeshListIndex < rMeshList.size())
    {
        vector<SVector> rVectorList = rMeshList[iMeshListIndex].GetVertices();
        vector<uint32> rIndicesList = rMeshList[iMeshListIndex].GetIndices();
        
        sData.append("#Vector List\r\n");

        //Vertex List
        while(iSubIndex < rVectorList.size())
        {
            sData.append("v " + to_string(rVectorList[iSubIndex].rPosition.x) + " " + to_string(rVectorList[iSubIndex].rPosition.y) + " " + to_string(rVectorList[iSubIndex].rPosition.z) + " " + to_string(1.0f) + "\r\n"); 

            ++iSubIndex;
        }


        iSubIndex = 0;

        sData.append("#Texture Coord List\r\n");

        //Texture coord List
        while(iSubIndex < rVectorList.size())
        {
            sData.append("vt " + to_string(rVectorList[iSubIndex].rTexCoords.x) + " " + to_string(rVectorList[iSubIndex].rTexCoords.y) + "\r\n");
            ++iSubIndex;
        }

        iSubIndex = 0;

        sData.append("#rNormal List\r\n");

        //Vertex rNormal List
        while(iSubIndex < rVectorList.size())
        {                
            sData.append("vp " + to_string(rVectorList[iSubIndex].rNormal.x) + " " + to_string(rVectorList[iSubIndex].rNormal.y) + " " + to_string(rVectorList[iSubIndex].rNormal.z) + "\r\n");
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

        ++iMeshListIndex;
    }

    iMeshListIndex = 0;
}


//TODO:Exporter for FBX format
void Export::ExportAsFBX(Model& InrModel)
{

}

//TODO:Exporter for DXF format
void Export::ExportAsDXF(Model& InrModel)
{

}

//TODO:Exporter for DAE format
void Export::ExportAsDAE(Model& InrModel)
{

}