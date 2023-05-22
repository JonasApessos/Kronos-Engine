#pragma once
#include <glm/glm.hpp>
#include <vector>

using glm::vec2, glm::vec3;

struct FVector
{
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;

	FVector() noexcept;
	FVector(const vec3& InrPos, const vec3& InrNorm, const vec2& InrTexCoord) noexcept;
	FVector(const FVector& InrVertex) noexcept;
	FVector(FVector&& InrVertex) noexcept;

	inline void operator +(const FVector& InrVertex);
	inline void operator +(const vec3& InrVector);
	inline void operator -(const FVector& InrVertex);
	inline void operator -(const vec3& InrVector);
	inline void operator *(const FVector& InrVertex);
	inline void operator *(const vec3& InrVector);
	inline void operator /(const FVector& InrVertex);
	inline void operator /(const vec3& InrVector);
	void operator =(const FVector& InrVertex);
	void operator =(FVector&& InrVertex);

	inline void SetPosition(const vec3& InrPos);
	inline void SetPosition(const float InrPosX, const float InrPosY, const float InrPosZ);

	inline void SetNormal(const vec3& InrNorm);
	inline void SetNormal(const float InrNormX, const float InrNormY, const float InrNormZ);

	inline void SetTexCoord(const vec2& InrTexCoord);
	inline void SetTexCoord(const float InrTexCoordX, const float InrTexCoordY);

	inline vec3 GetPosition() const;
	inline vec3 GetNormal() const;
	inline vec2 SetTexCoord() const;

	inline float GetDotProduct(const vec3& InrVertex) const;
	inline vec3 GetCrossProduct(const vec3& InrVertex) const;
	inline vec3 GetDirection(const vec3& InrVertex) const;
	inline float GetLength(const vec3& InrVec) const;
	inline float GetDistance(const vec3& InrVec) const;
};



inline void FVector::operator+(const FVector& InrVertex) { Position += InrVertex.Position; }
inline void FVector::operator+(const vec3& InrVector) { Position += InrVector; }

inline void FVector::operator-(const FVector& InrVertex) { Position -= InrVertex.Position; }
inline void FVector::operator-(const vec3& InrVector) { Position -= InrVector; }

inline void FVector::operator*(const FVector& InrVertex) { Position *= InrVertex.Position; }
inline void FVector::operator*(const vec3& InrVector) { Position *= InrVector; }

inline void FVector::operator/(const FVector& InrVertex) { Position /= InrVertex.Position; }
inline void FVector::operator/(const vec3& InrVector) { Position /= InrVector; }

inline void FVector::SetPosition(const vec3& InrPos) { Position = InrPos; }
inline void FVector::SetPosition(const float InrPosX, const float InrPosY, const float InrPosZ) { Position.x = InrPosX; Position.y = InrPosY; Position.z = InrPosZ; }

inline void FVector::SetNormal(const vec3& InrNorm) { Normal = InrNorm; }
inline void FVector::SetNormal(const float InrNormX, const float InrNormY, const float InrNormZ) { Normal.x = InrNormX; Normal.y = InrNormY; Normal.z = InrNormZ; }

inline void FVector::SetTexCoord(const vec2& InrTexCoord) { TexCoords = InrTexCoord; }
inline void FVector::SetTexCoord(const float InrTexCoordX, const float InrTexCoordY) { TexCoords.x = InrTexCoordX; TexCoords.y = InrTexCoordY; }

inline vec3 FVector::GetPosition() const { return Position; }
inline vec3 FVector::GetNormal() const { return Normal; }
inline vec2 FVector::SetTexCoord() const { return TexCoords; }

inline float FVector::GetDotProduct(const vec3& InrVertex) const
{
	return Position.x * InrVertex.x +
		   Position.y * InrVertex.y +
		   Position.z * InrVertex.z;
}

inline vec3 FVector::GetCrossProduct(const vec3& InrVec) const
{
	return vec3(Position.y * InrVec.z - Position.z * InrVec.y,
				Position.x * InrVec.z - Position.z * InrVec.x,
				Position.x * InrVec.y - Position.y * InrVec.x);
}

inline vec3 FVector::GetDirection(const vec3& InrVertex) const
{
	return vec3(abs(abs(Position.x) - abs(InrVertex.x)),
		   abs(abs(Position.y) - abs(InrVertex.y)),
		   abs(abs(Position.z) - abs(InrVertex.z)));
}

inline float FVector::GetLength(const vec3& InrVec) const
{
	return abs(abs(Position.x) - abs(InrVec.x)) +
		   abs(abs(Position.y) - abs(InrVec.y)) +
		   abs(abs(Position.z) - abs(InrVec.z));
}

inline float FVector::GetDistance(const vec3& InrVec) const { return powf(GetLength(InrVec),2) + 1; }
