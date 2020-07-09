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


Model::Model(bool position, bool texture, bool color)
{
	Model::position = position;
	Model::texture = texture;
	Model::color = color;
	origin = glm::vec3(0.f);
	//Model::binder = new Binder(position, texture, color);
}

/*
void Model::bindArrayBuffer(bool unbind)
{
	(*this->binder).bindArrayBuffer(unbind, this);
}

void Model::bind()
{
	binder->bind();
}
void Model::unbind()
{
	binder->unbind();
}
*/
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