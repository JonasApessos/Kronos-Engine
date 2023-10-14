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
	fFOV(InfFOV),
	fAspectRation(InfAspectRatio),
	fTravelSpeed(InfTravelSpeed),
	fNearClip(InfNearClip),
	fFarClip(InfFarClip),
	rLocation(InrCameraLoc),
	rCameraFront(InrCameraFront),
	rCameraUp(InrCameraUp)
	
{

}

void Camera::Update()
{
	UpdateCoordRotation();
	UpdateProjectionMatrix();
	UpdateViewMatrix();
}