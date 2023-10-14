#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::vec3, glm::mat4;
using glm::perspective, glm::normalize, glm::radians, glm::lookAt;

/** \class Camera
* 	\brief Camera class for 3d space
* 
*/
class Camera
{
/*! \fn Camera
	*	\param InrCameraLoc
	*	\param InrCameraFront
	*	\param InrCameraUp
	*	\param InfFOV
	*	\param InfAspectRatio
	*	\param InfTravelSpeed
	*	\param InfNearClip
	*	\param InfFarClip
	*
	* 	\brief constructor method
	* */

public:
	bool bClampRotation = false; //!< Clamp camera rotation
	
	Camera(
		vec3 InrCameraLoc,
		vec3 InrCameraFront,
		vec3 InrCameraUp,
		float InfFOV,
		float InfAspectRatio,
		float InfTravelSpeed,
		float InfNearClip,
		float InfFarClip);

	inline void TravelForwards(float InfTravelSpeed); //!< \param InfTravelSpeed \brief Forward traveling vector
	inline void TravelSideways(float InfTravelSpeed); //!< \param InfTravelSpeed \brief Sideways traveling vector
	inline void TravelUpwards(float InfTravelSpeed); //!< \param InfTravelSpeed \brief Upwards traveling vector

	inline void AddLocation(vec3 InrVectorLoc); //!< \param InrVectorLoc \brief Add vector location
	inline void AddLocX(float InfLocX); //!< \param InfLocX \brief Add x location vector
	inline void AddLocY(float InfLocY); //!< \param InfLocY \brief Add y location vector
	inline void AddLocZ(float InfLocZ); //!< \param InfLocZ \brief Add z location vector

	inline void AddRotation(vec3 InrVectorRot); //!< \param InrVectorRot \brief Add vector rotation
	inline void AddYaw(float InfYaw); //!< \param InfYaw \brief Add x rotation vector
	inline void AddPitch(float InfPitch); //!< \param InfPitch \brief Add y rotation vector
	inline void AddRoll(float InfRoll); //!< \param InfRoll \brief Add z rotation vector

	inline void SetLocation(vec3 InrVectorLoc); //!< \param InrVectorLoc \brief Set vector location
	inline void SetLocX(float InfLocX); //!< \param InfLocX \brief Set x location vector
	inline void SetLocY(float InfLocY); //!< \param InfLocY \brief Set y location vector
	inline void SetLocZ(float InfLocZ); //!< \param InfLocZ \brief Set z location vector

	inline void SetRotation(vec3 InrVectorRot); //!< \param InrVectorRot \brief Set vector rotation
	inline void SetYaw(float InfYaw); //!< \param InfYaw \brief Set x rotation vector
	inline void SetPitch(float InfPitch); //!< \param InfPitch \brief Set y rotation vector
	inline void SetRoll(float InfRoll); //!< \param InfRoll \brief Set z rotation vector

	inline void SetMaxRotation(vec3 InrMaxRotation); //!< \param InrMaxRotation \brief Set maximum rotation vector
	inline void SetMinRotation(vec3 InrMinRotation); //!< \param InrMinRotation \brief Set Minimum rotation vector

	inline void SetFOV(float InfFOV); //!< \param InfFOV \brief Set camera FOV

	constexpr inline vec3 GetLocation() const; //!< \return vec3 \brief Get vector location
	constexpr inline vec3 GetRotation() const; //!< \return vec3 \brief Get vector rotation

	constexpr inline float GetFOV() const; //!< \return float \brief Get FOV
	constexpr inline vec3 GetFront() const; //!< \return vec3 \brief Get Front vector
	constexpr inline vec3 GetUp() const; //!< \return vec3 \brief Get Up vector
	constexpr inline mat4 GetView() const; //!< \return mat4 \brief Get view matrix
	constexpr inline mat4 GetProjection() const; //!< \return mat4 \brief Get projection matrix

