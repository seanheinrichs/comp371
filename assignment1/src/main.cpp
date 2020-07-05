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

#include "stb_image.h"	// For texture mapping (can remove once blocks don't have textures)
#include "Objects/geometry/Cube.h"
#include "Objects/geometry/Model.h"
#include "Objects/geometry/Polygon.h"
#include "Objects/Grid.hpp"

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
static Model * createSeansModel();

/* Global Constants */
const unsigned int WINDOW_WIDTH = 1024;
const unsigned int WINDOW_HEIGHT = 768;

/* Camera Setup */
glm::vec3 cameraPos = glm::vec3(0.0f, 0.2f, 2.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -2.0f);
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

	/* Models */

	// For the next person to add their model, we may want to use a VBO and VAO array (see Grid example)
	unsigned int VBO, VAO;
	GLCall(glGenVertexArrays(1, &VAO));
	GLCall(glGenBuffers(1, &VBO));

		// Sean's Model
		GLCall(glBindVertexArray(VAO));

		Model* m1 = createSeansModel();

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
		GLCall(glBufferData(GL_ARRAY_BUFFER, m1->getVAByteSize(), m1->getVertexArray(), GL_STATIC_DRAW));

		// Set Position
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0));
		GLCall(glEnableVertexAttribArray(0));
		
		// Set Textures
		GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));
		GLCall(glEnableVertexAttribArray(1));

	// Unbinding (safe)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/* Grid */

	Grid mainGrid = Grid();

	unsigned int grid_VAOs[2], grid_VBOs[2], grid_EBO;
	glGenVertexArrays(2, grid_VAOs);
	glGenBuffers(2, grid_VBOs);
	glGenBuffers(1, &grid_EBO);

		/* Grid Mesh */
		glBindVertexArray(grid_VAOs[0]);
		glBindBuffer(GL_ARRAY_BUFFER, grid_VBOs[0]);
		glBufferData(GL_ARRAY_BUFFER, mainGrid.meshVertices.size() * sizeof(glm::vec3), &mainGrid.meshVertices.front(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		/* Grid Floor */
		glBindVertexArray(grid_VAOs[1]);
		glBindBuffer(GL_ARRAY_BUFFER, grid_VBOs[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(mainGrid.floorVertices), mainGrid.floorVertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grid_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mainGrid.floorIndices), mainGrid.floorIndices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

	// Unbinding (safe)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/* Textures */ 

	// TEMPORARY CODE: I think at this point we should remove all of our texture "legacy" code
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

	// Uniform Declarations
	unsigned int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
	unsigned int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
	unsigned int projectionLoc = glGetUniformLocation(shaderProgram.ID, "projection");

	/* Setup Camera Projection */
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	shaderProgram.setMat4("projection", projection);

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

		// Handles camera views and transformations
		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		shaderProgram.setMat4("view", view);

		// Define model
		glm::mat4 model;

		// Draw Model 1 (Sean)
		GLCall(glBindVertexArray(VAO));			// Not sure how we are going to handle rendering, don't know if this is sustainable but here is how it currently works
			shaderProgram.setInt("fill", 2);                                    // Set Color or Textures with Uniform in Shader
			model = glm::mat4(1.0f);                                            // Use Identity Matrix to get rid of previous transformations
			model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));             // Make the model smaller with a scale function	
			model = glm::translate(model, glm::vec3(-22.0f, 0.0f, -22.0f));		// Move it to a corner
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));	// ??? All I know is that I need to call this or nothing works... Still trying to figure this out
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 612));							// Draw Call

		// Draw the Grid Mesh
		GLCall(glBindVertexArray(grid_VAOs[0]));
			shaderProgram.setInt("fill", 0);
			model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_LINES, 0, mainGrid.meshVertices.size());

		// Draw the Grid Floor
		GLCall(glBindVertexArray(grid_VAOs[1]));
			shaderProgram.setInt("fill", 1);
			model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0005f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap Buffers and Poll for Events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/* De-allocate resources */
	GLCall(glDeleteVertexArrays(1, &VAO));
	GLCall(glDeleteBuffers(1, &VBO));
	GLCall(glDeleteVertexArrays(1, grid_VAOs));
	GLCall(glDeleteBuffers(1, grid_VBOs));
	
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
	float cameraSpeed = 1.0 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

/* Static methods to create our Models */
static Model * createSeansModel()
{
	Cube * cb1 = new Cube(glm::vec3(0.0f, 0.5f, 0.0f));
	Cube * cb2 = new Cube(glm::vec3(0.0f, 1.5f, 0.0f));
	Cube * cb3 = new Cube(glm::vec3(0.0f, 2.5f, 0.0f));
	Cube * cb4 = new Cube(glm::vec3(0.0f, 3.5f, 0.0f));
	Cube * cb5 = new Cube(glm::vec3(1.0f, 1.5f, 0.0f));
	Cube * cb6 = new Cube(glm::vec3(1.0f, 3.5f, 0.0f));
	Cube * cb7 = new Cube(glm::vec3(2.0f, 0.5f, 0.0f));
	Cube * cb8 = new Cube(glm::vec3(2.0f, 1.5f, 0.0f));
	Cube * cb9 = new Cube(glm::vec3(2.0f, 2.5f, 0.0f));
	Cube * cb10 = new Cube(glm::vec3(2.0f, 3.5f, 0.0f));
	Cube * cb11 = new Cube(glm::vec3(4.0f, 2.5f, 0.0f));
	Cube * cb12 = new Cube(glm::vec3(4.0f, 3.5f, 0.0f));
	Cube * cb13 = new Cube(glm::vec3(5.0f, 3.5f, 0.0f));
	Cube * cb14 = new Cube(glm::vec3(6.0f, 3.5f, 0.0f));
	Cube * cb15 = new Cube(glm::vec3(6.0f, 2.5f, 0.0f));
	Cube * cb16 = new Cube(glm::vec3(6.0f, 1.5f, 0.0f));
	Cube * cb17 = new Cube(glm::vec3(6.0f, 0.5f, 0.0f));

	Model * seansModel = new Model();
	seansModel->addPolygon(cb1);
	seansModel->addPolygon(cb2);
	seansModel->addPolygon(cb3);
	seansModel->addPolygon(cb4);
	seansModel->addPolygon(cb5);
	seansModel->addPolygon(cb6);
	seansModel->addPolygon(cb7);
	seansModel->addPolygon(cb8);
	seansModel->addPolygon(cb9);
	seansModel->addPolygon(cb10);
	seansModel->addPolygon(cb11);
	seansModel->addPolygon(cb12);
	seansModel->addPolygon(cb13);
	seansModel->addPolygon(cb14);
	seansModel->addPolygon(cb15);
	seansModel->addPolygon(cb16);
	seansModel->addPolygon(cb17);

	return seansModel;
}