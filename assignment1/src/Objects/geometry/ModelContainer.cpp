#include "ModelContainer.h"
#include <vector>
#include <string>
#include <glm/gtx/transform2.hpp>
#include <iostream>

/*
*Description: binds all the array buffers for all the objects that it contains
*/
void ModelContainer::bindArrayBuffer()
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		(*it)->bindArrayBuffer(true, (*it));
	}
}

/*
*Description: adds a new model to the models vector
*
*@param
*		model: new model to add
*/
void ModelContainer::addModel(Model* model) 
{
	models.push_back(model);
}

/*
*Description: resets the shear vector for all models
*/
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

/*
*Description: default constructor for modelContainer
*/
ModelContainer::ModelContainer() 
{
	rotate_vec = glm::vec3(0.0f, 0.0f, 0.0f);
	translate_vec = glm::vec3(0.0f, 0.0f, 0.0f);
	scale_vec = glm::vec3(0.0f, 0.0f, 0.0f);
	rotate_angle = 0.0;
	rotate_angleX = 0.0;
	rotate_angleY = 0.0;
	rotate_angleZ = 0.0;

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

/*
*Description: returns a model by its name if that model was specified
*
*@param
*		name: name of the model to retrieve
*/
Model* ModelContainer::getModelByName(std::string name) 
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		if ((**it).name == name)
			return (*it);
	}
	return nullptr;
}

/*
*Description: renders all models by calling their draw methdo
*
*@params:
*		mode: the opengl rendering mode
*		shaderProg: the shader program that is in charge of rendering the current object
*/
void ModelContainer::draw(int mode, Shader* shaderProg)
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		(*it)->draw(mode, shaderProg);
	}
}


/*
*Description: deallocates all gpu memory for the models
*/
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

/*
*Description: rotates a model by its name if that model was specified
*
*@param:
*		degrees: the amount of rotations in degrees
*		axis: vector representing the axis around which to rotate
*		name: name of the model to change
*/
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

/*
*Description: rotates a the calling object by a certain amount of degrees about the X axis
*
*@param:
*		degrees: the amount of rotations in degrees
*/
void ModelContainer::addRotationX(float degrees)
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		(*it)->addRotationX(degrees);
	}
	rotate_angleX += degrees;
}

/*
*Description: rotates a the calling object by a certain amount of degrees about the Y axis
*
*@param:
*		degrees: the amount of rotations in degrees
*/
void ModelContainer::addRotationY(float degrees)
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		(*it)->addRotationY(degrees);
	}
	rotate_angleY += degrees;
}

/*
*Description: rotates a the calling object by a certain amount of degrees about the Z axis
*
*@param:
*		degrees: the amount of rotations in degrees
*/
void ModelContainer::addRotationZ(float degrees)
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		(*it)->addRotationZ(degrees);
	}
	rotate_angleZ += degrees;
}

/*
*Description: sets the rotation parameters for all models
*
*@param:
*		degrees: the amount of rotations in degrees
*		axis: vector representing the axis around which to rotate
*/
void ModelContainer::setRotation(float degrees, glm::vec3 axis)
{
	rotate_vec = axis;
	rotate_angle = degrees;

	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		(*it)->setRotation(degrees, axis);
	}
}

glm::mat4 ModelContainer::getRotationX()
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(rotate_angleX), glm::vec3(1.0, 0.0, 0.0));
}

glm::mat4 ModelContainer::getRotationY()
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(rotate_angleY), glm::vec3(0.0, 1.0, 0.0));
}

glm::mat4 ModelContainer::getRotationZ()
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(rotate_angleZ), glm::vec3(0.0, 0.0, 1.0));
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

/*
*Description: adds to the scale for a specific model matching the passed name
*
*@param:
*		scale: a scale vector representing the values to add
*		name: name of the model to change
*/
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
	return getTranslation() * getRotationX() * getRotationY() * getRotationZ() * getScale() * (shear ? getShearMatrix() : glm::mat4(1.0f));
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

/*
*Description: adds translation to a specific model
*
*@param:
*		translate: vector representing the translation amounts in each axis
*		name: name of the model to change
*/
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


