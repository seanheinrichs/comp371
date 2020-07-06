/*
This is the vertex class

Description: it abstracts away the concept of an openGL vertex,
allowing for future additions of components without compromising the API

Note: This is the class that should be modified to allow access to a varied number of parameters for our vertices.

position: a 3 component vector that holds the postiions of the vertex -- will be changed to vec4 in the future
texture: a 2 component vextor that holds the texture of the vertex

*/

#include "Vertex.h"

Vertex::Vertex(glm::vec3 pos, glm::vec2 tex)
{
	// constructor for the vertex class
	position = pos;
	texture = tex;
}

Vertex::Vertex() {}

void Vertex::addVertexComponent(VertexComponent vc) 
{
	vertexComponents.push_back(vc);
}





int Vertex::getByteSize()
{
	//this method is hardcoded for the time being
	//it should eventually be replaced by some code that retrieve the byte size automatically

	return 5 * sizeof(float);

}
int Vertex::getComponentCount()
{
	//this method is hardcoded for the time being
	//it should eventually be replaced by some code that retrieve the component count automatically
	return 5;
}

void Vertex::setPosition(glm::vec3 pos)
{
	position = pos;
}

void Vertex::setTexture(glm::vec2 tex)
{
	texture = tex;
}

float* Vertex::getVertex()
{
	float* verts = new float[5]; 
	verts[0] = position.x;
	verts[1] = position.y;
	verts[2] = position.z;
	verts[3] = texture.x;
	verts[4] = texture.y;
	return verts;
}