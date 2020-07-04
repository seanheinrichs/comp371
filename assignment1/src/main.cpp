/*
	COMP 371 - Section CC
	Practical Assignment #1
	Written By:
		Benjamin Therien (40034572)
		Sean Heinrichs (40075789)
		Wayne St Amand (Add your SN# when you make a commit)
		Isabelle Gourchette (Add your SN# when you make a commit)
		Ziming Wang (Add your SN# when you make a commit)
	Due:  July 9th, 2020
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#define STB_IMAGE_IMPLEMENTATION


#include "stb_image.h"	// For texture mapping (might be useful for the grid?)
#include "Objects/geometry/Cube.h"
#include "Objects/geometry/Model.h"
#include "Objects/geometry/Polygon.h"

#include <GL/glew.h>    
#include <GLFW/glfw3.h> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#define GLFW_REFRESH_RATE 60
#define	GLFW_DOUBLEBUFFER GLFW_TRUE

/* USED FOR DEBUGGING - Every OpenGL function call we use should be wrapped in a GLCall() */
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

/* Function Declarations */
void processInput(GLFWwindow *window);

/* Global Constants */
const unsigned int WINDOW_WIDTH = 1024;
const unsigned int WINDOW_HEIGHT = 768;

/* Camera Setup */
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float deltaTime = 0.0f;
float lastFrame = 0.0f;

/* Error Handling 

The following functions are ripped from cherno's videos and we need to modify them

*/
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
#include <vector>
int main(void)
{
	

	
	/* Initialize GLFW */
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// TODO: Add double buffering support for the window
	// TODO: Use perspective view
	GLFWwindow* window;

	/* Create a window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "COMP 371 - Assignment 1", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Initialize GLEW */
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	/* Enable depth test for 3D rendering */
	GLCall(glEnable(GL_DEPTH_TEST));

	/* Build and Compile Shader Program */
	Shader shaderProgram("comp371/assignment1/src/Shaders/vertex.shader", "comp371/assignment1/src/Shaders/fragment.shader"); 

	

	// TEMPORARY CODE: Will be removed once Cube class is finalized 
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
	};

	// TEMPORARY CODE - Will be changed once we use Cube to render all alphanumeric objects
	unsigned int VBO, VAO;
	GLCall(glGenVertexArrays(1, &VAO));
	GLCall(glGenBuffers(1, &VBO));

	GLCall(glBindVertexArray(VAO));


	Cube cb1(glm::vec3(0.5f, 0.5f, -1.5f));
	//cb1.translate_fromOrigin();
	

	Cube cb2(glm::vec3(-0.5f, 0.5f, -1.0f));
	//cb2.translate_fromOrigin();

	Cube cb3(glm::vec3(-0.5f, -0.5f, -0.5f));
	//cb3.translate_fromOrigin();

	Cube cb4(glm::vec3(0.5f, -0.5f, -0.5f));
	//cb4.translate_fromOrigin();

	Cube cb5(glm::vec3(-0.5f, 1.0f, -1.0f));
	//cb5.translate_fromOrigin();

	Cube cb6(glm::vec3(-0.5f, 1.5f, -1.5f));
	//cb6.translate_fromOrigin();

	Model m1; 
	m1.addPolygon(&cb1);
	m1.addPolygon(&cb2);
	m1.addPolygon(&cb3);
	m1.addPolygon(&cb4);
	m1.addPolygon(&cb5);
	m1.addPolygon(&cb6);

	std::cout << "byte size " << m1.getVAByteSize() << std::endl;
	std::cout << "Component Count " << m1.getVAComponentCount() << std::endl;

	/*Setup basic translation*/

	glm::mat4 translation(1.0f);
	translation = glm::translate(translation, glm::vec3(0.0f, 0.0f, -2.0f));
	translation = glm::rotate(translation, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shaderProgram.setMat4("translation", translation);


	/*
	
	[THIS IS THE NEW LINE OF CODE]
	
	*/
	m1.transform(translation);




	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, m1.getVAByteSize(), m1.getVertexArray(), GL_STATIC_DRAW));

	// Set Position
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0));
	GLCall(glEnableVertexAttribArray(0));
	
	// Set Textures
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));
	GLCall(glEnableVertexAttribArray(1));

	/* Textures */ 

	// TEMPORARY CODE: Either to be removed or moved to grid class (depending on whether we are using textures)
	unsigned int texture;
	GLCall(glGenTextures(1, &texture));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture));

	// Set texture wrapping parameters
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	// Set texture filtering parameters
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	// Load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); 
	
	// Get image from resources folder
	unsigned char *data = stbi_load("comp371/assignment1/src/Resources/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	shaderProgram.use();
	shaderProgram.setInt("texture", 0);

	/* Setup Camera Projection */
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	shaderProgram.setMat4("projection", projection);


	

	int count = 1;

	/* Main Loop */
	while (!glfwWindowShouldClose(window))
	{

		// Set frame for Camera (taken from LearnOpenGL)
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Event Handling
		processInput(window);

		// Render
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		// Tectures
		// TEMPORARY CODE: Either to be removed or moved to grid class (depending on whether we are using textures)
		GLCall(glActiveTexture(GL_TEXTURE0));
		GLCall(glBindTexture(GL_TEXTURE_2D, texture));

		// Activate the shader
		shaderProgram.use();

		// Handles camera views and transformations
		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		shaderProgram.setMat4("view", view);

		//throw in a little translation
		//translation = glm::translate(translation, glm::vec3(0.0f, count * 0.1f, 0.0f));
		//shaderProgram.setMat4("translation", translation);

		// TEMPORARY CODE: Will be changed once Cube class is finalized 
		GLCall(glBindVertexArray(VAO));

			glm::mat4 model = glm::mat4(1.0f); // always start with initialize to identity matrix first
			model = glm::translate(model, cubePositions[0]);
			model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.3f, 0.5f));
			shaderProgram.setMat4("model", model);

			GLCall(glDrawArrays(GL_TRIANGLES, 0, 216));

		// Swap Buffers and Poll for Events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/* De-allocate resources */
	GLCall(glDeleteVertexArrays(1, &VAO));
	GLCall(glDeleteBuffers(1, &VBO));
	
	/* Terminate Program */
	glfwTerminate();
	return 0;
}

/* Import all event handling functions here */
void processInput(GLFWwindow *window)
{
	/* Example call */
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	// TODO: Change Camera to be dependent on Mouse Movements (as specified in the assignment)
	float cameraSpeed = 2.5 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}