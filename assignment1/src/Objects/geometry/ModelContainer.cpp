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


ModelContainer::ModelContainer() 
{
	rotate_vec = glm::vec3(0.0f, 0.0f, 1.0f);
	translate_vec = glm::vec3(0.0f, 0.0f, 0.0f);
	scale_vec = glm::vec3(0.0f, 0.0f, 0.0f);
	rotate_angle = 0.0;
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

void ModelContainer::draw(int mode)
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		(*it)->draw(mode);
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

glm::mat4 ModelContainer::getShear()
{
	//return glm::shearZ3D(glm::mat4(1.0f), shear_vec.y, shear_vec.z); //forward/backwards
	return glm::shearX3D(glm::mat4(-1.0f), shear_vec.y, shear_vec.z); //from side to side

}

//Method that calculates the transformation matrix of the model
glm::mat4 ModelContainer::getModelMatrix(bool shear)
{
	if (rotate_vec.x == 0 && rotate_vec.y == 0 && rotate_vec.z == 0)
		return getTranslation() *  getScale();
	else
		return (shear ? getShear() : glm::mat4(1.0f)) * getTranslation() * getRotation() * getScale();
}

//adds shears to model
void ModelContainer::addShear(glm::vec3 shear)
{

	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		(*it)->addShear(shear);
	}

	shear_vec.x += shear.x;
	shear_vec.y += shear.y;
	shear_vec.z += shear.z;

}

void ModelContainer::addShear(glm::vec3 shear, std::string name)
{

	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		if ((**it).name == name)
		{
			(*it)->addShear(shear);
			break;
		}
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

