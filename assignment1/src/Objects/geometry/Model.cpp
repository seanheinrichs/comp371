/*
Model

Depends on: Polygon.h

Description: A container for groups of related geometry. It handles the creation of 
arbitrarily sized vertex arrays from the polgons that it contains.

TODO: Create API for one origin point for the entire polygon

origin: the point of origin for this particular polygon
vaComponentCount: the number of vertex components in the Polygons of the model
vaByteSize: the number Bytes required to contain the vertices of all the polygons in memory

*/

#pragma once


#include "Model.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>


Model::Model(bool position, bool texture, bool color)
{
	Model::position = position;
	Model::texture = texture;
	Model::color = color;
	origin = glm::vec3(0.f);
	//Model::binder = new Binder(position, texture, color);
	rotate_vec = glm::vec3(0.0f, 0.0f, 1.0f);
	translate_vec = glm::vec3(0.0f, 0.0f, 0.0f);
	scale_vec = glm::vec3(0.0f, 0.0f, 0.0f);
	rotate_angle = 0.0;
}

Model::Model() 
{
	Model::position = true;
	Model::texture = false;
	Model::color = false;
	origin = glm::vec3(0.f);
	rotate_vec = glm::vec3(0.0f, 0.0f, 0.0f);
	translate_vec_origin = translate_vec = glm::vec3(0.0f, 0.0f, 0.0f); //not sure if this is the best way to set up the translate_vec_origin
	scale_vec = glm::vec3(0.0f, 0.0f, 0.0f);
	rotate_angle = 0.0;
}

void Model::addTranslationOrigin(glm::vec3 translate)
{
	Model::translate_vec_origin.x = translate.x;
	Model::translate_vec_origin.y = translate.y;
	Model::translate_vec_origin.z = translate.z;
}

void Model::addRotation(float degrees, glm::vec3 axis) 
{
	rotate_vec.x += axis.x;
	rotate_vec.y += axis.y;
	rotate_vec.z += axis.z;
	rotate_angle += degrees;
}

void Model::addScale(glm::vec3 scale)
{
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

void Model::addTranslation(glm::vec3 translate)
{
	//std::cout << "translation updated" << std::endl;
	Model::translate_vec.x += translate.x;
	Model::translate_vec.y += translate.y;
	Model::translate_vec.z += translate.z;
}

void Model::printTranslate()
{
	//std::cout << "translation updated" << std::endl;
	std::cout << "x:"<< Model::translate_vec.x << std::endl;
	std::cout << "y:"<< Model::translate_vec.y << std::endl;
	std::cout << "z:"<< Model::translate_vec.z << std::endl;
}

glm::mat4 Model::getRotation() 
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(rotate_angle), rotate_vec);

	//an attempt, maybe not placed in the right method
	//missing the point translation step from the model to rotate around itself
	//1. translate to center of model
	//2. rotate
	//3. translate back to origin 
	return
	getTranslation() *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotate_angle), rotate_vec) *
			glm::translate(glm::mat4(1.0f), glm::vec3(-translate_vec_origin.x, -translate_vec_origin.y, translate_vec_origin.z));
}


glm::mat4 Model::getTranslation() 
{
	return glm::translate(glm::mat4(1.0f), translate_vec);
}

glm::mat4 Model::getTranslationOrigin()
{
	return glm::translate(glm::mat4(1.0f), translate_vec_origin);
}

glm::mat4 Model::getScale() 
{
	return glm::scale(glm::mat4(1.0f), scale_vec);
}

glm::mat4 Model::getModelMatrix()
{
	if (rotate_vec.x == 0 && rotate_vec.y == 0 && rotate_vec.z == 0)
		return getTranslation() *  getScale();
	else
		return getTranslation() * getRotation() * getScale();
}


void Model::addPolygon(Polygon* poly) 
{
	poly->setVertexController(position, texture, color);
	polygons.push_back(poly);
}

void Model::setVertexController(bool position, bool texture, bool color) 
{
	Model::position = position;
	Model::texture = texture;
	Model::color = color;
}

Vertex Model::getSampleVertex() 
{
	return polygons.front()->getSampleVertex();
}


int Model::getVAFloatCount()
{
	vaComponentCount = 0;
	for (std::vector<Polygon *>::iterator it = polygons.begin(); it < polygons.end(); it++) 
	{
		vaComponentCount += (**it).getVAFloatCount();
	}
	return vaComponentCount;
}

void Model::transform(glm::mat4 transmat)
{
	for (std::vector<Polygon *>::iterator it = polygons.begin(); it < polygons.end(); it++)
	{
		(**it).transform(transmat);
	}
}

int Model::getVAByteSize()
{
	vaByteSize = 0;
	for (std::vector<Polygon *>::iterator it = polygons.begin(); it < polygons.end(); it++)
	{
		vaByteSize += (**it).getVAByteSize();
	}
	return vaByteSize;
}

int Model::getVAVertexCount() 
{
	int vertexCount = 0;
	for (std::vector<Polygon *>::iterator it = polygons.begin(); it < polygons.end(); it++)
	{
		vertexCount += (**it).getVAVertexCount();
	}
	return vertexCount;
}

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

int Model::getVertexByteSize() 
{
	return polygons.front()->getVertexByteSize();
}

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