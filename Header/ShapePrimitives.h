#pragma once

#include <assert.h>

#include "MacroUtils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Log.h"
#include "Utils.h"
#include "Primitives.h"
#include "Model.h"
#include "Math.h"

using glm::vec3, glm::mat4;
using KronosPrim::uint32;

/** @struct SShapePrimBase
*   @brief abstract structure to inherit from
*   @todo Complete docs for doxygen
*/
struct SShapePrimBase
{
    //Doxygen
    /*! @var uint32 iResW
	*	@brief Width Resolution that shapes will use to generate Vertices/Indices.
	*
	*	@var uint32 iResH
	*	@brief Height Resolution that shapes will use to generate Vertices/Indices.
    *
    *   @var float fRadius
	*	@brief Radius of object (can be used for scaling ex. Cube).
    * 
    *   @var float fHeight
	*	@brief Height of Shape (Can be used to non-uniform scale for height).
    *
    *   @var vector<SVector> rVertices
	*	@brief Height of Shape (Can be used to non-uniform scale for height).
    *
    *   @var vector<uint32> rIndices
	*	@brief Height of Shape (Can be used to non-uniform scale for height).
    *
    *   @var Model rModel
	*	@brief Model object that will encapsulate the mesh data.
    *   
    *   @fn SetResW
    *   @brief Set width resolution of shape, if used by shape.
    * 
    *   @fn SetResH
    *   @brief Set height resolution of shape, if used by shape.
    * 
    *   @fn SetRes
    *   @brief Set resolution of shape, if used by shape.
    * 
    *   @fn SetRadius
    *   @brief Set radius of shape, if used by shape.
    * 
    *   @fn SetHeight
    *   @brief Set Height of shape, if used by shape.
    * 
    *   @fn GetResW
    *   @brief get width resolution of shape, if used by shape.
    * 
    *   @fn GetResH
    *   @brief get height resolution of shape, if used by shape.
    * 
    *   @fn GetRadius
    *   @brief get radius of shape, if used by shape.
    * 
    *   @fn GetHeight
    *   @brief get Height of shape, if used by shape.
    * 
    *   @fn GetModel
    *   @brief get model with the generated mesh.
    * 
    *   @fn Translate
    *   @brief Translate shape.
    * 
    *   @fn Rotate
    *   @brief Rotate shape.
    * 
    *   @fn Scale
    *   @brief Translate shape.
    * 
    *   @fn GenerateVertexData
    *   @brief overridable function to generate specific shape.
    * 
    *   @fn GenerateIndicesData
    *   @brief overridable function to generate specific Indices of shape.
    * */

    //Resolution that shapes will use to generate Vertices/Indices
    uint32 iResW = 8, iResH = 8;

    //Radius of shape (can be used for scaling ex. Cube)
    float fRadius = 1.0f;

    //Height of Shape (Can be used to non-uniform scale for height)
    float fHeight = 1.0f;

    //Vertices for the primitive
    vector<SVector> rVertices;

    //Indices for drawing order of primitives
    vector<uint32> rIndices;

    //Model object that will encapsulate the mesh data
    Model rModel;

    Log rLog;

    //Set width resolution of shape, if used by shape
    inline void SetResW(uint32 IniResW) noexcept;
    //Set height resolution of shape, if used by shape
    inline void SetResH(uint32 IniResH) noexcept;
    //Set resolution of shape, if used by shape
    inline void SetRes(uint32 IniResW, uint32 IniResH) noexcept;

    //Set the Radius of the shape
    inline void SetRadius(float InfRadius);
    //Set Height if shape
    inline void SetHeight(float InfHeight);

    //Get width resolution of shape
    inline uint32 GetResW() const;
    //Get height resolution of shape
    inline uint32 GetResH() const;

    //Get radius of shape
    inline float GetRadius() const;
    //Get Height of shape
    inline float GetHeight() const;

    //Get generated mesh
    virtual inline Mesh GetMesh();

    //Get model with the generated mesh
    virtual inline Model GetModel() const;