	void Update(); //!< \brief Update camera data matrices

protected:
	/*! \var float fFOV
	*	\brief Field of view
	*
	*	\var float fAspectRation
	*	\brief screen Aspect Ratio
	*
	*	\var float fTravelSpeed
	*	\brief Camera travel speed*/
	float fFOV = 45.0f, fAspectRation = 16.0f/9.0f, fTravelSpeed = 0.001f;

	/*! \var float fNearClip
	*	\brief Near Clip plane
	*
	*	\var float fFarClip
	*	\brief Far Clip plane*/
	float fNearClip = 0.1f, fFarClip = 100.0f;

	/*! \var vec3 rLocation
	*	\brief Camera location in 3D space
	*
	*	\var vec3 rRotation
	*	\brief Camera rotation in 3D space*/
	vec3 rLocation = vec3(0.0f), rRotation = vec3(0.0f);

	/*! \var vec3 rMaxRotation
	*	\brief Maximum camera rotation
	*
	*	\var float rMinRotation
	*	\brief Minimum camera rotation*/
	vec3 rMaxRotation = vec3(0.0f), rMinRotation = vec3(0.0f);

private:
	vec3 rCameraFront = vec3(0.0f, 0.0f, 1.0f);
	vec3 rCameraUp = vec3(0.0f, 1.0f, 0.0f);
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

inline void Camera::AddLocX(float InfLocX) { rLocation.x += InfLocX; }

inline void Camera::AddLocY(float InfLocY) { rLocation.y += InfLocY; }

inline void Camera::AddLocZ(float InfLocZ) { rLocation.z += InfLocZ; }

inline void Camera::AddRotation(vec3 InrVectorRot)
{
	AddYaw(InrVectorRot.x);
	AddPitch(InrVectorRot.y);
	AddRoll(InrVectorRot.z);
}

inline void Camera::AddYaw(float InfYaw)
{
	rRotation.x += InfYaw;

	if (bClampRotation)
	{
		if (rRotation.x < rMinRotation.x)
			rRotation.x = rMinRotation.x;
		else if (rRotation.x > rMaxRotation.x)
			rRotation.x = rMaxRotation.x;
	}
}

inline void Camera::AddPitch(float InfPitch)
{
	rRotation.y += InfPitch;

	if (bClampRotation)
	{
		if (rRotation.y < rMinRotation.y)
			rRotation.y = rMinRotation.y;
		else if (rRotation.y > rMaxRotation.y)
			rRotation.y = rMaxRotation.y;
	}
}

inline void Camera::AddRoll(float InfRoll)
{
	rRotation.z += InfRoll;

	if (bClampRotation)
	{
		if (rRotation.z < rMinRotation.z)
			rRotation.z = rMinRotation.z;
		else if (rRotation.z > rMaxRotation.z)
			rRotation.z = rMaxRotation.z;
	}
}

inline void Camera::SetLocation(vec3 InrVectorLoc)
{
	SetLocX(InrVectorLoc.x);
	SetLocY(InrVectorLoc.y);
	SetLocZ(InrVectorLoc.z);
}

inline void Camera::SetLocX(float InrLocX) { rLocation.x = InrLocX; }

inline void Camera::SetLocY(float InrLocY) { rLocation.y = InrLocY; }

inline void Camera::SetLocZ(float InrLocZ) { rLocation.z = InrLocZ; }

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

inline void Camera::UpdateViewMatrix() { rCameraView = lookAt(rLocation, rLocation + rCameraFront, rCameraUp); }

inline void Camera::UpdateProjectionMatrix() { rCameraProjection = perspective(fFOV, fAspectRation, fNearClip, fFarClip); }

constexpr inline vec3 Camera::GetLocation() const { return rLocation; }

constexpr inline vec3 Camera::GetRotation() const { return rRotation; }

constexpr inline float Camera::GetFOV() const { return fFOV; }

constexpr inline vec3 Camera::GetFront() const { return rCameraFront; }

constexpr inline vec3 Camera::GetUp() const { return rCameraUp; }

constexpr inline mat4 Camera::GetProjection() const { return rCameraProjection; }

constexpr inline mat4 Camera::GetView() const { return rCameraView; }