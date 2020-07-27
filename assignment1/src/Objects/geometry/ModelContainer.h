#pragma once
#include <vector>
#include <string>
#include "Model.h"
class ModelContainer 
{
public: 
	std::vector<Model*> models;

	ModelContainer();

	Model* getModelByName(std::string name);
	void addModel(Model* model);
	void draw(int mode, Shader* shaderProg);
	void bindArrayBuffer();
	void deallocate();
	
	void Reposition(glm::vec3 position);
	void addRotation(float radians, glm::vec3 axis);
	void addScale(glm::vec3 scale);
	void addTranslation(glm::vec3 translate);
	void addRotation(float radians, glm::vec3 axis, std::string name);
	void addScale(glm::vec3 scale, std::string name);
	glm::mat4 getShear(); 

	glm::mat4 getShearMatrix();
	void addShearMatrix(glm::vec2 shear, char axis);
	void addTranslation(glm::vec3 translate, std::string name);
	glm::mat4 getRotation();
	glm::mat4 getTranslation();
	glm::mat4 getScale();
	glm::mat4 getModelMatrix(bool shear = false);
  
	glm::vec3 shear_vec; 
	glm::vec3 rotate_vec;
	glm::vec3 translate_vec;
	glm::vec3 scale_vec;

	glm::mat4 shearMatrix;
	glm::vec2 shearX;
	glm::vec2 shearY;
	glm::vec2 shearZ;

	float rotate_angle;
};