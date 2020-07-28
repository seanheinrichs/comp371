#include "ModelContainer.h"
#include <vector>
#include <string>
#include <glm/gtx/transform2.hpp>


void ModelContainer::bindArrayBuffer()
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		(*it)->bindArrayBuffer(true, (*it));
	}
}

void ModelContainer::addModel(Model* model) 
{
	models.push_back(model);
}

void ModelContainer::resetShear()
{
	shearX = glm::vec2(0.0f, 0.0f);
	shearY = glm::vec2(0.0f, 0.0f);
	shearZ = glm::vec2(0.0f, 0.0f);

	setupShearMatrix();
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		(*it)->resetShear();
	}

}

ModelContainer::ModelContainer() 
{
	rotate_vec = glm::vec3(0.0f, 0.0f, 1.0f);
	translate_vec = glm::vec3(0.0f, 0.0f, 0.0f);
	scale_vec = glm::vec3(0.0f, 0.0f, 0.0f);
	rotate_angle = 0.0;

	shearX = glm::vec2(0.0f,0.0f);
	shearY = glm::vec2(0.0f, 0.0f);
	shearZ = glm::vec2(0.0f, 0.0f);

	setupShearMatrix();
	

}

//sets up the values of the shear matrix for each axis
void ModelContainer::setupShearMatrix()
{
	shearMatrix[0][0] = 1;
	shearMatrix[0][1] = shearZ.y;
	shearMatrix[0][2] = shearY.y;
	shearMatrix[0][3] = 0;

	shearMatrix[1][0] = shearZ.x;
	shearMatrix[1][1] = 1;
	shearMatrix[1][2] = shearX.y;
	shearMatrix[1][3] = 0;

	shearMatrix[2][0] = shearY.x;
	shearMatrix[2][1] = shearX.x;
	shearMatrix[2][2] = 1;
	shearMatrix[2][3] = 0;

	shearMatrix[3][0] = 0;
	shearMatrix[3][1] = 0;
	shearMatrix[3][2] = 0;
	shearMatrix[3][3] = 0;
}
Model* ModelContainer::getModelByName(std::string name) 
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		if ((**it).name == name)
			return (*it);
	}
	return nullptr;
}

void ModelContainer::draw(int mode, Shader* shaderProg)
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		(*it)->draw(mode, shaderProg);
	}
}

void ModelContainer::deallocate()
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		(*it)->deallocate();
	}
}


//Method that updates the values of the x-y-z components of the rotation vector used to calculate the model transformation matrix
void ModelContainer::addRotation(float degrees, glm::vec3 axis)
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		(*it)->addRotation(degrees, axis);
	}

	rotate_vec.x += axis.x;
	rotate_vec.y += axis.y;
	rotate_vec.z += axis.z;
	rotate_angle += degrees;
}

void ModelContainer::addRotation(float degrees, glm::vec3 axis, std::string name)
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		if ((**it).name == name)
		{
			(*it)->addRotation(degrees, axis);
			break;
		}
	}
}

//Method that updates the values of the x-y-z components of the scale vector used to calculate the model transformation matrix
void ModelContainer::addScale(glm::vec3 scale)
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		(*it)->addScale(scale);
	}

	if (scale_vec.x >= 0.0 && scale_vec.y >= 0.0 && scale_vec.z >= 0.0) {
		scale_vec.x += scale.x;
		scale_vec.y += scale.y;
		scale_vec.z += scale.z;
	}
	else {
		scale_vec.x = 0.2f;
		scale_vec.y = 0.2f;
		scale_vec.z = 0.2f;
	}

}

void ModelContainer::addScale(glm::vec3 scale, std::string name)
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		if ((**it).name == name)
		{
			(*it)->addScale(scale);
			break;
		}
	}

}

//returns the shearing matrix
glm::mat4 ModelContainer::getShearMatrix()
{
	setupShearMatrix();
	return shearMatrix;
}

//Method that calculates the transformation matrix of the model
glm::mat4 ModelContainer::getModelMatrix(bool shear)
{
	if (rotate_vec.x == 0 && rotate_vec.y == 0 && rotate_vec.z == 0)
		return getTranslation() *  getScale();
	else
		return
		getTranslation() * getRotation() * getScale() * (shear ? getShearMatrix() : glm::mat4(1.0f));

}

//adds shears to model according to the axis passed, which will determine around which axis it will shear
void ModelContainer::addShearMatrix(glm::vec2 shear, char axis)
{
	if (axis == 'x')
	{
		for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
		{
			(*it)->addShearMatrix(shear, 'x');
		}
		shearX.x += shear.x;
		shearX.y += shear.y;
	}
	else if (axis == 'y')
	{
		for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
		{
			(*it)->addShearMatrix(shear, 'y');
		}
		shearY.x += shear.x;
		shearY.y += shear.y;
	}
	else if (axis == 'z')
	{
		for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
		{
			(*it)->addShearMatrix(shear, 'z');
		}
		shearZ.x += shear.x;
		shearZ.y += shear.y;
	}
}


//Method that updates the values of the x-y-z components of the translation vector used to calculate the model transformation matrix
void ModelContainer::addTranslation(glm::vec3 translate)
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		(*it)->addTranslation(translate);
	}

	ModelContainer::translate_vec.x += translate.x;
	ModelContainer::translate_vec.y += translate.y;
	ModelContainer::translate_vec.z += translate.z;
}

void ModelContainer::addTranslation(glm::vec3 translate, std::string name)
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		if ((**it).name == name)
		{
			(*it)->addTranslation(translate);
			break;
		}
	}
}

//Method that returns the rotation matrix
glm::mat4 ModelContainer::getRotation()
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(rotate_angle), rotate_vec);
}

//Method that returns the translation matrix
glm::mat4 ModelContainer::getTranslation()
{

	return glm::translate(glm::mat4(1.0f), translate_vec);
}

//Method that returns the scale matrix
glm::mat4 ModelContainer::getScale()
{
	return glm::scale(glm::mat4(1.0f), scale_vec);
}

//Method that updates the position of the model
void ModelContainer::Reposition(glm::vec3 position)
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		(*it)->Reposition(position);
	}

	ModelContainer::translate_vec.x = position.x;
	ModelContainer::translate_vec.y = position.y;
	ModelContainer::translate_vec.z = position.z;
}


glm::mat4 ModelContainer::getReposition()
{
	return glm::translate(glm::mat4(1.0f), translate_vec);
}