#include "Vector.h"


SVector::SVector() noexcept : 
rPosition(vec3(0.0f)),
rNormal(vec3(0.0f)),
rTexCoords(vec2(0.0f)) {}

SVector::SVector(vec3 const& InrPos, vec3 const& InrNorm, vec2 const& InrTexCoord) noexcept : 
rPosition(InrPos),
rNormal(InrNorm),
rTexCoords(InrTexCoord) {}

SVector::SVector(SVector const& InrVertex) noexcept : 
rPosition(InrVertex.rPosition),
rNormal(InrVertex.rNormal),
rTexCoords(InrVertex.rTexCoords) {}

SVector::SVector(SVector&& InrVertex) noexcept :
rPosition(InrVertex.rPosition),
rNormal(InrVertex.rNormal),
rTexCoords(InrVertex.rTexCoords) {}

SVector SVector::operator=(SVector const& InrVertex) noexcept
{
	rPosition = InrVertex.rPosition;
	rNormal = InrVertex.rNormal;
	rTexCoords = InrVertex.rTexCoords;

	return InrVertex;
}

SVector SVector::operator=(SVector&& InrVertex) noexcept
{
	rPosition = InrVertex.rPosition;
	rNormal = InrVertex.rNormal;
	rTexCoords = InrVertex.rTexCoords;

	return InrVertex;
}