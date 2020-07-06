/*
Model

Depends on: Polygon.h

Description: A container for groups of related geometry. It handles the creation of
arbitrarily sized vertex arrays from the polygons that it contains.

TODO: Create API for one origin point for the entire polygon

origin: the point of origin for this particular polygon
vaComponentCount: the number of vertex components in the Polygons of the model
vaByteSize: the number Bytes required to contain the vertices of all the polygons in memory 

*/

#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Polygon.h"

class Model : Polygon
{
public:
	virtual void transform(glm::mat4 transmat);
	std::vector<Polygon*> polygons;
	void addPolygon(Polygon* poly);
	Model();

	virtual float* getVertexArray();
	virtual int getVAFloatCount();
	virtual int getVAByteSize();
	virtual int getVAVertexCount();


	glm::vec3 origin;
	int vaComponentCount;
	int vaByteSize;

};