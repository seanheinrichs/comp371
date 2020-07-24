/*
Model

Depends on: Polygon.h

Description: A container for groups of related geometry. It handles the creation of 
arbitrarily sized vertex arrays from the polgons that it contains.

origin: the point of origin for this particular polygon
vaComponentCount: the number of vertex components in the Polygons of the model
vaByteSize: the number Bytes required to contain the vertices of all the polygons in memory

*/

#pragma once

#include "Model.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "../../Common.h"
#include <GL/glew.h> 
#include "../../utils/GL_Error.h"
#include "../../Opengl_a/Texture.h"


//Model constructor, setting up position, texture and color components
Model::Model(bool position, bool texture, bool color, bool normal, std::string name, Shader* shader, int textureIndex)
{
	Model::textureIndex = textureIndex;
	Model::shader = shader;
	Model::name = name;
	Model::position = position;
	Model::texture = texture;
	Model::color = color;
	Model::normal = normal;
	origin = glm::vec3(0.0f);
	rotate_vec = glm::vec3(0.0f, 0.0f, 1.0f);
	translate_vec = glm::vec3(0.0f, 0.0f, 0.0f);
	scale_vec = glm::vec3(0.0f, 0.0f, 0.0f);
	rotate_angle = 0.0;
}

//default constructor
Model::Model() 
{
	Model::textureIndex = 0;
	Model::shader = nullptr;
	Model::name = "default";
	Model::position = true;
	Model::texture = false;
	Model::color = false;
	Model::normal = false;
	origin = glm::vec3(0.f);
	rotate_vec = glm::vec3(0.0f, 0.0f, 0.0f);
	scale_vec = glm::vec3(0.0f, 0.0f, 0.0f);
	rotate_angle = 0.0;
}

void Model::setBoolean(bool position, bool texture, bool color, bool normal) 
{
	Model::position = position;
	Model::texture = texture;
	Model::color = color;
	Model::normal = normal;

	for (std::vector<Polygon *>::iterator it = polygons.begin(); it < polygons.end(); it++)
	{
		(**it).setVertexController(position, texture, color, normal);
	}

}

//Method that updates the values of the x-y-z components of the rotation vector used to calculate the model transformation matrix
void Model::addRotation(float degrees, glm::vec3 axis) 
{
	for (std::vector<Polygon *>::iterator it = polygons.begin(); it < polygons.end(); it++)
	{
		if (dynamic_cast<Model*>(*it) != NULL)
			dynamic_cast<Model*>(*it)->addRotation(degrees, axis);
	}

	rotate_vec.x += axis.x;
	rotate_vec.y += axis.y;
	rotate_vec.z += axis.z;
	rotate_angle += degrees;
}

//Method that updates the values of the x-y-z components of the scale vector used to calculate the model transformation matrix
void Model::addScale(glm::vec3 scale)
{
	for (std::vector<Polygon *>::iterator it = polygons.begin(); it < polygons.end(); it++)
	{
		if (dynamic_cast<Model*>(*it) != NULL)
			dynamic_cast<Model*>(*it)->addScale(scale);
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

//Method that updates the values of the x-y-z components of the translation vector used to calculate the model transformation matrix
void Model::addTranslation(glm::vec3 translate)
{
	for (std::vector<Polygon *>::iterator it = polygons.begin(); it < polygons.end(); it++)
	{
		if (dynamic_cast<Model*>(*it) != NULL)
			dynamic_cast<Model*>(*it)->addTranslation(translate);
	}

	Model::translate_vec.x += translate.x;
	Model::translate_vec.y += translate.y;
	Model::translate_vec.z += translate.z;
}

//Method that updates the position of the model
void Model::Reposition(glm::vec3 position)
{
	Model::translate_vec.x = position.x;
	Model::translate_vec.y = position.y;
	Model::translate_vec.z = position.z;
}

//Method that returns the rotation matrix
glm::mat4 Model::getRotation() 
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(rotate_angle), rotate_vec);
}

//Method that returns the translation matrix
glm::mat4 Model::getTranslation() 
{

	return glm::translate(glm::mat4(1.0f), translate_vec);
}

//Method that returns the translation matrix
glm::mat4 Model::getReposition()
{
	return glm::translate(glm::mat4(1.0f), translate_vec);
}

//Method that returns the scale matrix
glm::mat4 Model::getScale() 
{
	return glm::scale(glm::mat4(1.0f), scale_vec);
}

