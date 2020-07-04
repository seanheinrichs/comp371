//to be cube

#include<iostream>
#include <GL/glew.h>    
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cube{

public: 
	glm::vec3 origin;

	Cube(glm::vec3 origin_a)
	{
		origin = origin_a;
		std::cout << "here" << std::endl;
	}

	void translate_tst()
	{
		glm::mat4 translation(1.0f);
		translation = glm::translate(translation, glm::vec3(0.0 + origin.x, 0.0 + origin.y, 0.0 + origin.z));
		glm::vec4 m(1.0f, 1.0f, 1.0f, 1.0f);
		m = translation * m;
		std::cout<< "x: " << m.x << std::endl;
		std::cout << "y: " << m.y << std::endl;
		std::cout << "z: " << m.z << std::endl;
	}

	float vertices[180] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	void translate(glm::mat4 translation)
	{
		for (int x = 0; x < 180; x += 5)
		{
			glm::vec4 m(
				Cube::vertices[x],
				Cube::vertices[x + 1],
				Cube::vertices[x + 2],
				1.0f);
			m = translation * m;
			Cube::vertices[x] = m.x;
			Cube::vertices[x + 1] = m.y;
			Cube::vertices[x + 2] = m.z;
		}
	}

	void translate_fromOrigin()
	{

		glm::mat4 translation(1.0f);
		translation = glm::translate(translation, glm::vec3(0.0 + origin.x, 0.0 + origin.y, 0.0 + origin.z));




		for (int x = 0; x < 180; x += 5)
		{
			glm::vec4 m(
				Cube::vertices[x],
				Cube::vertices[x + 1],
				Cube::vertices[x + 2],
				1.0f);
			m = translation * m;
			Cube::vertices[x] = m.x;
			Cube::vertices[x + 1] = m.y;
			Cube::vertices[x + 2] = m.z;
		}
	}


};