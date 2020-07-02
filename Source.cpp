//
// COMP 371 Assignment Framework
//


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL

#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
						// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language

#define GLFW_REFRESH_RATE 60
#define	GLFW_DOUBLEBUFFER GLFW_TRUE
#define GLFW_CONTEXT_VERSON_MAJOR 3
#define GLFW_CONTEXT_VERSION_MINOR 3
#define GLFW_OPENGL_PROFILE GLFW_OPENGL_CORE_PROFILE

#define ASSERT(x) if (!(x)) __debugbreak();

#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};


static ShaderProgramSource ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};


	std::string line;
	std::stringstream ss[2];

	ShaderType type = ShaderType::NONE;


	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
			else if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
		}
		else {
			ss[(int)type] << line << "\n";
		}


	}

	return { ss[0].str(), ss[1].str() };

}

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




static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;

	}

	return id;


}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;

}




int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSON_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	/* get monitors */
	//int count;
	//GLFWmonitor** monitors = glfwGetMonitors(&count);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1080, 1080, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "error" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	float positions[12] = {
	   -0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f
	};

	unsigned int indices[] = {
		0,1,2,
		2,3,0
	};

	unsigned int vao;
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	unsigned int buffer;

	// The below function allows users to retrieve the id of the buffer that open gl creates through the buffer variable that is passed
	GLCall(glGenBuffers(1, &buffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
	GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));


	unsigned int ibo;

	// The below function allows users to retrieve the id of the buffer that open gl creates through the buffer variable that is passed
	GLCall(glGenBuffers(1, &ibo));
	// NOW we have created a buffer, we can immediately fill it with data or fill it later
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));


	ShaderProgramSource source = ParseShader("basic.shader");

	std::cout << source.FragmentSource << std::endl;
	std::cout << source.VertexSource << std::endl;

	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);

	GLCall(glUseProgram(shader));

	int location = glGetUniformLocation(shader, "u_Color");
	ASSERT(location != -1);
	GLCall(glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f));

	GLCall(glBindVertexArray(0));
	GLCall(glUseProgram(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));


	float r = 0.0f;
	float increment = 0.05f;



	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		glClearColor(
			0.0,
			0.0,
			0.0,
			0.0
		);

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// there are two ways to draw what you have put into the actual buffer
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		GLCall(glUseProgram(shader));

		GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));

		GLCall(glBindVertexArray(vao));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));

		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		if (r > 1.0f)
			increment = -0.05f;
		else if (r < 0.0f)
			increment = 0.05f;

		r += increment;

		// another way to display would be glDrawElements

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}











