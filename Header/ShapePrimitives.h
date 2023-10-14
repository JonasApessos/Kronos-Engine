#pragma once

#include "MacroUtils.h"

#include <assert.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Log.h"
#include "Utils.h"
#include "Primitives.h"
#include "Model.h"
#include "Math.h"

using glm::vec3, glm::mat4;
using KronosPrim::uint32;

/** \struct SShapePrimBase
*   \brief abstract structure to inherit from
*   \todo Complete docs for doxygen
*/
struct SShapePrimBase
{
    //
    /*! \var uint32 iResW
	*	\brief Width Resolution that shapes will use to generate Vertices/Indices
	*
	*	\var uint32 iResH
	*	\brief Height Resolution that shapes will use to generate Vertices/Indices
    *
    *   \var float fRadius
	*	\brief Radius of object (can be used for scaling ex. Cube)
    * 
    *   \var float fHeight
	*	\brief Height of Shape (Can be used to non-uniform scale for height)
    *
    *   \var Model rModel
	*	\brief Model object that will encapsulate the mesh data
    * */

    //Resolution that shapes will use to generate Vertices/Indices
    uint32 iResW = 8, iResH = 8;

    //Radius of object (can be used for scaling ex. Cube)
    float fRadius = 1.0f;

    //Height of Shape (Can be used to non-uniform scale for height)
    float fHeight = 1.0f;

    //Model object that will encapsulate the mesh data
    Model rModel;

    inline void SetResW(uint32 IniResW) noexcept;
    inline void SetResH(uint32 IniResH) noexcept;
    inline void SetRes(uint32 IniResW, uint32 IniResH) noexcept;

    inline void SetRadius(float InfRadius);
    inline void SetHeight(float InfHeight);

    inline uint32 GetResW() const;
    inline uint32 GetResH() const;

    inline uint32 GetRadius() const;
    inline uint32 GetHeight() const;

    virtual inline void Translate(vec3 const& InrTranslate);
    virtual inline void Rotate(float fDegrees, vec3 const& InrRotate);
    virtual inline void Scale(vec3 const& InrScale);

    virtual inline Model GetModel();

    virtual void GenerateVertexData(vector<SVector>& InrVertexList) = 0;
    virtual void GenerateIndicesData(vector<uint32>& InrIndicesList) = 0;
};

inline void SShapePrimBase::SetResW(uint32 IniResW) noexcept { iResW = IniResW; }
inline void SShapePrimBase::SetResH(uint32 IniResH) noexcept { iResH = IniResH; }
inline void SShapePrimBase::SetRes(uint32 IniResW, uint32 IniResH) noexcept { iResW = IniResW; iResH = IniResH; }

inline void SShapePrimBase::SetRadius(float InfRadius) { fRadius = InfRadius; }
inline void SShapePrimBase::SetHeight(float InfHeight) { fHeight = InfHeight; }

inline uint32 SShapePrimBase::GetResW() const { return iResW; }
inline uint32 SShapePrimBase::GetResH() const { return iResH; }

inline uint32 SShapePrimBase::GetRadius() const { return fRadius; }
inline uint32 SShapePrimBase::GetHeight() const { return fHeight; }

inline void SShapePrimBase::Translate(vec3 const& InrTranslate) { rModel.Translate(InrTranslate); }
inline void SShapePrimBase::Rotate(float fDegrees, vec3 const& InrRotate) { rModel.Rotate(fDegrees, InrRotate); }
inline void SShapePrimBase::Scale(vec3 const& InrScale) { rModel.Scale(InrScale); }

inline Model SShapePrimBase::GetModel() { return rModel; }

/** \struct SShapePrimPlane
*   \brief Primitive shape that generates a plane mesh
*   \todo Add correct normal and texture coord
*/
struct SShapePrimPlane : SShapePrimBase
{
    SShapePrimPlane()
    {
        PlaneConstruction();
    }

    void PlaneConstruction()
    {
        vector<SVector> rVertex;
        vector<uint32> rIndices;
        vector<Texture> rTextures = {};

        GenerateVertexData(rVertex);
        GenerateIndicesData(rIndices);

        rModel.AddMesh(Mesh(rVertex, rIndices, rTextures));

        vector<Mesh> rMeshList = rModel.GetMeshList();

        rMeshList[0].SetDrawMode(EGLDrawMode::EGLDM_TriangleStrip);

        rModel.SetMeshList(rMeshList);
    }

    void GenerateVertexData(vector<SVector>& InrVertexList) override
    {
        InrVertexList = {
            SVector(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)),
            SVector(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)),
            SVector(vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)),
            SVector(vec3(1.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f))
        };
        
    }

    void GenerateIndicesData(vector<uint32>& InrIndicesList) override
    {
        InrIndicesList = {
            0,1,2,3
        };
    }
};

