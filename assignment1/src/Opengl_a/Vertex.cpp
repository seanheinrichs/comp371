#include "Vertex.h"


Vertex::Vertex() {}

/*
*
*Description: adds a vertex component
*
*/
void Vertex::addVertexComponent(VertexComponent vc) 
{
	vertexComponents.push_back(vc);
}


/*
*
*Description: returns a string representing the vertex objects from the file
*
*/
std::string Vertex::toString() 
{
	std::string s;
	for (std::vector<VertexComponent>::iterator it = vertexComponents.begin(); it < vertexComponents.end(); it++) {
		s += (*it).toString();
		s += " ";
	}
	return s;
}


