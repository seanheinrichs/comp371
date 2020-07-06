/*
Cube

Depends on: Polygon.h

Description: A 3d cube that forms the basis for amy cubes  we may want to construct in the future


origin: the point of origin for this particular polygon
vaComponentCount: the number of vertex components in this Cube 
vaByteSize: the number Bytes required to contain the vertices of this cube
*/



#include "Polygon.h"

class VertexComponent;

#include "../../Opengl_a/VertexController.h"

class Cube : public Polygon{

	public:
		Cube(glm::vec3 origin_a);
		virtual void transform(glm::mat4 transmat);
		void translate_fromOrigin();
		virtual float* getVertexArray();
		virtual int getVAVertexCount();
		virtual int getVAByteSize();
		virtual int getVAFloatCount();
		

		glm::vec3 origin;
		int vaComponentCount;
		int vaByteSize;

		void setupVC();

		VertexController* vc;

		/*
		Vertex vertices[36] = {

			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),

			Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(0.5f, -0.5f, 0.5f),  glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(0.5f,  0.5f, 0.5f),  glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(0.5f,  0.5f, 0.5f),  glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f, 0.5f),  glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec2(0.0f, 0.0f)),

			Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),

			Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),

			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),

			Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f))
		};
		*/

		/*
		Vertex vertices[36] = {
			                  
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),

			Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3( 0.5f, -0.5f, 0.5f),  glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3( 0.5f,  0.5f, 0.5f),  glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3( 0.5f,  0.5f, 0.5f),  glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f, 0.5f),  glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec2(0.0f, 0.0f)),

			Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),

			Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),

			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),

			Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f))
		};

		*/
		
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
