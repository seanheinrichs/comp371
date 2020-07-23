#include "PointLight.h"

#include <string>
#include <iostream>

PointLight::PointLight(Model * model, glm::vec3 startingPos)
{
	PointLight::model = model;

	PointLight::color = glm::vec3(1.0, 1.0, 1.0);
	PointLight::position = startingPos;

	PointLight::ambient = glm::vec3(0.8f, 0.8f, 0.8f);
	PointLight::diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	PointLight::specular = glm::vec3(1.0f, 1.0f, 1.0f);

	PointLight::constant = 1.0f;
	PointLight::linear = 0.35f;
	PointLight::quadratic = 0.44f;
}

PointLight::PointLight(Model * model, glm::vec3 startingPos, glm::vec3 col, glm::vec3 amb, glm::vec3 dif, glm::vec3 spec, float line, float quad)
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
}

PointLight::~PointLight() {};

void PointLight::setShaderValues(Shader * shader, int lampIndex)
{
	std::string shaderIndex = "pointLights[" + std::to_string(lampIndex) + "]";

	shader->setVec3(shaderIndex + ".position", position);
	shader->setVec3(shaderIndex + ".ambient", ambient.x, ambient.y, ambient.z);
	shader->setVec3(shaderIndex + ".diffuse", diffuse.x, diffuse.y, diffuse.z);
	shader->setVec3(shaderIndex + ".specular", specular.x, specular.y, specular.z);
	shader->setFloat(shaderIndex + ".constant", constant);
	shader->setFloat(shaderIndex + ".linear", linear);
	shader->setFloat(shaderIndex + ".quadratic", quadratic);
}
