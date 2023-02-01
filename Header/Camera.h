#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

class Camera
{
public:

	Camera(vec3 InrCameraLoc, vec3 InrCameraFront, vec3 InrCameraUp, float InfFOV, float InfAspectRatio, float InfTravelSpeed, float InfNearClip, float InfFarClip);

	inline void TravelForwards(float InfTravelSpeed);
	inline void TravelSideways(float InfTravelSpeed);
	inline void TravelUpwards(float InfTravelSpeed);

	inline void AddLocation(vec3 InrVectorLoc);
	inline void AddLocX(float InfLocX);
	inline void AddLocY(float InfLocY);
	inline void AddLocZ(float InfLocZ);

	inline void AddRotation(vec3 InrVectorRot);
	inline void AddYaw(float InfYaw);
	inline void AddPitch(float InfPitch);
	inline void AddRoll(float InfRoll);

	inline void SetLocation(vec3 InrVectorLoc);
	inline void SetLocX(float InfLocX);
	inline void SetLocY(float InfLocY);
	inline void SetLocZ(float InfLocZ);

	inline void SetRotation(vec3 InrVectorRot);
	inline void SetYaw(float InfYaw);
	inline void SetPitch(float InfPitch);
	inline void SetRoll(float InfRoll);

	inline void SetMaxRotation(vec3 InrMaxRotation);
	inline void SetMinRotation(vec3 InrMinRotation);

	inline void SetFOV(float InfFOV);

	constexpr inline vec3 GetLocation() const;
	constexpr inline vec3 GetRotation() const;

	constexpr inline float GetFOV() const;
	constexpr inline vec3 GetFront() const;
	constexpr inline vec3 GetUp() const;
	constexpr inline mat4 GetView() const;
	constexpr inline mat4 GetProjection() const;

	void Update();

protected:
	float fFOV = 45.0f, fAspectRation = 16.0f/9.0f, fTravelSpeed = 0.001f;
	float fNearClip = 0.1f, fFarClip = 100.0f;

	vec3 rLoc;
	vec3 rRotation;
	vec3 rMaxRotation = vec3(0.0f), rMinRotation = vec3(0.0f);

private:
	vec3 rCameraFront;
	vec3 rCameraUp;
	mat4 rCameraView = mat4(1.0f);
	mat4 rCameraProjection = mat4(1.0f);

	inline void UpdateCoordRotation();
	inline void UpdateViewMatrix();
	inline void UpdateProjectionMatrix();
};

inline void Camera::TravelForwards(float InfScalar) { AddLocation(((InfScalar * fTravelSpeed) * rCameraFront)); }

inline void Camera::TravelSideways(float InfScalar) { AddLocation(((InfScalar * fTravelSpeed) * normalize(cross(rCameraFront, rCameraUp)))); }

inline void Camera::TravelUpwards(float InfScalar) { AddLocation(((InfScalar * fTravelSpeed) * rCameraUp)); }

inline void Camera::AddLocation(vec3 InrVectorLoc)
{
	AddLocX(InrVectorLoc.x);
	AddLocY(InrVectorLoc.y);
	AddLocZ(InrVectorLoc.z);
}

inline void Camera::AddLocX(float InfLocX) { rLoc.x += InfLocX; }

inline void Camera::AddLocY(float InfLocY) { rLoc.y += InfLocY; }

inline void Camera::AddLocZ(float InfLocZ) { rLoc.z += InfLocZ; }

inline void Camera::AddRotation(vec3 InrVectorRot)
{
	AddYaw(InrVectorRot.x);
	AddPitch(InrVectorRot.y);
	AddRoll(InrVectorRot.z);
}

inline void Camera::AddYaw(float InfYaw)
{
	rRotation.x += InfYaw;

	if (rRotation.x < rMinRotation.x)
		rRotation.x = rMinRotation.x;
	else if (rRotation.x > rMaxRotation.x)
		rRotation.x = rMaxRotation.x;
}

inline void Camera::AddPitch(float InfPitch)
{
	rRotation.y += InfPitch;

	if (rRotation.y < rMinRotation.y)
		rRotation.y = rMinRotation.y;
	else if (rRotation.y > rMaxRotation.y)
		rRotation.y = rMaxRotation.y;
}

inline void Camera::AddRoll(float InfRoll)
{
	rRotation.z += InfRoll;

	if (rRotation.z < rMinRotation.z)
		rRotation.z = rMinRotation.z;
	else if (rRotation.z > rMaxRotation.z)
		rRotation.z = rMaxRotation.z;
}

inline void Camera::SetLocation(vec3 InrVectorLoc)
{
	SetLocX(InrVectorLoc.x);
	SetLocY(InrVectorLoc.y);
	SetLocZ(InrVectorLoc.z);
}

inline void Camera::SetLocX(float InrLocX) { rLoc.x = InrLocX; }

inline void Camera::SetLocY(float InrLocY) { rLoc.y = InrLocY; }

inline void Camera::SetLocZ(float InrLocZ) { rLoc.z = InrLocZ; }

inline void Camera::SetRotation(vec3 InrVectorRot)
{
	SetYaw(InrVectorRot.x);
	SetPitch(InrVectorRot.y);
	SetRoll(InrVectorRot.z);
}

inline void Camera::SetYaw(float InfYaw)
{
	rRotation.x = InfYaw;

	if (rRotation.x < rMinRotation.x)
		rRotation.x = rMinRotation.x;
	else if (rRotation.x > rMaxRotation.x)
		rRotation.x = rMaxRotation.x;
}

inline void Camera::SetPitch(float InfPitch)
{
	rRotation.y = InfPitch;

	if (rRotation.y < rMinRotation.y)
		rRotation.y = rMinRotation.y;
	else if (rRotation.y > rMaxRotation.y)
		rRotation.y = rMaxRotation.y;
}

inline void Camera::SetRoll(float InfRoll)
{
	rRotation.y = InfRoll;

	if (rRotation.z < rMinRotation.z)
		rRotation.z = rMinRotation.z;
	else if (rRotation.z > rMaxRotation.z)
		rRotation.z = rMaxRotation.z;
}

inline void Camera::SetMaxRotation(vec3 InrMaxRotation) { rMaxRotation = InrMaxRotation; }

inline void Camera::SetMinRotation(vec3 InrMinRotation) { rMinRotation = InrMinRotation; }

inline void Camera::SetFOV(float InfFOV) { fFOV = InfFOV; }

inline void Camera::UpdateCoordRotation()
{
	rCameraFront = normalize(
		vec3(
			cos(radians(rRotation.x)) * cos(radians(rRotation.y)),
			sin(radians(rRotation.y)),
			sin(radians(rRotation.x)) * cos(radians(rRotation.y))
		)
	);
}

inline void Camera::UpdateViewMatrix() { rCameraView = lookAt(rLoc, rLoc + rCameraFront, rCameraUp); }

inline void Camera::UpdateProjectionMatrix() { rCameraProjection = perspective(fFOV, fAspectRation, fNearClip, fFarClip); }

constexpr inline vec3 Camera::GetLocation() const { return rLoc; }

constexpr inline vec3 Camera::GetRotation() const { return rRotation; }

constexpr inline float Camera::GetFOV() const { return fFOV; }

constexpr inline vec3 Camera::GetFront() const { return rCameraFront; }

constexpr inline vec3 Camera::GetUp() const { return rCameraUp; }

constexpr inline mat4 Camera::GetProjection() const { return rCameraProjection; }

constexpr inline mat4 Camera::GetView() const { return rCameraView; }