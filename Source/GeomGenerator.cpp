#include "GeomGenerator.h"

GeomGenerator::GeomGenerator() { Init(); }

GeomGenerator::GeomGenerator(uint32 IniVertexNum, uint32 IniHorizontalSub, uint32 IniVerticalSub) :
iVertexNum(IniVertexNum) { Init(); }

GeomGenerator::GeomGenerator(GeomGenerator const& InrGeomGenerator)
{
    iVertexNum = InrGeomGenerator.iVertexNum;

    Init();
}

GeomGenerator::GeomGenerator(GeomGenerator&& InrGeomGenerator)
{
    if(this != &InrGeomGenerator)
        iVertexNum = InrGeomGenerator.iVertexNum;
}

GeomGenerator GeomGenerator::operator=(GeomGenerator const& InrGeomGenerator)
{
    iVertexNum = InrGeomGenerator.iVertexNum;

    return InrGeomGenerator;
}

GeomGenerator GeomGenerator::operator=(GeomGenerator&& InrGeomGenerator)
{
    if(this != &InrGeomGenerator)
        iVertexNum = InrGeomGenerator.iVertexNum;

    return *this;
}

void GeomGenerator::SetVertexPosition(vec3 const& InrVector) 
{
    uint32 iLoopIndex = 0;

    while(iLoopIndex < rVectorList.size())
    {
        rVectorList[iLoopIndex].SetPosition(InrVector);

        ++iLoopIndex;
    }
}

void GeomGenerator::SetVertexPosition(vector<vec3> const& InrVectorList) 
{
    uint32 iLoopIndex = 0;

    uint32 iSize = static_cast<uint32>((rVectorList.size() - InrVectorList.size()) ? rVectorList.size() : InrVectorList.size());

    while(iLoopIndex < iSize)
    {
        rVectorList[iLoopIndex].SetPosition(InrVectorList[iLoopIndex]);

        ++iLoopIndex;
    }
}

void GeomGenerator::VertexLoop()
{

}

void GeomGenerator::Init() 
{
    uint32 iLoopIndex = 0;

    while(iLoopIndex < iVertexNum)
    {
        rVectorList.push_back(SVector());

        ++iLoopIndex;
    }
}