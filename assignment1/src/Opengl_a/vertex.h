#pragma once


#include "../Shaders/Shader.h"


class Vertex 
{

public:
	glm::vec3 position;
	glm::vec2 texture;

	Vertex(glm::vec3 pos, glm::vec2 tex);
	float* getVertex();
	int getByteSize();
	int getComponentCount();
	void setPosition(glm::vec3 pos);
	void setTexture(glm::vec2 tex);

};
