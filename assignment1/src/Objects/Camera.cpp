#include "Camera.h";

#include <iostream>

const float MAX_ZOOM = 45.0f;
const float MIN_ZOOM = 1.0f;

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraFront, glm::vec3 cameraUp)
{
	position = glm::vec3(cameraPosition);
	front = glm::vec3(cameraFront);
	up = glm::vec3(cameraUp);

	// Set to predefined defaults
	yawAngle = -90.0f;
	pitchAngle = 0.0f;
	fieldOfViewAngle = 45.0f;
}

Camera::~Camera() {}

void Camera::panCamera(float yaw)
{
	yawAngle += yaw;
}	

void Camera::tiltCamera(float pitch)
{
	pitchAngle += pitch;
	
	// Ensure pitch is inbounds for both + and - values to prevent irregular behavior
	pitchAngle >  89.0f ? pitchAngle =  89.0f : NULL;
	pitchAngle < -89.0f ? pitchAngle = -89.0f : NULL;
}

void Camera::zoomCamera(float yOffset)
{
	if (fieldOfViewAngle >= MIN_ZOOM && fieldOfViewAngle <= MAX_ZOOM)
	{
		fieldOfViewAngle -= yOffset * 0.1;
	}

	// Limit zoom values to prevent irregular behavior
	fieldOfViewAngle <= MIN_ZOOM ? fieldOfViewAngle = MIN_ZOOM : NULL;
	fieldOfViewAngle >= MAX_ZOOM ? fieldOfViewAngle = MAX_ZOOM : NULL;
}