#include "ObjParser.h"

ObjParser::ObjParser()
{
}


ObjParser::~ObjParser()
{
}

void ObjParser::setupVC(
	std::vector<glm::vec3> & in_vertices,
	std::vector<glm::vec2> & in_uvs,
	std::vector<glm::vec3> & in_normals)
{
	for (int i = 0; i < in_vertices.size(); i++)
	{
		VertexController * vc = new VertexController(true, false, false);
		Vertex v;
		v.addVertexComponent(VertexComponent(POSITION, in_vertices.at(i)));
		v.addVertexComponent(VertexComponent(NORMAL, in_normals.at(i)));
	}

	//vc = new VertexController(true, false, false);

	// a -> model's back faces
	//Vertex a1;
	//a1.addVertexComponent(VertexComponent(POSITION, glm::vec3(-0.5f, -0.5f, -0.5f)));
	//a1.addVertexComponent(VertexComponent(TEXTURE, glm::vec2(0.0f, 0.0f)));


	//vc->appendVertex(a3);
	//vc->appendVertex(a2);
}