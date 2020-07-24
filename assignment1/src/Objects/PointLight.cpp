#include "PointLight.h"

#include <string>
#include <iostream>

PointLight::PointLight(Model * model, glm::vec3 startingPos, bool active)
{
	PointLight::model = model;

	PointLight::color = glm::vec3(1.0, 1.0, 1.0);
	PointLight::position = startingPos;

	PointLight::ambient = glm::vec3(0.8f, 0.8f, 0.8f);
	PointLight::diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	PointLight::specular = glm::vec3(1.0f, 1.0f, 1.0f);

	PointLight::constant = 1.0f;
	PointLight::linear = 0.045f;
	PointLight::quadratic = 0.0075f;

	PointLight::active = active;
}

PointLight::PointLight(Model * model, glm::vec3 startingPos, glm::vec3 col, glm::vec3 amb, glm::vec3 dif, glm::vec3 spec, float line, float quad, bool active)
{
	PointLight::model = model;

	PointLight::position = startingPos;
	PointLight::color = col;

	PointLight::ambient = amb;
	PointLight::diffuse = dif;
	PointLight::specular = spec;

	PointLight::constant = 1.0f;
	PointLight::linear = line;
	PointLight::quadratic = quad;

	PointLight::active = active;
}

PointLight::~PointLight() {};

void PointLight::setShaderValues(Shader * shader)
{
	shader->setVec3("pointLight.position", position);
	shader->setVec3("pointLight.ambient", ambient.x, ambient.y, ambient.z);
	shader->setVec3("pointLight.diffuse", diffuse.x, diffuse.y, diffuse.z);
	shader->setVec3("pointLight.specular", specular.x, specular.y, specular.z);
	shader->setFloat("pointLight.constant", constant);
	shader->setFloat("pointLight.linear", linear);
	shader->setFloat("pointLight.quadratic", quadratic);
}
