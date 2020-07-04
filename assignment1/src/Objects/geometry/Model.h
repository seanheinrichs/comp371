#pragma once
#include <vector>
#include <glm/glm.hpp>
class Polygon {};

class Model
{
public:
	std::vector<Polygon> polygons;
	void addPolygon(Polygon poly);

	float* getVertexArray();
	int getVAComponentCount();
	int getVAByteSize();


	glm::vec3 origin;
	int vaComponentCount;
	int vaByteSize;

};