/*
*Description: Helper method used in combination with assimp that otimizes models that use the same textures
* the way the system currently works, each model has a unique material. Therefore, if there are multiple models 
* using the same material, we can combine them into a single model. That is what this method does
*
*/
void ModelContainer::optimizeModels() 
{	
	std::vector<Model*> m;
	int mCounter = 0;
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		if (mCounter == 0)
		{
			m.push_back(*it);
			mCounter += 1;
		}
		else
		{
			bool found = false;
			for (std::vector<Model *>::iterator it2 = m.begin(); it2 < m.end(); it2++)
			{
				if ((*it2)->textureEquals(*it)) {
					(*it2)->addModel((**it));
					found = true;
					break;
				}
			}

			if (found == false) {

				m.push_back(*it);
			}

		}
	}

	std::cout << m.size() << std::endl;


	models = m;
}


/*
*Description: set all the boolean values for vertex components we wish to render
*
*@params:
*		position: boolean indicating whether to render positions or not
*		color: boolean indicating whether to render colors or not
*		normal: boolean indicating whether to render normals or not
*		texture: boolean indicating whether to render textures or not
*/
void ModelContainer::setVertexController(bool position, bool texture, bool color, bool normal)
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
		(*it)->setVertexController(position, texture, color, normal);
}


/*
*Description: print all the models that the current model container containss
*/
void ModelContainer::print() 
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
		(*it)->print();
}

/*
*Description: renders the calling object using a custom model matrix
*
*@params:
*		mode: the opengl rendering mode
*		shaderProg: the shader program that is in charge of rendering the current object
*		modelmat: a 4x4 matrix representing an arbitrary 3d transformation
*
*/
void ModelContainer::drawMod(int mode, Shader* shaderProg, glm::mat4 modelmat)
{
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		(*it)->drawMod(mode, shaderProg, modelmat);
	}
}

/*
*Description: returns the transformation of the calling object to the position specified in the constructor
*
*@params:
*		position: the position that we wish to translate the object to
*
*/
glm::mat4 ModelContainer::getTranslatedModelMatrix(glm::vec3 position)
{
	glm::vec3 mid((aabb.max.x + aabb.min.x) / 2, aabb.min.y, (aabb.max.z + aabb.min.z) / 2);
	glm::vec3 translate(position.x - mid.x, position.y - mid.y, position.z - mid.z);
	//std::cout << "x: " << translate_vec.x << " y: " << translate_vec.y << " z: " << translate_vec.z << std::endl;
	return glm::translate(glm::mat4(1.0f), translate + translate_vec) * getRotationX() * getRotationY() * getRotationZ() * getScale();
}

/*
*Description: returns the transformation of the calling object to the position specified in the constructor
*			and the vector containing the specific translation values computed
*
*@params:
*		position: the position that we wish to translate the object to
*
*/
move ModelContainer::getTranslatedModelMatrixM(glm::vec3 position)
{
	glm::vec3 mid((aabb.max.x + aabb.min.x) / 2, aabb.min.y, (aabb.max.z + aabb.min.z) / 2);
	glm::vec3 translate(position.x - mid.x, position.y - mid.y, position.z - mid.z);
	move temp;
	temp.mm = glm::translate(glm::mat4(1.0f), translate + translate_vec) * getRotationX() * getRotationY() * getRotationZ() * getScale();
	temp.translate = glm::vec4(translate + translate_vec, 1.0);
	return temp;
}

/*
*Description: calculates the axis alligned boundary box for a modelContainer
*/
void ModelContainer::calculateMinMax()
{
	std::vector<Model *>::iterator it = models.begin();
	std::map<std::string, glm::vec3> map = (**it).getMinMaxT();
	it++;
	for (; it < models.end(); it++)
	{
		std::map<std::string, glm::vec3> temp = (**it).getMinMaxT();
		if (map["max"].x < temp["max"].x)
			map["max"].x = temp["max"].x;

		if (map["max"].y < temp["max"].y)
			map["max"].y = temp["max"].y;

		if (map["max"].z < temp["max"].z)
			map["max"].z = temp["max"].z;

		if (map["min"].x > temp["min"].x)
			map["min"].x = temp["min"].x;

		if (map["min"].y > temp["min"].y)
			map["min"].y = temp["min"].y;

		if (map["min"].z > temp["min"].z)
			map["min"].z = temp["min"].z;

	}
	aabb.max = glm::vec4(map["max"], 0.0f);// *getModelMatrix();
	aabb.min = glm::vec4(map["min"], 0.0f);// *getModelMatrix();

}

int ModelContainer::getVAVertexCount() 
{
	long vertexCount = 0;
	for (std::vector<Model *>::iterator it = models.begin(); it < models.end(); it++)
	{
		vertexCount += (*it)->getVAVertexCount();
	}
	return vertexCount;
}
