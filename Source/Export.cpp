#include "Export.h"

Export* Export::rExport = nullptr;

Export::Export() {}

Export* Export::GetInstance() 
{
    if(rExport == nullptr)
        rExport = new Export();

    return rExport;
}

void Export::ExportModel(char const* IncPath, Model* InrModel, EExportType const IneExportType)
{
    switch(static_cast<uint32>(IneExportType))
    {
        case EExportType::EET_OBJ:
            ExportAsObj(IncPath, InrModel);
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
            ExportAsObj(IncPath, InrModel);
    }
}


//TODO: Improve Exporter, add safety check for:
//file not open or access denied
//Data Structure Incomplete etc.
void Export::ExportAsObj(string const& InsPath, Model* InrModel)
{
    fstream rFile;

    string Path = InsPath;

    Path.append(".obj");

    rFile.open(Path, ios_base::in | ios_base::out | ios_base::app);

    uint32 iMeshListIndex = 0;
    uint32 iSubIndex = 0;

    vector<Mesh*> rMeshList = InrModel->GetMeshList();

    while(iMeshListIndex < rMeshList.size())
    {
        if(rMeshList[iMeshListIndex] != nullptr)
        {
            vector<SVector> rVectorList = rMeshList[iMeshListIndex]->GetVertices();
            vector<uint32> rIndicesList = rMeshList[iMeshListIndex]->GetIndices();
            
            rFile << "#Vector List" << endl;

            //Vertex List
            while(iSubIndex < rVectorList.size())
            {
                rFile << fixed << setprecision(5) << "v " << rVectorList[iSubIndex].Position.x << " " << rVectorList[iSubIndex].Position.y << " " << rVectorList[iSubIndex].Position.z << " " << 1.0f << std::endl; 

                ++iSubIndex;
            }

            iSubIndex = 0;

            rFile << "#Texture Coord List" << endl;

            //Texture coord List
            while(iSubIndex < rVectorList.size())
            {
                rFile << fixed << setprecision(5) << "vt " << rVectorList[iSubIndex].TexCoords.x << " " << rVectorList[iSubIndex].TexCoords.y << std::endl;
                ++iSubIndex;
            }

            iSubIndex = 0;

            rFile << "#Normal List" << endl;

            //Vertex Normal List
            while(iSubIndex < rVectorList.size())
            {                
                rFile << fixed << setprecision(5) << "vp " << rVectorList[iSubIndex].Normal.x << " " << rVectorList[iSubIndex].Normal.y << " " << rVectorList[iSubIndex].Normal.z << std::endl;
                ++iSubIndex;
            }

            iSubIndex = 0;

            rFile << "#Indices List" << endl;

            //Indices List
            while(iSubIndex < rIndicesList.size())
            {     
                if(!(iSubIndex % 3))
                    rFile << endl << "f ";

                rFile << " " << rIndicesList[iSubIndex] + 1;

                ++iSubIndex;
            }

            iSubIndex = 0;
        }

        ++iMeshListIndex;
    }

    iMeshListIndex = 0;


    rFile.close();
}


//TODO:Exporter for FBX format
void Export::ExportAsFBX(string const& IncPath, Model* InrModel)
{

}

//TODO:Exporter for DXF format
void Export::ExportAsDXF(string const& IncPath, Model* InrModel)
{

}

//TODO:Exporter for DAE format
void Export::ExportAsDAE(string const& IncPath, Model* InrModel)
{

}