    //Translate shape.
    virtual inline void Translate(vec3 const& InrTranslate);
    //Rotate shape.
    virtual inline void Rotate(float fDegrees, vec3 const& InrRotate);
    //Scale
    virtual inline void Scale(vec3 const& InrScale);

    //Overridable function to generate specific shape.
    virtual void GenerateVertexData() = 0;
    //Overridable function to generate specific Indices of shape.
    virtual void GenerateIndicesData() = 0;
};

inline void SShapePrimBase::SetResW(uint32 IniResW) noexcept { iResW = IniResW; }
inline void SShapePrimBase::SetResH(uint32 IniResH) noexcept { iResH = IniResH; }
inline void SShapePrimBase::SetRes(uint32 IniResW, uint32 IniResH) noexcept { iResW = IniResW; iResH = IniResH; }

inline void SShapePrimBase::SetRadius(float InfRadius) { fRadius = InfRadius; }
inline void SShapePrimBase::SetHeight(float InfHeight) { fHeight = InfHeight; }

inline uint32 SShapePrimBase::GetResW() const { return iResW; }
inline uint32 SShapePrimBase::GetResH() const { return iResH; }

inline float SShapePrimBase::GetRadius() const { return fRadius; }
inline float SShapePrimBase::GetHeight() const { return fHeight; }

inline void SShapePrimBase::Translate(vec3 const& InrTranslate) { rModel.Translate(InrTranslate); }
inline void SShapePrimBase::Rotate(float fDegrees, vec3 const& InrRotate) { rModel.Rotate(fDegrees, InrRotate); }
inline void SShapePrimBase::Scale(vec3 const& InrScale) { rModel.Scale(InrScale); }

inline Model SShapePrimBase::GetModel() const { return rModel; }
inline Mesh SShapePrimBase::GetMesh() { return Mesh(rVertices, rIndices); }

/** @struct SShapePrimLine
*   @brief Primitive shape that generates a Line mesh
*   @todo Add correct normal and texture coord
*/
struct SShapePrimLine : SShapePrimBase
{
    SShapePrimLine() { LineConstruction(); }

    SShapePrimLine(float InfRadius) 
    { 
        SetRadius(InfRadius);

        LineConstruction(); 
    }

    void LineConstruction()
    {
        rLog.SetLogName("LinePrimGenerator");

        GenerateVertexData();
        GenerateIndicesData();

        rModel.AddMesh(Mesh(rVertices, rIndices));

        vector<Mesh> rMeshList = rModel.GetMeshList();

        rMeshList[0].SetDrawMode(EGLDrawMode::EGLDM_LineStrip);

        rModel.SetMeshList(rMeshList);
    }

    void GenerateVertexData() override
    {
        rLog.WriteAndDisplay("Constructing Vertices...");

        rVertices = {
            SVector(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)),
            SVector(vec3(1.0f, 0.0f, 0.0f * fRadius), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f))
        };

        rLog.WriteAndDisplay("Vertices: " + to_string(rVertices.size()));
    }

    void GenerateIndicesData() override
    {
        rLog.WriteAndDisplay("Constructing Indices...");

        rIndices = {
            0,1
        };

        rLog.WriteAndDisplay("Indices: " + to_string(rIndices.size()));
    }
};

/** @struct SShapePrimCircle
*   @brief Primitive shape that generates a Line mesh
*   @todo Add correct normal and texture coord
*/
struct SShapePrimCircle : SShapePrimBase
{
    SShapePrimCircle() { CyrcleConstruction(); }

    SShapePrimCircle(uint32 IniResW, float InfRadius) 
    { 
        SetResW(IniResW);
        SetRadius(InfRadius);

        CyrcleConstruction(); 
    }

    void CyrcleConstruction()
    {
        rLog.SetLogName("CirclePrimGenerator");

        GenerateVertexData();
        GenerateIndicesData();

        rModel.AddMesh(Mesh(rVertices, rIndices));

        vector<Mesh> rMeshList = rModel.GetMeshList();

        rMeshList[0].SetDrawMode(EGLDrawMode::EGLDM_LineLoop);

        rModel.SetMeshList(rMeshList);
    }

