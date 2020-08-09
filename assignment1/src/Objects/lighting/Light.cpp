#include "Light.h"

#include <string>
#include <iostream>

// Default Constructor
Light::Light(Model * model, glm::vec3 startingPos, bool active)
{
	Light::model = model;

	Light::direction = glm::vec3(0.0f, 0.0f, 1.0f);
	Light::position = startingPos;

	Light::ambient = glm::vec3(0.8f, 0.8f, 0.8f);
	Light::diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	Light::specular = glm::vec3(1.0f, 1.0f, 1.0f);

	Light::constant = 1.0f;
	Light::linear = 0.045f;
	Light::quadratic = 0.0075f;

	Light::active = active;
}

// Parameterized Constructor
Light::Light(Model * model, glm::vec3 startingPos, glm::vec3 dir, glm::vec3 amb, glm::vec3 dif, glm::vec3 spec, float line, float quad, bool active)
{
	Light::model = model;

	Light::position = startingPos;
	Light::direction = dir;

	Light::ambient = amb;
	Light::diffuse = dif;
	Light::specular = spec;

	Light::constant = 1.0f;
	Light::linear = line;
	Light::quadratic = quad;

	Light::active = active;
}

// Deconstructor
Light::~Light() {};

// Sets all the values in the fragment shader specific to that light
void Light::setShaderValues(Shader * shader, bool isSpotLight)
{
	if (isSpotLight)
	{
		shader->setVec3("spotLight.position", position);
		shader->setVec3("spotLight.direction", direction);
		shader->setVec3("spotLight.ambient", ambient.x, ambient.y, ambient.z);
		shader->setVec3("spotLight.diffuse", diffuse.x, diffuse.y, diffuse.z);
		shader->setVec3("spotLight.specular", specular.x, specular.y, specular.z);
		shader->setFloat("spotLight.constant", constant);
		shader->setFloat("spotLight.linear", linear);
		shader->setFloat("spotLight.quadratic", quadratic);
		shader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		shader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
	}
	else
	{
		shader->setVec3("pointLight.position", position);
		shader->setVec3("pointLight.ambient", ambient.x, ambient.y, ambient.z);
		shader->setVec3("pointLight.diffuse", diffuse.x, diffuse.y, diffuse.z);
		shader->setVec3("pointLight.specular", specular.x, specular.y, specular.z);
		shader->setFloat("pointLight.constant", constant);
		shader->setFloat("pointLight.linear", linear);
		shader->setFloat("pointLight.quadratic", quadratic);
	}
}
