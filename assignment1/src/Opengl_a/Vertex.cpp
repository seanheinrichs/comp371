#include "Vertex.h"

Vertex::Vertex(glm::vec3 pos, glm::vec2 tex)
{
	// constructor for the vertex class
	position = pos;
	texture = tex;
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