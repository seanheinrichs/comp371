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


Model::Model()
{
	origin = glm::vec3(0.f);
}

void Model::addPolygon(Polygon* poly) 
{
	polygons.push_back(poly);
}

int Model::getVAComponentCount()
{
	int totalComponents = 0;
	for (std::vector<Polygon *>::iterator it = polygons.begin(); it < polygons.end(); it++) 
	{
		totalComponents += (**it).getVAComponentCount();
	}
	vaComponentCount = totalComponents;
	return vaComponentCount;
}

int Model::getVAByteSize()
{
	vaByteSize = getVAComponentCount() * sizeof(float);
	return vaByteSize;
}

float* Model::getVertexArray()
{
	float* va = new float[getVAComponentCount()];
	int filled = 0;
	for (std::vector<Polygon*>::iterator it = polygons.begin(); it < polygons.end(); it++)
	{
		int vertexCount = (**it).getVAComponentCount();
		float* a = (**it).getVertexArray();
		std::copy(a, a + vertexCount, va + filled);
		filled += vertexCount;
		std::cout << "filled: " << filled << std::endl;
	}
	return va;

}