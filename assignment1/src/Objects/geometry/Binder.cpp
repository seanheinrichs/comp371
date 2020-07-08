
#include "binder.h"
#include <iostream>
#include "../../Opengl_a/vertexComponent.h"
#include "../../Opengl_a/vertex.h"
#include "model.h"

/* Error Handling

The following functions are ripped from cherno's videos and we need to modify them

*/
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

#include <GL/glew.h>    

static void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[openGL error] (" << error << ") " << function <<
			" " << file << ":" << std::endl;
		return false;
	}
	return true;
}

Binder::Binder()
{
	Binder::position = true;
	Binder::texture = false;
	Binder::color = false;
}

Binder::Binder(bool position, bool texture, bool color)
{
	Binder::position = position;
	Binder::texture = texture;
	Binder::color = color;
}

void Binder::bindArrayBuffer(bool unbind, Model* model)
{

	bool* arr = new bool[3];
	arr[POSITION] = position;
	arr[TEXTURE] = texture;
	arr[COLOR] = color;

	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glGenBuffers(1, &vbo));

	GLCall(glBindVertexArray(vao));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));

	GLCall(glBufferData(GL_ARRAY_BUFFER, model->getVAByteSize(), model->getVertexArray(), GL_STATIC_DRAW));
	int vertexAttribCount = 0;
	int vertexByteOffset = 0;
	Vertex tempVert = model->getSampleVertex();
	for (std::vector<VertexComponent>::iterator it = tempVert.vertexComponents.begin(); it < tempVert.vertexComponents.end(); it++)
	{
		if (arr[(int)it->type]) 
		{
			std::cout << "BINDER: "  << std::endl;
			std::cout << "model->getVertexByteSize(): " << model->getVertexByteSize() << std::endl;
			std::cout << "it->getFloatCount() : " << it->getFloatCount() << std::endl;
			std::cout << "(void*)vertexByteOffset: " << (void*)0 << std::endl;
			std::cout << "getVertexByteSize: " << 3 * sizeof(float) << std::endl;

			GLCall(glVertexAttribPointer(vertexAttribCount, it->getFloatCount(), GL_FLOAT, GL_FALSE, model->getVertexByteSize(), (void*)0));
			GLCall(glEnableVertexAttribArray(0));
			vertexAttribCount += 1;
			vertexByteOffset += it->getByteSize();
		}
	}
	
	if (unbind)
		Binder::unbind();
}

void Binder::bind() 
{
	GLCall(glBindVertexArray(vao));
}

void Binder::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Binder::deallocate() 
{
	GLCall(glDeleteVertexArrays(1, &vao));
	GLCall(glDeleteBuffers(1, &vbo));
}