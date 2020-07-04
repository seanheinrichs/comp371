// Cube code will go here in actual PR
//#include "polygon.h"
/*
This is the cube class, it is meant to be the basis for any cube


*/


#include "Polygon.h"


class Cube : public Polygon{

	public:
		Cube(glm::vec3 origin_a);
		virtual void transform(glm::mat4 transmat);
		void translate_fromOrigin();
		void translate_tst();
		virtual float* getVertexArray();
		virtual int getVAComponentCount();
		virtual int getVAByteSize();
		

		glm::vec3 origin;
		int vaComponentCount;
		int vaByteSize;

		Vertex vertices[36] = {
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f),glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(0.5f,  0.5f, -0.5f),glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(0.5f,  0.5f, -0.5f),glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f, -0.5f),glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 0.0f)),

			Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(0.5f, -0.5f, 0.5f),glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(0.5f,  0.5f, 0.5f),glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(0.5f,  0.5f, 0.5f),glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f, 0.5f),glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),glm::vec2(0.0f, 0.0f)),

			Vertex(glm::vec3(-0.5f,  0.5f,  0.5f),glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f, -0.5f),glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f,  0.5f),glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f,  0.5f),glm::vec2(1.0f, 0.0f)),

			Vertex(glm::vec3(0.5f,  0.5f,  0.5f),glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(0.5f,  0.5f, -0.5f),glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(0.5f, -0.5f,  0.5f),glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(0.5f,  0.5f,  0.5f),glm::vec2(1.0f, 0.0f)),

			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f),glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(0.5f, -0.5f,  0.5f),glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(0.5f, -0.5f,  0.5f),glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f,  0.5f),glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 1.0f)),

			Vertex(glm::vec3(-0.5f,  0.5f, -0.5f),glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(0.5f,  0.5f, -0.5f),glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(0.5f,  0.5f,  0.5f),glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(0.5f,  0.5f,  0.5f),glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f,  0.5f),glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f, -0.5f),glm::vec2(0.0f, 1.0f))
		};
		


			/*
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

	
	*/

};
