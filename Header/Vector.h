#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "math.h"

using glm::vec2, glm::vec3;

/** @struct SVector
*   @brief Vector structure*/
struct SVector
{
	vec3 rPosition;
	vec3 rNormal;
	vec2 rTexCoords;

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



inline SVector SVector::operator+(SVector const& InrVertex) noexcept { rPosition += InrVertex.rPosition; return InrVertex; }
inline void SVector::operator+(vec3 const& InrVector) noexcept { rPosition += InrVector; }

inline SVector SVector::operator-(SVector const& InrVertex) noexcept { rPosition -= InrVertex.rPosition; return InrVertex; }
inline void SVector::operator-(vec3 const& InrVector) noexcept { rPosition -= InrVector; }

inline SVector SVector::operator*(SVector const& InrVertex) noexcept { rPosition *= InrVertex.rPosition; return InrVertex; }
inline void SVector::operator*(vec3 const& InrVector) noexcept { rPosition *= InrVector;}

inline SVector SVector::operator/(SVector const& InrVertex) { rPosition /= InrVertex.rPosition; return InrVertex; }
inline void SVector::operator/(vec3 const& InrVector) { rPosition /= InrVector; }

inline void SVector::SetPosition(vec3 const& InrPos) noexcept { rPosition = InrPos; }
inline void SVector::SetPosition(float const InrPosX, float const InrPosY, float const InrPosZ) noexcept { rPosition.x = InrPosX; rPosition.y = InrPosY; rPosition.z = InrPosZ; }

inline void SVector::SetNormal(vec3 const& InrNorm) noexcept { rNormal = InrNorm; }
inline void SVector::SetNormal(float const InrNormX, float const InrNormY, float const InrNormZ) noexcept { rNormal.x = InrNormX; rNormal.y = InrNormY; rNormal.z = InrNormZ; }

inline void SVector::SetTexCoord(vec2 const& InrTexCoord) noexcept { rTexCoords = InrTexCoord; }
inline void SVector::SetTexCoord(float const InrTexCoordX, float const InrTexCoordY) noexcept { rTexCoords.x = InrTexCoordX; rTexCoords.y = InrTexCoordY; }

constexpr inline vec3 SVector::GetPosition() const noexcept { return rPosition; }
constexpr inline vec3 SVector::GetNormal() const noexcept { return rNormal; }
constexpr inline vec2 SVector::SetTexCoord() const noexcept { return rTexCoords; }

constexpr inline float SVector::GetDotProduct(vec3 const& InrVertex) const  noexcept
{
	return rPosition.x * InrVertex.x +
		   rPosition.y * InrVertex.y +
		   rPosition.z * InrVertex.z;
}

constexpr inline vec3 SVector::GetCrossProduct(vec3 const& InrVec) const noexcept
{
	return vec3(rPosition.y * InrVec.z - rPosition.z * InrVec.y,
				rPosition.x * InrVec.z - rPosition.z * InrVec.x,
				rPosition.x * InrVec.y - rPosition.y * InrVec.x);
}

constexpr inline vec3 SVector::GetDirection(vec3 const& InrVertex) const noexcept
{
	return vec3(abs(abs(rPosition.x) - abs(InrVertex.x)),
		   abs(abs(rPosition.y) - abs(InrVertex.y)),
		   abs(abs(rPosition.z) - abs(InrVertex.z)));
}

constexpr inline float SVector::GetLength(vec3 const& InrVec) const noexcept
{
	return abs(abs(rPosition.x) - abs(InrVec.x)) +
		   abs(abs(rPosition.y) - abs(InrVec.y)) +
		   abs(abs(rPosition.z) - abs(InrVec.z));
}

constexpr inline float SVector::GetDistance(vec3 const& InrVec) const noexcept { return powf(GetLength(InrVec),2) + 1; }