//TODO: Add correct normal and texture coord
/** \struct SShapePrimCube
*   \brief Primitive shape that generates a cube mesh
*   \todo Add correct normal and texture coord
*/
struct SShapePrimCube : SShapePrimBase
{
    SShapePrimCube()
    {
        BoxConstruction();
    }

    void BoxConstruction()
    {
        vector<SVector> rVertex;
        vector<uint32> rIndices;
        vector<Texture> rTextures = {};

        GenerateVertexData(rVertex);
        GenerateIndicesData(rIndices);

        rModel.AddMesh(Mesh(rVertex, rIndices, rTextures));

        vector<Mesh> rMeshList = rModel.GetMeshList();

        rMeshList[0].SetDrawMode(EGLDrawMode::EGLDM_TriangleStrip);

        rModel.SetMeshList(rMeshList);
    }

    void GenerateVertexData(vector<SVector>& InrVertexList) override
    {
        InrVertexList = {
            SVector(vec3(0.0f, 0.0f, 0.0f), vec3(-1.0f, -1.0f, 1.0f), vec2(0.0f, 0.0f)),
            SVector(vec3(0.0f, 1.0f, 0.0f), vec3(-1.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f)),
            SVector(vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, -1.0f, 1.0f), vec2(0.0f, 1.0f)),
            SVector(vec3(1.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)),
            SVector(vec3(1.0f, 0.0f, 1.0f), vec3(1.0f, -1.0f, -1.0f), vec2(0.0f, 0.0f)),
            SVector(vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, -1.0f), vec2(1.0f, 0.0f)),
            SVector(vec3(0.0f, 0.0f, 1.0f), vec3(-1.0f, -1.0f, -1.0f), vec2(0.0f, 1.0f)),
            SVector(vec3(0.0f, 1.0f, 1.0f), vec3(-1.0f, 1.0f, -1.0f), vec2(1.0f, 1.0f))
        };
        
    }

    void GenerateIndicesData(vector<uint32>& InrIndicesList) override
    {
        InrIndicesList = {
            1,7,3,5,
            5,4,3,2,
            3,2,1,0,
            1,0,7,6,
            7,6,5,4,
            2,4,0,6
        };
    }
};

//TODO: Add correct normal and texture coord
/** \struct SShapePrimSphere
*   \brief Primitive shape that generates a sphere mesh
*   \todo Add correct normal and texture coord
*/
struct SShapePrimSphere : SShapePrimBase
{
    uint32 iVertexNum = 0;

    SShapePrimSphere()
    {
        SphereConsruction();
    }

    void SphereConsruction()
    {
        SetRes(32, 16);

        if(iResW < 3)
            iResW = 3;

        if(iResH < 3)
            iResH = 3;

        vector<SVector> rVertex = {};

        vector<uint32> rIndices = {};

        vector<Texture> rTextures = {};

        GenerateVertexData(rVertex);

        GenerateIndicesData(rIndices);

        rModel.AddMesh(Mesh(rVertex, rIndices, rTextures));
    }

    void GenerateVertexData(vector<SVector>& InrVertexList) override
    {
        uint32 iLoopW = 0, iLoopH = 1;

        const float fFullRad = DOUBLE_PI_F/static_cast<float>(iResW);
        const float fHalfRad = PI_F/static_cast<float>(iResH);
        const float fQuarterRad = HALF_PI_F/static_cast<float>(iResH);

        float fSinDistanceRadius = 0.0f, fCosDistanceRadius = 0.0f, fCurbe = 0.0f;

        InrVertexList.push_back(SVector(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f), vec2(0.0f)));

        while(iLoopW < iResW)
        {
            fSinDistanceRadius = sinf(fFullRad * static_cast<float>(iLoopW));
            fCosDistanceRadius = cosf(fFullRad * static_cast<float>(iLoopW));

            while(iLoopH + 1 < iResH + 1)
            {
                fCurbe = sinf(fHalfRad * static_cast<float>(iLoopH));

                InrVertexList.push_back(
                    SVector(
                    vec3(fCosDistanceRadius * fCurbe * fRadius,
                    SquarePow(sinf(fQuarterRad * static_cast<float>(iLoopH))) * fRadius * 2.f,
                    fSinDistanceRadius * fCurbe * fRadius),
                    vec3(0.0f),
                    vec2(0.0f)));

                ++iLoopH;
            }

            ++iLoopW;

            iLoopH = 1;
        }