    void GenerateVertexData() override
    {
        rLog.WriteAndDisplay("Constructing Vertices...");

        uint32 iLoopW = 0;

        float fSinDistanceRadius = 0.f, fCosDistanceRadius = 0.f;

        float fRadByDiv = DOUBLE_PI_F/static_cast<float>(iResW);

        rVertices.reserve(iResW);

        while(iLoopW < iResW)
        {
            fSinDistanceRadius = sinf(fRadByDiv * static_cast<float>(iLoopW + 1)) * fRadius;
            fCosDistanceRadius = cosf(fRadByDiv * static_cast<float>(iLoopW + 1)) * fRadius;

            //Bottom
            rVertices.emplace_back(
                SVector(
                    vec3(fSinDistanceRadius, 0.0f, fCosDistanceRadius),
                    vec3(0.0f),
                    vec2(0.0f)));

            ++iLoopW;
        }

        rLog.WriteAndDisplay("Vertices: " + to_string(rVertices.size()));
    }

    void GenerateIndicesData() override
    {
        rLog.WriteAndDisplay("Constructing Indices...");

        uint32 iLoopW = 0;

        rIndices.reserve(iResW);

        while(iLoopW < iResW)
        {
            rIndices.emplace_back(iLoopW);                

            ++iLoopW;
        }

        rLog.WriteAndDisplay("Indices: " + to_string(rIndices.size()));
    }
};

/** @struct SShapePrimPlane
*   @brief Primitive shape that generates a plane mesh
*   @todo Add correct normal and texture coord
*/
struct SShapePrimPlane : SShapePrimBase
{
    SShapePrimPlane() { PlaneConstruction(); }

    SShapePrimPlane(float InfRadius) 
    { 
        SetRadius(InfRadius);

        PlaneConstruction(); 
    }

    void PlaneConstruction()
    {
        rLog.SetLogName("PlanePrimGenerator");

        GenerateVertexData();
        GenerateIndicesData();

        rModel.AddMesh(Mesh(rVertices, rIndices));

        vector<Mesh> rMeshList = rModel.GetMeshList();

        rMeshList[0].SetDrawMode(EGLDrawMode::EGLDM_TriangleStrip);

        rModel.SetMeshList(rMeshList);
    }

    void GenerateVertexData() override
    {
        rLog.WriteAndDisplay("Constructing Vertices...");

        rVertices = {
            SVector(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)),
            SVector(vec3(0.0f, 0.0f, 1.0f * fRadius), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)),
            SVector(vec3(1.0f * fRadius, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)),
            SVector(vec3(1.0f * fRadius, 0.0f, 1.0f * fRadius), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f))
        };

        rLog.WriteAndDisplay("Vertices: " + to_string(rVertices.size()));
    }

    void GenerateIndicesData() override
    {
        rLog.WriteAndDisplay("Constructing Indices...");

        rIndices = {
            0,1,2,3
        };

        rLog.WriteAndDisplay("Indices: " + to_string(rIndices.size()));
    }
};

//TODO: Add correct normal and texture coord
/** @struct SShapePrimCube
*   @brief Primitive shape that generates a cube mesh
*   @todo Add correct normal and texture coord
*/
struct SShapePrimCube : SShapePrimBase
{
    SShapePrimCube() { BoxConstruction(); }

    SShapePrimCube(float InfRadius, float InfHeight)
    { 
        SetRadius(InfRadius);
        SetHeight(InfHeight);

        BoxConstruction();
    }

    void BoxConstruction()
    {
        rLog.SetLogName("CubePrimGenerator");

        rLog.WriteAndDisplay("Generating Cube...");

        GenerateVertexData();
        GenerateIndicesData();

        rModel.AddMesh(Mesh(rVertices, rIndices));

        vector<Mesh> rMeshList = rModel.GetMeshList();

        rMeshList[0].SetDrawMode(EGLDrawMode::EGLDM_TriangleStrip);

        rModel.SetMeshList(rMeshList);

        rLog.WriteAndDisplay("Generating Done...");
    }

