#pragma once

#include <glm/glm.hpp>

#include <vector>

#include "math.h"

using glm::vec2, glm::vec3;

/** \struct SVector
*   \brief Vector structure*/
struct SVector
{
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;

	SVector() noexcept;
	SVector(vec3 const& InrPos, vec3 const& InrNorm, vec2 const& InrTexCoord) noexcept;
	SVector(SVector const& InrVertex) noexcept;
	SVector(SVector&& InrVertex) noexcept;

	inline SVector operator +(SVector const& InrVertex) noexcept;
	inline void operator +(vec3 const& InrVector) noexcept;
	inline SVector operator -(SVector const& InrVertex) noexcept;
	inline void operator -(vec3 const& InrVector) noexcept;
	inline SVector operator *(SVector const& InrVertex) noexcept;
	inline void operator *(vec3 const& InrVector) noexcept;
	inline SVector operator /(SVector const& InrVertex);
	inline void operator /(vec3 const& InrVector);
	SVector operator =(SVector const& InrVertex) noexcept;
	SVector operator =(SVector&& InrVertex) noexcept;

	inline void SetPosition(vec3 const& InrPos) noexcept;
	inline void SetPosition(float const InrPosX, float const InrPosY, float const InrPosZ) noexcept;

	inline void SetNormal(vec3 const& InrNorm) noexcept;
	inline void SetNormal(float const InrNormX, float const InrNormY, float const InrNormZ) noexcept;

	inline void SetTexCoord(vec2 const& InrTexCoord) noexcept;
	inline void SetTexCoord(float const InrTexCoordX, float const InrTexCoordY) noexcept;

	constexpr inline vec3 GetPosition() const noexcept;
	constexpr inline vec3 GetNormal() const noexcept;
	constexpr inline vec2 SetTexCoord() const noexcept;

	constexpr inline float GetDotProduct(vec3 const& InrVertex) const noexcept;
	constexpr inline vec3 GetCrossProduct(vec3 const& InrVertex) const noexcept;
	constexpr inline vec3 GetDirection(vec3 const& InrVertex) const noexcept;
	constexpr inline float GetLength(vec3 const& InrVec) const noexcept;
	constexpr inline float GetDistance(vec3 const& InrVec) const noexcept;
};



inline SVector SVector::operator+(SVector const& InrVertex) noexcept { Position += InrVertex.Position; return InrVertex; }
inline void SVector::operator+(vec3 const& InrVector) noexcept { Position += InrVector; }

inline SVector SVector::operator-(SVector const& InrVertex) noexcept { Position -= InrVertex.Position; return InrVertex; }
inline void SVector::operator-(vec3 const& InrVector) noexcept { Position -= InrVector; }

inline SVector SVector::operator*(SVector const& InrVertex) noexcept { Position *= InrVertex.Position; return InrVertex; }
inline void SVector::operator*(vec3 const& InrVector) noexcept { Position *= InrVector;}

inline SVector SVector::operator/(SVector const& InrVertex) { Position /= InrVertex.Position; return InrVertex; }
inline void SVector::operator/(vec3 const& InrVector) { Position /= InrVector; }

inline void SVector::SetPosition(vec3 const& InrPos) noexcept { Position = InrPos; }
inline void SVector::SetPosition(float const InrPosX, float const InrPosY, float const InrPosZ) noexcept { Position.x = InrPosX; Position.y = InrPosY; Position.z = InrPosZ; }

inline void SVector::SetNormal(vec3 const& InrNorm) noexcept { Normal = InrNorm; }
inline void SVector::SetNormal(float const InrNormX, float const InrNormY, float const InrNormZ) noexcept { Normal.x = InrNormX; Normal.y = InrNormY; Normal.z = InrNormZ; }

inline void SVector::SetTexCoord(vec2 const& InrTexCoord) noexcept { TexCoords = InrTexCoord; }
inline void SVector::SetTexCoord(float const InrTexCoordX, float const InrTexCoordY) noexcept { TexCoords.x = InrTexCoordX; TexCoords.y = InrTexCoordY; }

constexpr inline vec3 SVector::GetPosition() const noexcept { return Position; }
constexpr inline vec3 SVector::GetNormal() const noexcept { return Normal; }
constexpr inline vec2 SVector::SetTexCoord() const noexcept { return TexCoords; }

constexpr inline float SVector::GetDotProduct(vec3 const& InrVertex) const  noexcept
{
	return Position.x * InrVertex.x +
		   Position.y * InrVertex.y +
		   Position.z * InrVertex.z;
}

constexpr inline vec3 SVector::GetCrossProduct(vec3 const& InrVec) const noexcept
{
	return vec3(Position.y * InrVec.z - Position.z * InrVec.y,
				Position.x * InrVec.z - Position.z * InrVec.x,
				Position.x * InrVec.y - Position.y * InrVec.x);
}

constexpr inline vec3 SVector::GetDirection(vec3 const& InrVertex) const noexcept
{
	return vec3(abs(abs(Position.x) - abs(InrVertex.x)),
		   abs(abs(Position.y) - abs(InrVertex.y)),
		   abs(abs(Position.z) - abs(InrVertex.z)));
}

constexpr inline float SVector::GetLength(vec3 const& InrVec) const noexcept
{
	return abs(abs(Position.x) - abs(InrVec.x)) +
		   abs(abs(Position.y) - abs(InrVec.y)) +
		   abs(abs(Position.z) - abs(InrVec.z));
}

constexpr inline float SVector::GetDistance(vec3 const& InrVec) const noexcept { return powf(GetLength(InrVec),2) + 1; }