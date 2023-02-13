#pragma once
#include <glm/glm.hpp>
#include <vector>

using glm::vec2, glm::vec3;

struct FVertex
{
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
};

class Vertex
{
public:
	FVertex VertexData;

	Vertex() noexcept;
	Vertex(const Vertex& InrVertex) noexcept;
	Vertex(const Vertex&& InrVertex) noexcept;

	virtual void Move(Vertex&& InrVertex);

	inline virtual void operator +(const Vertex& InrVertex);
	inline virtual void operator +(const vec3& InrVector);
	inline virtual void operator -(const Vertex& InrVertex);
	inline virtual void operator -(const vec3& InrVector);
	inline virtual void operator *(const Vertex& InrVertex);
	inline virtual void operator *(const vec3& InrVector);
	inline virtual void operator /(const Vertex& InrVertex);
	inline virtual void operator /(const vec3& InrVector);
	virtual void operator =(const Vertex& InrVertex);

	float GetDotProduct(const vec3& InrVertex);
	vec3 GetCrossProduct(const vec3& InrVertex);
	vec3 GetLength(const vec3& InrVertex);
	float GetLength2(const vec3& InrVec);
	float GetDistance(const vec3& InrVec);


};



inline void Vertex::operator+(const Vertex& InrVertex) { VertexData.Position += InrVertex.VertexData.Position; }
inline void Vertex::operator+(const vec3& InrVector) { VertexData.Position += InrVector; }

inline void Vertex::operator-(const Vertex& InrVertex) { VertexData.Position -= InrVertex.VertexData.Position; }
inline void Vertex::operator-(const vec3& InrVector) { VertexData.Position -= InrVector; }

inline void Vertex::operator*(const Vertex& InrVertex) { VertexData.Position *= InrVertex.VertexData.Position; }
inline void Vertex::operator*(const vec3& InrVector) { VertexData.Position *= InrVector; }

inline void Vertex::operator/(const Vertex& InrVertex) { VertexData.Position /= InrVertex.VertexData.Position; }
inline void Vertex::operator/(const vec3& InrVector) { VertexData.Position /= InrVector; }