        InrVertexList.push_back(SVector(vec3(0.0f, fRadius*2.f, 0.0f), vec3(0.0f), vec2(0.0f)));

        iVertexNum = static_cast<uint32>(InrVertexList.size());
    }

    void GenerateIndicesData(vector<uint32>& InrIndicesList) override
    {
        uint32 iLoopW = 0;
        uint32 iLoopH = 0;

        uint32 iCurIndice = 1;

        //Loop throught the width of the sphere
        while(iLoopW < iResW - 1)
        {
            //Bottom fan Indices
            InrIndicesList.push_back(0);
            InrIndicesList.push_back(1 + (iLoopW * (iResH-1)));
            InrIndicesList.push_back(1 + ((iLoopW + 1) * (iResH-1)));

            //Loop throught the height of the sphere at the specific point of the width
            while(iLoopH < iResH - 2)
            {
                //Height indices travel
                InrIndicesList.push_back(iCurIndice);
                InrIndicesList.push_back(iCurIndice+1);
                InrIndicesList.push_back(iCurIndice+iResH);

                InrIndicesList.push_back(iCurIndice+iResH);
                InrIndicesList.push_back(iCurIndice+iResH-1);
                InrIndicesList.push_back(iCurIndice);

                ++iLoopH;
                ++iCurIndice;
            }            

            //Top fan Indices
            InrIndicesList.push_back(iVertexNum-1);
            InrIndicesList.push_back(iVertexNum - 2 - (iResH-1) * iLoopW);
            InrIndicesList.push_back(iVertexNum - 2 - (iResH-1) * (iLoopW+1));

            iLoopH = 0;

            ++iLoopW;

            iCurIndice = 1 + iLoopW * (iResH-1);
        }

        //Looping around heigth indices
        iLoopW = 0;
        iCurIndice = 1 + (iResH-1) * (iResW-1);

        while(iLoopW < iResH-2)
        {
            InrIndicesList.push_back(iCurIndice);
            InrIndicesList.push_back(iCurIndice + 1);
            InrIndicesList.push_back(1 + 1 * (iLoopW+1));
            InrIndicesList.push_back(1 + 1 * (iLoopW+1));
            InrIndicesList.push_back((iLoopW+1));
            InrIndicesList.push_back(iCurIndice);
            
            ++iLoopW;
            ++iCurIndice;
        }

        //Looping around bottom fan indices 
        InrIndicesList.push_back(0);
        InrIndicesList.push_back(1 + (iResW-1)*(iResH-1));
        InrIndicesList.push_back(1);
        
        //Looping around Top fan indices
        InrIndicesList.push_back(iVertexNum-1);
        InrIndicesList.push_back(iResH-1);
        InrIndicesList.push_back(iVertexNum-2);
    }
};

//TODO: Add correct normal and texture coord
/** \struct SShapePrimCone
*   \brief Primitive shape that generates a cone mesh
*   \todo Add correct normal and texture coord
*/
struct SShapePrimCone : SShapePrimBase
{
    SShapePrimCone()
    {
        ConeConstruction();
    }

    void ConeConstruction()
    {
        if(iResW < 3)
            iResW = 3;

        vector<SVector> rVertex = {};

        vector<uint32> rIndices = {};

        vector<Texture> rTextures = {};

        GenerateVertexData(rVertex);

        GenerateIndicesData(rIndices);

        rModel.AddMesh(Mesh(rVertex, rIndices, rTextures));
    }

    void GenerateVertexData(vector<SVector>& InrVertexList) override
    {
        uint32 iLoopW = 0;

        const float fRadiansByDivision = DOUBLE_PI_F/static_cast<float>(iResW);

        float fSinDistanceRadius = 0.0f, fCosDistanceRadius = 0.0f;

        InrVertexList.push_back(SVector(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f), vec2(0.0f)));

        while(iLoopW < iResW)
        {
            fSinDistanceRadius = sinf(fRadiansByDivision * static_cast<float>(iLoopW + 1)) * fRadius;
            fCosDistanceRadius = cosf(fRadiansByDivision * static_cast<float>(iLoopW + 1)) * fRadius;

            //Bottom
            InrVertexList.push_back(
                SVector(
                    vec3(fSinDistanceRadius, 0.0f, fCosDistanceRadius),
                    vec3(0.0f),
                    vec2(0.0f)));

            ++iLoopW;
        }

