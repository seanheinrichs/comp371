#include "Camera.h";

#include <glm/glm.hpp>
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

	updateCamera();
}	

void Camera::tiltCamera(float pitch)
{
	pitchAngle += pitch;
	
	// Ensure pitch is inbounds for both + and - values to prevent irregular behavior
	pitchAngle >  89.0f ? pitchAngle =  89.0f : NULL;
	pitchAngle < -89.0f ? pitchAngle = -89.0f : NULL;

	updateCamera();
}

void Camera::zoomCamera(float zoom)
{
	if (fieldOfViewAngle >= MIN_ZOOM && fieldOfViewAngle <= MAX_ZOOM)
	{
		fieldOfViewAngle -= zoom * 0.1;
	}

	// Limit zoom values to prevent irregular behavior
	fieldOfViewAngle <= MIN_ZOOM ? fieldOfViewAngle = MIN_ZOOM : NULL;
	fieldOfViewAngle >= MAX_ZOOM ? fieldOfViewAngle = MAX_ZOOM : NULL;
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::updateCamera()
{
	front.x = cos(glm::radians(yawAngle)) * cos(glm::radians(pitchAngle));
	front.y = sin(glm::radians(pitchAngle));
	front.z = sin(glm::radians(yawAngle)) * cos(glm::radians(pitchAngle));
	front = glm::normalize(front);
}