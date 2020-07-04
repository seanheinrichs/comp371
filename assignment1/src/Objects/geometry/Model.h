#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Polygon.h"

class Model
{
public:
	std::vector<Polygon*> polygons;
	void addPolygon(Polygon* poly);
	Model();

	float* getVertexArray();
	int getVAComponentCount();
	int getVAByteSize();


	glm::vec3 origin;
	int vaComponentCount;
	int vaByteSize;

};