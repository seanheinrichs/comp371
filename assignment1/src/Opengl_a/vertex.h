/*
This is the vertex class

Description: it abstracts away the concept of an openGL vertex, 
allowing for future additions of components without compromising the API

Note: This is the class that should be modified to allow access to a varied number of parameters for our vertices. 

position: a 3 component vector that holds the postiions of the vertex -- will be changed to vec4 in the future
texture: a 2 component vextor that holds the texture of the vertex

*/


#pragma once


#include "../Shaders/Shader.h"
#include <vector>
#include "vertexComponent.h"

class Vertex 
{

public:
	glm::vec3 position;
	glm::vec2 texture;
	std::vector<VertexComponent> vertexComponents;
	Vertex();


	void addVertexComponent(VertexComponent vc);


	Vertex(glm::vec3 pos, glm::vec2 tex);
	float* getVertex();
	int getByteSize();
	int getComponentCount();
	void setPosition(glm::vec3 pos);
	void setTexture(glm::vec2 tex);

};
