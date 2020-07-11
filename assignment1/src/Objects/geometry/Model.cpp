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
	rotate_vec = glm::vec3(0.0f, 0.0f, 1.0f);
	translate_vec = glm::vec3(0.0f, 0.0f, 0.0f);
	scale_vec = glm::vec3(0.0f, 0.0f, 0.0f);
	rotate_angle = 0.0;
}

void Model::addTranslationOrigin(glm::vec3 translate)
{
	Model::translate_vec_origin.x = translate.x;
	Model::translate_vec_origin.y = translate.y;
	Model::translate_vec_origin.z = translate.z;
}

void Model::addRotation(float radians, glm::vec3 axis) 
{
	rotate_vec.x += axis.x;
	rotate_vec.y += axis.y;
	rotate_vec.z += axis.z;
	rotate_angle += radians;


}

void Model::addScale(glm::vec3 scale)
{
	scale_vec.x += scale.x;
	scale_vec.y += scale.y;
	scale_vec.z += scale.z;
}

void Model::addTranslation(glm::vec3 translate)
{
	std::cout << "translation updated" << std::endl;
	Model::translate_vec.x += translate.x;
	Model::translate_vec.y += translate.y;
	Model::translate_vec.z += translate.z;
}

void Model::printTranslate()
{
	std::cout << "translation updated" << std::endl;
	std::cout << "x:"<< Model::translate_vec.x << std::endl;
	std::cout << "y:"<< Model::translate_vec.y << std::endl;
	std::cout << "z:"<< Model::translate_vec.z << std::endl;
}

glm::mat4 Model::getRotation() 
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(rotate_angle), rotate_vec);
}


glm::mat4 Model::getTranslation() 
{
	return glm::translate(glm::mat4(1.0f), translate_vec);
}

glm::mat4 Model::getScale() 
{
	return glm::scale(glm::mat4(1.0f), scale_vec);
}

glm::mat4 Model::getModelMatrix()
{
	return getTranslation()  * getScale() * getRotation();
	//translate X scale X rotate
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

int Model::getVertexByteSize() 
{
	return polygons.front()->getVertexByteSize();
}