//Method that calculates the transformation matrix of the model
glm::mat4 Model::getModelMatrix()
{
	if (rotate_vec.x == 0 && rotate_vec.y == 0 && rotate_vec.z == 0)
		return getTranslation() *  getScale();
	else
		return getTranslation() * getRotation() * getScale();
}

//Method that adds a polygon object to the list of polygons that this model is composed of
void Model::addPolygon(Polygon* poly) 
{
	poly->setBoolean(position, texture, color, normal);
	polygons.push_back(poly);
}

//Method that sets the position, texture and color components
void Model::setVertexController(bool position, bool texture, bool color, bool normal) 
{
	Model::position = position;
	Model::texture = texture;
	Model::color = color;
	Model::normal = normal;

	for (std::vector<Polygon *>::iterator it = polygons.begin(); it < polygons.end(); it++)
	{
		(**it).setVertexController(position, texture, color, normal);
	}

}

//Method that returns the sample vertex of the polygon list
Vertex Model::getSampleVertex() 
{
	return polygons.front()->getSampleVertex();
}

//Method that returns the vertex array float count
int Model::getVAFloatCount()
{
	vaComponentCount = 0;
	for (std::vector<Polygon *>::iterator it = polygons.begin(); it < polygons.end(); it++) 
	{
		vaComponentCount += (**it).getVAFloatCount();
	}
	return vaComponentCount;
}

//Method that applies the passed tranformation matrix to every polygon in the list
void Model::transform(glm::mat4 transmat)
{
	for (std::vector<Polygon *>::iterator it = polygons.begin(); it < polygons.end(); it++)
	{
		(**it).transform(transmat);
	}
}

//Method that retusn the vertex array byte size
int Model::getVAByteSize()
{
	vaByteSize = 0;
	for (std::vector<Polygon *>::iterator it = polygons.begin(); it < polygons.end(); it++)
	{
		vaByteSize += (**it).getVAByteSize();
	}

	return vaByteSize;
}

//Method that returns the vertex array count
int Model::getVAVertexCount() 
{
	int vertexCount = 0;
	for (std::vector<Polygon *>::iterator it = polygons.begin(); it < polygons.end(); it++)
	{
		vertexCount += (**it).getVAVertexCount();
	}
	return vertexCount;
}

//Method that returns the array of vertices that make each polygon
float* Model::getVertexArray()
{
	float* va = new float[getVAFloatCount()];
	int filled = 0;
	for (std::vector<Polygon*>::iterator it = polygons.begin(); it < polygons.end(); it++)
	{
		int vertexCount = (**it).getVAFloatCount();
		float* a = (**it).getVertexArray();
		std::copy(a, a + vertexCount, va + filled);
		filled += vertexCount;
	}
	return va;

}

//Method that returns the origin coordinate of a model
std::map<std::string, glm::vec3> Model::getMinMax()
{
	std::map<std::string, glm::vec3> map;
	map["min"] = glm::vec3(0.0f);
	map["max"] = glm::vec3(0.0f);
	for (std::vector<Polygon*>::iterator it = polygons.begin(); it < polygons.end(); it++)
	{
		std::map<std::string, glm::vec3> temp = (**it).getMinMax();
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
	return map;
}

//Method that returns the vertex byte size
int Model::getVertexByteSize() 
{
	return polygons.front()->getVertexByteSize();
}

//Method that translates the model to its origin
void Model::translateToOrigin()
{
	std::map<std::string, glm::vec3> map;
	map = getMinMax();

	glm::vec3 temp;
	temp.x = -(map["min"].x + map["max"].x) / 2;
	temp.y = -(map["min"].y + map["max"].y) / 2;
	temp.z = -(map["min"].z + map["max"].z) / 2;

	transform(glm::translate(glm::mat4(1.0f), temp));
}

void Model::draw(int mode, Shader* shaderProg)
{
	shaderProg->use();
	this->bind();
	if (textureIndex == -1)
	{
		shaderProg->setInt("fill", textureIndex);
	}
	else
	{
		g_textures[textureIndex].bind(g_texLocations[textureIndex]);
		shaderProg->setFloat("material.shininess", g_shininess[textureIndex]);
		shaderProg->setVec3("material.specular", g_specularStrength[textureIndex]);
		shaderProg->setInt("material.diffuse", textureIndex);
	}
	shaderProg->setMat4("model", this->getModelMatrix());
	GLCall(glDrawArrays(mode, 0, this->getVAVertexCount()));
}