    void GenerateVertexData() override
    {
        rLog.WriteAndDisplay("Constructing Vertices...");

        rVertices = {
            SVector(vec3(0.0f, 0.0f, 0.0f), vec3(-1.0f, -1.0f, 1.0f), vec2(0.0f, 0.0f)),
            SVector(vec3(0.0f, fHeight, 0.0f), vec3(-1.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f)),
            SVector(vec3(fRadius, 0.0f, 0.0f), vec3(1.0f, -1.0f, 1.0f), vec2(0.0f, 1.0f)),
            SVector(vec3(fRadius, fHeight, 0.0f), vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)),
            SVector(vec3(fRadius, 0.0f, fRadius), vec3(1.0f, -1.0f, -1.0f), vec2(0.0f, 0.0f)),
            SVector(vec3(fRadius, fHeight, fRadius), vec3(1.0f, 1.0f, -1.0f), vec2(1.0f, 0.0f)),
            SVector(vec3(0.0f, 0.0f, fRadius), vec3(-1.0f, -1.0f, -1.0f), vec2(0.0f, 1.0f)),
            SVector(vec3(0.0f, fHeight, fRadius), vec3(-1.0f, 1.0f, -1.0f), vec2(1.0f, 1.0f))
        };
        
        rLog.WriteAndDisplay("Vertices: " + to_string(rVertices.size()));
    }

    void GenerateIndicesData() override
    {
        rLog.WriteAndDisplay("Constructing Indices...");

        rIndices = {
            1,7,3,5,
            5,4,3,2,
            3,2,1,0,
            1,0,7,6,
            7,6,5,4,
            2,4,0,6
        };

        rLog.WriteAndDisplay("Indices: " + to_string(rVertices.size()));
    }
};

//TODO: Add correct normal and texture coord
/** @struct SShapePrimSphere
*   @brief Primitive shape that generates a sphere mesh
*   @todo Add correct normal and texture coord
*/
struct SShapePrimSphere : SShapePrimBase
{
    SShapePrimSphere() { SetRes(32, 16); SphereConsruction(); }

    SShapePrimSphere(uint32 IniResW, uint32 IniResH, float InfRadius, float InfHeight)
    {
        SetRes(IniResW, IniResH);

        SetRadius(InfRadius);
        SetHeight(InfHeight);

        SphereConsruction(); 
    }

    void SphereConsruction()
    {
        rLog.SetLogName("SpherePrimGenerator");

        if(iResW < 3)
            iResW = 3;

        if(iResH < 3)
            iResH = 3;

        rLog.WriteAndDisplay("Generating Sphere...");

        GenerateVertexData();
        GenerateIndicesData();

        rModel.AddMesh(Mesh(rVertices, rIndices));

        rLog.WriteAndDisplay("Generating Done...");
    }

    void GenerateVertexData() override
    {
        rLog.WriteAndDisplay("Constructing Vertices...");

        uint32 iLoopW = 0, iLoopH = 1;

        //reserve before operation to avoid memory reservetion with every new element
        rVertices.reserve(GetResW() * (GetResH()-1) + 2);

        const float fFullRad = DOUBLE_PI_F/static_cast<float>(iResW);
        const float fHalfRad = PI_F/static_cast<float>(iResH);
        const float fQuarterRad = HALF_PI_F/static_cast<float>(iResH);

        float fSinDistanceRadius = 0.0f, fCosDistanceRadius = 0.0f, fCurbe = 0.0f;

        rVertices.emplace_back(SVector(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f), vec2(0.0f)));

