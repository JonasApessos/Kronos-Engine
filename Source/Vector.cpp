#include "Vector.h"


SVector::SVector() noexcept : 
Position(vec3(0.0f)),
Normal(vec3(0.0f)),
TexCoords(vec2(0.0f)) {}

SVector::SVector(vec3 const& InrPos, vec3 const& InrNorm, vec2 const& InrTexCoord) noexcept : 
Position(InrPos),
Normal(InrNorm),
TexCoords(InrTexCoord) {}

SVector::SVector(SVector const& InrVertex) noexcept : 
Position(InrVertex.Position),
Normal(InrVertex.Normal),
TexCoords(InrVertex.TexCoords) {}

SVector::SVector(SVector&& InrVertex) noexcept :
Position(InrVertex.Position),
Normal(InrVertex.Normal),
TexCoords(InrVertex.TexCoords) {}

SVector SVector::operator=(SVector const& InrVertex) noexcept
{
	Position = InrVertex.Position;
	Normal = InrVertex.Normal;
	TexCoords = InrVertex.TexCoords;

	return InrVertex;
}

SVector SVector::operator=(SVector&& InrVertex) noexcept
{
	Position = InrVertex.Position;
	Normal = InrVertex.Normal;
	TexCoords = InrVertex.TexCoords;

	return InrVertex;
}