#pragma once

#include "Model.h"
#include "Polygon.h"


void Model::addPolygon(Polygon poly) 
{
	polygons.push_back(poly);
}



int Model::getVAComponentCount()
{
	int totalComponents = 0;
	for (std::vector<Polygon>::iterator it = polygons.begin(); it < polygons.end(); it++) 
	{
		totalComponents += it->getVAComponentCount();
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
	for (std::vector<Polygon>::iterator it = polygons.begin(); it < polygons.end(); it++)
	{
		float* a = it->getVertices();
		int vertexCount = it->getVAComponentCount();
		std::copy(a, a + vertexCount, va + filled);
		filled += vertexCount;
	}
	return va;

}