        while(iLoopW < iResW)
        {
            fSinDistanceRadius = sinf(fFullRad * static_cast<float>(iLoopW));
            fCosDistanceRadius = cosf(fFullRad * static_cast<float>(iLoopW));

            while(iLoopH + 1 < iResH + 1)
            {
                fCurbe = sinf(fHalfRad * static_cast<float>(iLoopH));

                rVertices.emplace_back(
                    SVector(
                    vec3(fCosDistanceRadius * fCurbe * fRadius,
                    SquarePow(sinf(fQuarterRad * static_cast<float>(iLoopH))) * fRadius * fHeight * 2.f,
                    fSinDistanceRadius * fCurbe * fRadius),
                    vec3(0.0f),
                    vec2(0.0f)));

                ++iLoopH;
            }

            ++iLoopW;

            iLoopH = 1;
        }

        rVertices.emplace_back(SVector(vec3(0.0f, fRadius*fHeight*2.f, 0.0f), vec3(0.0f), vec2(0.0f)));

        rLog.WriteAndDisplay("Vertices: " + to_string(rVertices.size()));
        assert("Number of generated vertices does not correspond what was reserved" && !((GetResW() * (GetResH()-1) + 2) != rVertices.size()));

    }

    void GenerateIndicesData() override
    {
        rLog.WriteAndDisplay("Constructing Indices...");

        uint32 iLoopW = 0;
        uint32 iLoopH = 0;

        uint32 iCurIndice = 1;

        uint32 iVertexNum = static_cast<uint32>(rVertices.size());
        
        //reserve before operation to avoid memory reservetion with every new element
        rIndices.reserve((GetResW() * (GetResH()-1))*6);

        //Loop throught the width of the sphere
        while(iLoopW < iResW - 1)
        {
            
            //Bottom fan Indices
            rIndices.emplace_back(0);
            rIndices.emplace_back(1 + (iLoopW * (iResH-1)));
            rIndices.emplace_back(1 + ((iLoopW + 1) * (iResH-1)));

            //Loop throught the height of the sphere at the specific point of the width
            while(iLoopH < iResH - 2)
            {
                //Height indices travel
                rIndices.emplace_back(iCurIndice);
                rIndices.emplace_back(iCurIndice+1);
                rIndices.emplace_back(iCurIndice+iResH);

                rIndices.emplace_back(iCurIndice+iResH);
                rIndices.emplace_back(iCurIndice+iResH-1);
                rIndices.emplace_back(iCurIndice);

                ++iLoopH;
                ++iCurIndice;
            }            

            //Top fan Indices
            rIndices.emplace_back(iVertexNum-1);
            rIndices.emplace_back(iVertexNum - 2 - (iResH-1) * iLoopW);
            rIndices.emplace_back(iVertexNum - 2 - (iResH-1) * (iLoopW+1));

            iLoopH = 0;

            ++iLoopW;

            iCurIndice = 1 + iLoopW * (iResH-1);
        }

        //Looping around heigth indices
        iLoopW = 0;
        iCurIndice = 1 + (iResH-1) * (iResW-1);

        while(iLoopW < iResH-2)
        {
            rIndices.emplace_back(iCurIndice);
            rIndices.emplace_back(iCurIndice + 1);
            rIndices.emplace_back(1 + 1 * (iLoopW+1));
            rIndices.emplace_back(1 + 1 * (iLoopW+1));
            rIndices.emplace_back((iLoopW+1));
            rIndices.emplace_back(iCurIndice);
            
            ++iLoopW;
            ++iCurIndice;
        }

        //Looping around bottom fan indices 
        rIndices.emplace_back(0);
        rIndices.emplace_back(1 + (iResW-1)*(iResH-1));
        rIndices.emplace_back(1);
        
        //Looping around Top fan indices
        rIndices.emplace_back(iVertexNum-1);
        rIndices.emplace_back(iResH-1);
        rIndices.emplace_back(iVertexNum-2);

        rLog.WriteAndDisplay("Indices: " + to_string(rIndices.size()));
        assert("Number of generated indices does not correspond what was reserved" && !(((GetResW() * (GetResH()-1))*6) != rIndices.size()));
    }
};

