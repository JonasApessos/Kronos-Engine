#include "Camera.h"


Camera::Camera(
	vec3 InrCameraLoc,
	vec3 InrCameraFront,
	vec3 InrCameraUp,
	float InfFOV,
	float InfAspectRatio,
	float InfTravelSpeed,
	float InfNearClip,
	float InfFarClip) : 
	rLoc(InrCameraLoc),
	rCameraFront(InrCameraFront),
	rCameraUp(InrCameraUp),
	fFOV(InfFOV),
	fAspectRation(InfAspectRatio),
	fTravelSpeed(InfTravelSpeed),
	fNearClip(InfNearClip),
	fFarClip(InfFarClip)
{

}

void Camera::Update()
{
	UpdateCoordRotation();
	UpdateProjectionMatrix();
	UpdateViewMatrix();
}