        InrVertexList.push_back(
            SVector(vec3(0.0f, fHeight, 0.0f), vec3(0.0f), vec2(0.0f)));
    }

    void GenerateIndicesData(vector<uint32>& InrIndicesList) override
    {
        uint32 iLoopW = 0;

        while(iLoopW < iResW - 1)
        {
            //Bottom
            InrIndicesList.push_back(0);
            InrIndicesList.push_back(iResW - iLoopW);
            InrIndicesList.push_back(iResW - (iLoopW+1));

            //Top
            InrIndicesList.push_back(iResW + 1);
            InrIndicesList.push_back(iLoopW+1);
            InrIndicesList.push_back(iLoopW+2);

            ++iLoopW;
        }

        //Bottom
        InrIndicesList.push_back(0);
        InrIndicesList.push_back(1);
        InrIndicesList.push_back(iResW);

        //Top
        InrIndicesList.push_back(iResW + 1);
        InrIndicesList.push_back(iResW);
        InrIndicesList.push_back(1);
    }
};


//TODO: Add correct normal and texture coord
/** \struct SShapePrimCylinder
*   \brief Primitive shape that generates a cylinder mesh
*   \todo Add correct normal and texture coord
*/
struct SShapePrimCylinder : SShapePrimBase
{
    SShapePrimCylinder()
    {
        CylinderConstruction();
    }

    void CylinderConstruction()
    {
        if(iResW < 3)
            iResW = 3;

        vector<SVector> rVertex = {};

        vector<uint32> rIndices = {};

        vector<Texture> rTextures = {};

        GenerateVertexData(rVertex);

        GenerateIndicesData(rIndices);

        rModel.AddMesh(Mesh(rVertex, rIndices, rTextures));
    }

    void GenerateVertexData(vector<SVector>& InrVertexList) override
    {   
        uint32 iLoopW = 0;

        const float fRadiansByDivision = DOUBLE_PI_F/static_cast<float>(iResW);

        float fSinDistanceRadius = 0.0f, fCosDistanceRadius = 0.0f;

        InrVertexList.push_back(SVector(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f), vec2(0.0f)));

        while(iLoopW < iResW)
        {
            fSinDistanceRadius = sinf(fRadiansByDivision * static_cast<float>(iLoopW + 1)) * fRadius;
            fCosDistanceRadius = cosf(fRadiansByDivision * static_cast<float>(iLoopW + 1)) * fRadius;

            //Bottom
            InrVertexList.push_back(
                SVector(
                    vec3(fSinDistanceRadius, 0.0f, fCosDistanceRadius),
                    vec3(0.0f), 
                    vec2(0.0f)));

            //Top
            InrVertexList.push_back(
                SVector(
                    vec3(fSinDistanceRadius, fHeight, fCosDistanceRadius),
                    vec3(0.0f),
                    vec2(0.0f)));

            ++iLoopW;
        }

        InrVertexList.push_back(
            SVector(vec3(0.0f, fHeight, 0.0f), vec3(0.0f), vec2(0.0f)));
    }

    void GenerateIndicesData(vector<uint32>& InrIndicesList) override
    {
        uint32 iLoopW = 0;

        uint32 iMaxRound = iResW * 2;

        while(iLoopW < iResW - 1)
        {
            //Bottom
            InrIndicesList.push_back(0);
            InrIndicesList.push_back(iMaxRound + 1 - (2 * (iLoopW+1)));
            InrIndicesList.push_back(iMaxRound + 1 - (2 * (iLoopW+2)));

            //Top
            InrIndicesList.push_back(iMaxRound + 1);
            InrIndicesList.push_back(2 * (iLoopW + 1));
            InrIndicesList.push_back(2 * (iLoopW + 2));

            //Round
            InrIndicesList.push_back(iMaxRound - 1 - (2 * iLoopW));
            InrIndicesList.push_back(iMaxRound - (2 * iLoopW));
            InrIndicesList.push_back(iMaxRound - 2 - (2 * iLoopW));

            InrIndicesList.push_back(iMaxRound - 2 - (2 * iLoopW));
            InrIndicesList.push_back(iMaxRound - 3 - (2 * iLoopW));
            InrIndicesList.push_back(iMaxRound - 1 - (2 * iLoopW));

            ++iLoopW;
        }

        //Bottom
        InrIndicesList.push_back(0);
        InrIndicesList.push_back(1);
        InrIndicesList.push_back(iMaxRound - 1);

        //Top
        InrIndicesList.push_back(iMaxRound + 1);
        InrIndicesList.push_back(iMaxRound);
        InrIndicesList.push_back(2);

        //Round
        InrIndicesList.push_back(1);
        InrIndicesList.push_back(2);
        InrIndicesList.push_back(iMaxRound);

        InrIndicesList.push_back(iMaxRound);
        InrIndicesList.push_back(iMaxRound - 1);
        InrIndicesList.push_back(1);
    }
};