//TODO: Add correct normal and texture coord
/** @struct SShapePrimCone
*   @brief Primitive shape that generates a cone mesh
*   @todo Add correct normal and texture coord
*/
struct SShapePrimCone : SShapePrimBase
{
    SShapePrimCone() { ConeConstruction(); }

    SShapePrimCone(uint32 IniResW, float InfRadius, float InfHeight) 
    { 
        SetResW(IniResW);

        SetRadius(InfRadius);
        SetHeight(InfHeight);

        ConeConstruction();
    }

    void ConeConstruction()
    {
        if(iResW < 3)
            iResW = 3;

        rLog.WriteAndDisplay("Generating Cone...");

        GenerateVertexData();
        GenerateIndicesData();

        rModel.AddMesh(Mesh(rVertices, rIndices));

        rLog.WriteAndDisplay("Generating Done...");
    }

    void GenerateVertexData() override
    {
        rLog.WriteAndDisplay("Constructing Vertices...");

        uint32 iLoopW = 0;

        const float fRadByDiv = DOUBLE_PI_F/static_cast<float>(iResW);

        float fSinDistanceRadius = 0.0f, fCosDistanceRadius = 0.0f;

        //reserve before operation to avoid memory reservetion with every new element
        rVertices.reserve(iResW + 2);

        rVertices.emplace_back(SVector(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f), vec2(0.0f)));

        while(iLoopW < iResW)
        {
            fSinDistanceRadius = sinf(fRadByDiv * static_cast<float>(iLoopW + 1)) * fRadius;
            fCosDistanceRadius = cosf(fRadByDiv * static_cast<float>(iLoopW + 1)) * fRadius;

            //Bottom
            rVertices.emplace_back(
                SVector(
                    vec3(fSinDistanceRadius, 0.0f, fCosDistanceRadius),
                    vec3(0.0f),
                    vec2(0.0f)));

            ++iLoopW;
        }

        rVertices.emplace_back(
            SVector(vec3(0.0f, fHeight, 0.0f), vec3(0.0f), vec2(0.0f)));

        rLog.WriteAndDisplay("Vertices: " + to_string(rVertices.size()));
        assert("Number of generated vertices does not correspond what was reserved" && !((iResW + 2) != rVertices.size()));

    }

    void GenerateIndicesData() override
    {
        rLog.WriteAndDisplay("Constructing Indices...");

        uint32 iLoopW = 0;

        //reserve before operation to avoid memory reservetion with every new element
        rIndices.reserve(iResW * 6);

        while(iLoopW < iResW - 1)
        {
            //Bottom
            rIndices.emplace_back(0);
            rIndices.emplace_back(iResW - iLoopW);
            rIndices.emplace_back(iResW - (iLoopW+1));

            //Top
            rIndices.emplace_back(iResW + 1);
            rIndices.emplace_back(iLoopW+1);
            rIndices.emplace_back(iLoopW+2);

            ++iLoopW;
        }

        //Bottom
        rIndices.emplace_back(0);
        rIndices.emplace_back(1);
        rIndices.emplace_back(iResW);

        //Top
        rIndices.emplace_back(iResW + 1);
        rIndices.emplace_back(iResW);
        rIndices.emplace_back(1);

        rLog.WriteAndDisplay("Indices: " + to_string(rIndices.size()));
        assert("Number of generated indices does not correspond what was reserved" && !((iResW * 6) != rIndices.size()));
    }
};


//TODO: Add correct normal and texture coord
/** @struct SShapePrimCylinder
*   @brief Primitive shape that generates a cylinder mesh
*   @todo Add correct normal and texture coord
*/
struct SShapePrimCylinder : SShapePrimBase
{
    SShapePrimCylinder() { CylinderConstruction(); }

    SShapePrimCylinder(uint32 IniResW, float InfRadius, float InfHeight)
    {
        SetResW(IniResW);

        SetRadius(InfRadius);
        SetHeight(InfHeight);

        CylinderConstruction();
    }

