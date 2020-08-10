#pragma once

#include "../../Opengl_a/Shader.h"
#include "../geometry/Model.h"

class Light
{
public:
	// Constructors & Destructors

	Light(Model * lampModel, glm::vec3 startingPos, bool active);
	Light(Model * lampModel, glm::vec3 startingPos, glm::vec3 dir, glm::vec3 amb, glm::vec3 dif, glm::vec3 spec, float line, float quad, bool active);
	
	~Light();

	// Functions
	void setShaderValues(Shader * shader, bool isSpotLight);

	// Accessors
	Model* getModel() const { return model; };
	glm::vec3 getPosition() const { return position; };
	glm::vec3 getDirection() const { return direction; };
	glm::vec3 getAmbient() const { return ambient; };
	glm::vec3 getDiffuse() const { return diffuse; };
	glm::vec3 getSpecular() const { return specular; };
	float getConstant() const { return constant; };
	float getLinear() const { return linear; };
	float getQuadratic() const { return quadratic; };
	bool getActive() const { return active; };

	// Mutators
	void setActive(bool value) { active = value; };

private:
	Model * model;

	glm::vec3 direction;
	glm::vec3 position;

	// Light Modifiers
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	// Distance Modifiers
	float constant;
	float linear;
	float quadratic;

	bool active;
};