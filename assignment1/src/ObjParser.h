#pragma once
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <../../A1/comp371/assignment1/src/Opengl_a/VertexComponent.h>
#include <../../A1/comp371/assignment1/src/Opengl_a/VertexController.h>

class ObjParser
{
public:
	ObjParser();
	~ObjParser();

	void setupVC(
		std::vector<glm::vec3> & in_vertices,
		std::vector<glm::vec2> & in_uvs,
		std::vector<glm::vec3> & in_normals);


};