    void CylinderConstruction()
    {
        rLog.SetLogName("CylinderPrimGenerator");

        if(iResW < 3)
            iResW = 3;

        rLog.WriteAndDisplay("Generating Cylinder...");

        GenerateVertexData();
        GenerateIndicesData();

        rModel.AddMesh(Mesh(rVertices, rIndices));

        rLog.WriteAndDisplay("Generating Done...");
    }

    void GenerateVertexData() override
    {   
        rLog.WriteAndDisplay("Constructing Vertices...");

        uint32 iLoopW = 0;

        const float fRadByDiv = DOUBLE_PI_F/static_cast<float>(iResW);

        float fSinDistanceRadius = 0.0f, fCosDistanceRadius = 0.0f;

        //reserve before operation to avoid memory reservetion with every new element
        rVertices.reserve(iResW * 2 + 2);

        rVertices.push_back(SVector(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f), vec2(0.0f)));

        while(iLoopW < iResW)
        {
            fSinDistanceRadius = sinf(fRadByDiv * static_cast<float>(iLoopW + 1)) * fRadius;
            fCosDistanceRadius = cosf(fRadByDiv * static_cast<float>(iLoopW + 1)) * fRadius;

            //Bottom
            rVertices.emplace_back(
                SVector(
                    vec3(fSinDistanceRadius, 0.0f, fCosDistanceRadius),
                    vec3(0.0f), 
                    vec2(0.0f)));

            //Top
            rVertices.emplace_back(
                SVector(
                    vec3(fSinDistanceRadius, fHeight, fCosDistanceRadius),
                    vec3(0.0f),
                    vec2(0.0f)));

            ++iLoopW;
        }

        rVertices.emplace_back(
            SVector(vec3(0.0f, fHeight, 0.0f), vec3(0.0f), vec2(0.0f)));

        rLog.WriteAndDisplay("Vertices: " + to_string(rVertices.size()));
        assert("Number of generated vertices does not correspond what was reserved" && !((iResW * 2 + 2) != rVertices.size()));
    }

    void GenerateIndicesData() override
    {
        rLog.WriteAndDisplay("Constructing indices...");

        uint32 iLoopW = 0;

        uint32 iMaxRound = iResW * 2;

        //reserve before operation to avoid memory reservetion with every new element
        rIndices.reserve(iResW*12);

        while(iLoopW < iResW - 1)
        {
            //Bottom
            rIndices.emplace_back(0);
            rIndices.emplace_back(iMaxRound + 1 - (2 * (iLoopW+1)));
            rIndices.emplace_back(iMaxRound + 1 - (2 * (iLoopW+2)));

            //Top
            rIndices.emplace_back(iMaxRound + 1);
            rIndices.emplace_back(2 * (iLoopW + 1));
            rIndices.emplace_back(2 * (iLoopW + 2));

            //Round
            rIndices.emplace_back(iMaxRound - 1 - (2 * iLoopW));
            rIndices.emplace_back(iMaxRound - (2 * iLoopW));
            rIndices.emplace_back(iMaxRound - 2 - (2 * iLoopW));

            rIndices.emplace_back(iMaxRound - 2 - (2 * iLoopW));
            rIndices.emplace_back(iMaxRound - 3 - (2 * iLoopW));
            rIndices.emplace_back(iMaxRound - 1 - (2 * iLoopW));

            ++iLoopW;
        }

        //Bottom
        rIndices.emplace_back(0);
        rIndices.emplace_back(1);
        rIndices.emplace_back(iMaxRound - 1);

        //Top
        rIndices.emplace_back(iMaxRound + 1);
        rIndices.emplace_back(iMaxRound);
        rIndices.emplace_back(2);

        //Round
        rIndices.emplace_back(1);
        rIndices.emplace_back(2);
        rIndices.emplace_back(iMaxRound);

        rIndices.emplace_back(iMaxRound);
        rIndices.emplace_back(iMaxRound - 1);
        rIndices.emplace_back(1);

        rLog.WriteAndDisplay("Indices: " + to_string(rIndices.size()));
        assert("Number of generated indices does not correspond what was reserved" && !((iResW*12) != rIndices.size()));
    }
};