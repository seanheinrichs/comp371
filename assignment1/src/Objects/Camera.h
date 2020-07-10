#ifndef GRID_H
#define GRID_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Camera
{
public:
	// Constructors & Destructors
	Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up);
	~Camera();

	// Functions
	void panCamera(float yaw);
	void tiltCamera(float pitch);
	void zoomCamera(float zoom);
	glm::mat4 calculateViewMatrix();

	float fieldOfViewAngle;

private:
	// Camera Initialization
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;

	// Transformation Variables
	float yawAngle;
	float pitchAngle;
	
	void updateCamera();
};


#endif
