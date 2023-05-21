#include "Vector.h"


FVector::FVector() noexcept : 
Position(vec3(0.0f)),
Normal(vec3(0.0f)),
TexCoords(vec2(0.0f)) {}

FVector::FVector(const FVector& InrVertex) noexcept : 
Position(InrVertex.Position),
Normal(InrVertex.Normal),
TexCoords(InrVertex.TexCoords) {}

FVector::FVector(const FVector&& InrVertex) noexcept :
Position(InrVertex.Position),
Normal(InrVertex.Normal),
TexCoords(InrVertex.TexCoords) {}


void FVector::Move(FVector&& InrVertex)
{
	Position = InrVertex.Position;
	Normal = InrVertex.Normal;
	TexCoords = InrVertex.TexCoords;
}

void FVector::operator=(const FVector& InrVertex)
{
	Position = InrVertex.Position;
	Normal = InrVertex.Normal;
	TexCoords = InrVertex.TexCoords;
}

void FVector::operator=(FVector&& InrVertex)
{
	Position = InrVertex.Position;
	Normal = InrVertex.Normal;
	TexCoords = InrVertex.TexCoords;
}