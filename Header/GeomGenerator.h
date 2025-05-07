#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "Primitives.h"
#include "Vector.h"

using std::vector, std::string;
using glm::vec3;
using KronosPrim::uint32;

//TODO add a equation translator to the generator with a custom number of vertex and generate geometry with it
/** @class GeomGenerator
*   @brief Geometry Generator handles the generation of geometry
*   @details Generate geometry using vertices, 
*    the data generated can be parsed in a mesh class or combine it with other specialized classes in order to generate interesting shapes
*   @todo add a equation translator to the generator with a custom number of vertex and generate geometry with it
*/
class GeomGenerator
{
public:
    uint32 iVertexNum = 8;

    GeomGenerator();
    GeomGenerator(uint32 IniVertexNum, uint32 IniHorizontalSub, uint32 IniVerticalSub);
    GeomGenerator(GeomGenerator const& InrGeomGenerator);
    GeomGenerator(GeomGenerator&& InrGeomGenerator);

    GeomGenerator operator=(GeomGenerator const& InrGeomGenerator);
    GeomGenerator operator=(GeomGenerator&& InrGeomGenerator);

    ~GeomGenerator();

    constexpr inline void SetVertexNum(uint32 IniVertexNum);

    void SetVertexPosition(vec3 const& InrVector);
    void SetVertexPosition(vector<vec3> const& InrVectorList);

    void TranslateEquation(string const& InrEquation);

protected:
    vec3 rLastPosition = vec3(0.0f);

    vector<SVector> rVectorList;

    void VertexLoop();
private:
    void Init();
};

constexpr inline void GeomGenerator::SetVertexNum(uint32 IniVertexNum) { iVertexNum = IniVertexNum; }