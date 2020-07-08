#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "vertex.h"

class VertexController{

public: 
	std::vector<Vertex> vertices;

	VertexController(bool position = true, bool texture = false, bool color = false);
	VertexController(std::vector<Vertex> verts, bool position = true, bool texture = false);

	void appendVertex(Vertex& ver);

	int getVertexByteSize(Vertex vert);
	int getVertexFloatCount(Vertex vert);
	int getVAFloatCount();
	int getVAByteSize();
	int getVAVertexCount();

	float* getVertex(Vertex vert);
	float* getVertexArray();
	void transform(glm::mat4 transmat);
	void transformOne(glm::mat4 transmat, VertexComponent& vc);

	bool position;
	bool texture;
	bool color;

	

};