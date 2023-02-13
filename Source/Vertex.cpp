#include "Vertex.h"


Vertex::Vertex() noexcept
{
	VertexData.Position = vec3(0.0f);
	VertexData.Normal = vec3(0.0f);
	VertexData.TexCoords = vec2(0.0f);
}

Vertex::Vertex(const Vertex& InrVertex) noexcept
{
	VertexData.Position = InrVertex.VertexData.Position;
	VertexData.Normal = InrVertex.VertexData.Normal;
	VertexData.TexCoords = InrVertex.VertexData.TexCoords;
}

Vertex::Vertex(const Vertex&& InrVertex) noexcept
{
	VertexData.Position = InrVertex.VertexData.Position;
	VertexData.Normal = InrVertex.VertexData.Normal;
	VertexData.TexCoords = InrVertex.VertexData.TexCoords;
}


void Vertex::Move(Vertex&& InrVertex)
{
	VertexData.Position = InrVertex.VertexData.Position;
	VertexData.Normal = InrVertex.VertexData.Normal;
	VertexData.TexCoords = InrVertex.VertexData.TexCoords;
}

void Vertex::operator=(const Vertex& InrVertex)
{
	VertexData.Position = InrVertex.VertexData.Position;
	VertexData.Normal = InrVertex.VertexData.Normal;
	VertexData.TexCoords = InrVertex.VertexData.TexCoords;
}

float Vertex::GetDotProduct(const vec3& InrVertex)
{
	return VertexData.Position.x * InrVertex.x +
		   VertexData.Position.y * InrVertex.y +
		   VertexData.Position.z * InrVertex.z;
}

vec3 Vertex::GetCrossProduct(const vec3& InrVec)
{
	return vec3(VertexData.Position.y * InrVec.z - VertexData.Position.z * InrVec.y,
				VertexData.Position.x * InrVec.z - VertexData.Position.z * InrVec.x,
				VertexData.Position.x * InrVec.y - VertexData.Position.y * InrVec.x);
}

vec3 Vertex::GetLength(const vec3& InrVertex)
{
	return vec3(abs(abs(VertexData.Position.x) - abs(InrVertex.x)),
		   abs(abs(VertexData.Position.y) - abs(InrVertex.y)),
		   abs(abs(VertexData.Position.z) - abs(InrVertex.z)));
}

float Vertex::GetLength2(const vec3& InrVec)
{
	return abs(abs(VertexData.Position.x) - abs(InrVec.x)) +
		   abs(abs(VertexData.Position.y) - abs(InrVec.y)) +
		   abs(abs(VertexData.Position.z) - abs(InrVec.z));
}

float Vertex::GetDistance(const vec3& InrVec)
{
	return powf(GetLength2(InrVec),2) + 1;
}