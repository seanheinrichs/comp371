/*
	COMP 371 - Section CC
	Practical Assignment #1
	Written By:
		Benjamin Therien (40034572)
		Sean Heinrichs (40075789)
		Wayne St Amand (40074423)
		Isabelle Gourchette (40008121)
		Ziming Wang (40041601)
	Due:  July 9th, 2020
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#define STB_IMAGE_IMPLEMENTATION

#include "Objects/geometry/Polygon.h"
#include "Objects/Grid.hpp"
#include "Objects/Camera.h"
#include "OurModels.cpp"

#include <GL/glew.h>    
#include <GLFW/glfw3.h> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLFW_REFRESH_RATE 60
#define	GLFW_DOUBLEBUFFER GLFW_TRUE

/* USED FOR DEBUGGING - Every OpenGL function call we use should be wrapped in a GLCall() 

The following 20 lines of code were taken from this video: 
https://www.youtube.com/watch?v=FBbPWSOQ0-w&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=10

*/
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))


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

/* Function Declarations */
void processInput(GLFWwindow *window, Model** models);
void cursorPositionCallback(GLFWwindow * window, double xPos, double yPos);

/* Global Constants */
const unsigned int WINDOW_WIDTH = 1024;
const unsigned int WINDOW_HEIGHT = 768;

/* Camera Setup */
Camera camera = Camera(glm::vec3(0.0f, 0.3f, 2.0f), glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Initialize variables used for rotations
float previousXPos = WINDOW_WIDTH / 2.0f;
float previousYPos = WINDOW_HEIGHT / 2.0f;
float xOffset = 0.0f;
float yOffset = 0.0f;
float rX = 0.0f;
float rY = 0.0f;

//globals used for selecting render mode and models
GLenum MODE = GL_TRIANGLES;
int SELECTED;

int main(void)
{
	/* Initialize GLFW */
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	GLFWwindow* window;

	// Create a window and its OpenGL context 
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "COMP 371 - Assignment 1", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

	// Initialize GLEW 
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Enable depth test for 3D rendering 
	GLCall(glEnable(GL_DEPTH_TEST));

	//Enable Culling
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GL_FRONT));
	GLCall(glFrontFace(GL_CW));

	// Build and Compile Shader Program 
	Shader shaderProgram("comp371/assignment1/src/Shaders/vertex.shader", "comp371/assignment1/src/Shaders/fragment.shader");

	// [Models]

	Model * ben = new Model(true, false, false);
	createBensModel(ben);
	ben->bindArrayBuffer(true, ben);

	Model * sean = new Model(true, false, false);
	createSeansModel(sean);
	sean->bindArrayBuffer(true, sean);

	Model* wayne = new Model(true, false, false);
	createWaynesModel(wayne);
	wayne->bindArrayBuffer(true, wayne);

	Model* isa = new Model(true, false, false);
	createIsabellesModel(isa);
	isa->bindArrayBuffer(true, isa);

	Model* ziming = new Model(true, false, false);
	createZimingsModel(ziming);
	ziming->bindArrayBuffer(true, ziming);

	// [Grid]

	Grid mainGrid = Grid();

	unsigned int grid_VAOs[3], grid_VBOs[3], grid_EBO;
	GLCall(glGenVertexArrays(3, grid_VAOs));
	GLCall(glGenBuffers(3, grid_VBOs));
	GLCall(glGenBuffers(1, &grid_EBO));

	// [Grid Mesh] 
	GLCall(glBindVertexArray(grid_VAOs[0]));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, grid_VBOs[0]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, mainGrid.meshVertices.size() * sizeof(glm::vec3), &mainGrid.meshVertices.front(), GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	GLCall(glEnableVertexAttribArray(0));

	// [Grid Floor] 
	GLCall(glBindVertexArray(grid_VAOs[1]));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, grid_VBOs[1]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(mainGrid.floorVertices), mainGrid.floorVertices, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grid_EBO));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mainGrid.floorIndices), mainGrid.floorIndices, GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	GLCall(glEnableVertexAttribArray(0));

	// [Coordinate Axis]
	GLCall(glBindVertexArray(grid_VAOs[2]));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, grid_VBOs[2]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(mainGrid.axisVertices), mainGrid.axisVertices, GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));
	GLCall(glEnableVertexAttribArray(1));


	// Uniform Declarations
	unsigned int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
	unsigned int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
	unsigned int projectionLoc = glGetUniformLocation(shaderProgram.ID, "projection");

	Model** models = new Model*[5];
	models[0] = ben;
	models[1] = sean;
	models[2] = isa;
	models[3] = wayne;
	models[4] = ziming;

	SELECTED = -1;

	ben->translateToOrigin();
	sean->translateToOrigin();
	isa->translateToOrigin();
	wayne->translateToOrigin();
	ziming->translateToOrigin();
	
	ben->addTranslation(glm::vec3(0.0f, 0.0f, -1.0f));
	ben->addScale(glm::vec3(0.2f, 0.2f, 0.2f));
	
	sean->addTranslation(glm::vec3(3.5f, 0.0f, -4.0f));
	sean->addScale(glm::vec3(0.2f, 0.2f, 0.2f));

	wayne->addTranslation(glm::vec3(-4.5f, 0.0f, -4.0f));
	wayne->addScale(glm::vec3(0.2f, 0.2f, 0.2f));

	isa->addTranslation(glm::vec3(3.5f, 0.0f, 4.5f));
	isa->addScale(glm::vec3(0.2f, 0.2f, 0.2f));
	
	ziming->addTranslation(glm::vec3(-4.0f, 0.0f, 4.5f));
	ziming->addScale(glm::vec3(0.2f, 0.2f, 0.2f));
	
	shaderProgram.use();

	// Main Loop 
	while (!glfwWindowShouldClose(window))
	{
		// Set frame for Camera (taken from LearnOpenGL)
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Event Handling
		processInput(window, models);

		// Render
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		// Recompute Camera Pipeline
		glm::mat4 model;
		shaderProgram.setMat4("model", model);

		glm::mat4 projection = glm::perspective(glm::radians(camera.fieldOfViewAngle), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		shaderProgram.setMat4("projection", projection);

		glm::mat4 view = camera.calculateViewMatrix();
		view = glm::rotate(view, glm::radians(rX), glm::vec3(0.0f, 0.0f, -1.0f));
		view = glm::rotate(view, glm::radians(rY), glm::vec3(-1.0f, 0.0f, 0.0f));
		shaderProgram.setMat4("view", view);

		// [Models]

		ben->bind();
		shaderProgram.setInt("fill", 2);
		model = ben->getModelMatrix();
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));	
		GLCall(glDrawArrays(MODE, 0, ben->getVAVertexCount()));
		
		sean->bind();
		shaderProgram.setInt("fill", 2);                               
		model = sean->getModelMatrix();
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));	
		GLCall(glDrawArrays(MODE, 0, sean->getVAVertexCount()));
		
		wayne->bind();
		shaderProgram.setInt("fill", 2);                                   	
		model = wayne->getModelMatrix();
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));	
		GLCall(glDrawArrays(MODE, 0, wayne->getVAVertexCount()));

		isa->bind();
		shaderProgram.setInt("fill", 2);                                    
		model = isa->getModelMatrix();
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));	
		GLCall(glDrawArrays(MODE, 0, isa->getVAVertexCount()));
		
		ziming->bind();
		shaderProgram.setInt("fill", 2);                               
		model = ziming->getModelMatrix();
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));	// ??? All I know is that I need to call this or nothing works... Still trying to figure this out
		GLCall(glDrawArrays(MODE, 0, ziming->getVAVertexCount()));
		
		// [Grid Mesh]

		GLCall(glBindVertexArray(grid_VAOs[0]));
		shaderProgram.setInt("fill", 0);
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_LINES, 0, mainGrid.meshVertices.size());

		// [Grid Floor]

		GLCall(glBindVertexArray(grid_VAOs[1]));
		shaderProgram.setInt("fill", 1);
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0005f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// [Coordinate Axis]
		glLineWidth(5.0f);
		GLCall(glBindVertexArray(grid_VAOs[2]));
		shaderProgram.setInt("fill", 3);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.01f, 0.0f));
		GLCall(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)));
		glDrawArrays(GL_LINES, 0, 6);
		glLineWidth(1.0f);

		// Swap Buffers and Poll for Events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// De-allocate resources 
	ben->deallocate();
	sean->deallocate();
	wayne->deallocate();
	isa->deallocate();
	ziming->deallocate();

	// Terminate Program 
	glfwTerminate();
	return 0;
}

// Event handling functions
void processInput(GLFWwindow *window, Model** models)
{
	bool modified = false; //needed?
	float cameraSpeed = 1.0 * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{
		camera.moveForward(cameraSpeed);
	}

	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
	{
		camera.moveBackward(cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		camera.moveLeft(cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
	{
		camera.moveRight(cameraSpeed);
	}

	// Anti-clockwise rotation about the positive x-axis
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		rX += 0.5f;
	}

	// Anti-clockwise rotation about the negative x-axis 
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		rX -= 0.5f;
	}

	// Anti-clockwise rotation about the positive y-axis
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		rY -= 0.5f;
	}

	// Anti-clockwise rotation about the negative y-axis
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		rY += 0.5f;
	}

	// Reset to initial world position
	if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS)
	{
		rY = 0;
		rX = 0;
	}

	// Change rendering to points
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		MODE = GL_POINTS;
	}

	// Change rendering to lines
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		MODE = GL_LINES;
	}

	// Change rendering to triangles
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		MODE = GL_TRIANGLES;
	}


	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && (SELECTED != 0 ))
	{
		std::cout << "inside key 1" << std::endl;

			SELECTED = 0; //I removed the SELECTED = -1 because each time you press on a key it toggled between SELECTED = -1 and SELECTED = anyothernumber
						//for as long as the key was pressed down. Causing the model to not be selected sometimes 
			//depending on how long the key was pressed.

	}
	
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && (SELECTED != 1))
	{
			SELECTED = 1;
	}
	
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && (SELECTED != 2))
	{
			SELECTED = 2;
	}
	
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && (SELECTED != 3))
	{
			SELECTED = 3;
	}
	
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS && (SELECTED != 4))
	{
			SELECTED = 4;
	}

	//TRANSLATION
	//left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{	
		modified = true;
		if (SELECTED == -1) 
		{

		}
		else 
		{
			std::cout << "in specific:" << std::endl;
			models[SELECTED]->addTranslation(glm::vec3(-0.1f,0.0f,0.0f));
		}
	}

	//right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		modified = true;
		if (SELECTED == -1)
		{

		}
		else
		{
			models[SELECTED]->addTranslation(glm::vec3(0.1f, 0.0f, 0.0f));
		}
	}

	//up
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		modified = true;
		if (SELECTED == -1)
		{

		}
		else
		{
			models[SELECTED]->addTranslation(glm::vec3(0.0f, 0.1f, 0.0f));
		}
	}

	//down
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		modified = true;
		if (SELECTED == -1)
		{

		}
		else
		{
			models[SELECTED]->addTranslation(glm::vec3(0.0f, -0.1f, 0.0f));
		}
	}

	//ROTATION
	//rotate left 5 degrees about y axis
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		modified = true;
	
		if (SELECTED == -1)
		{

		}
		else
		{
			models[SELECTED]->addRotation(5.0f,glm::vec3(0.0f, -0.1f, 0.0f));
		}
	}


	//rotate right 5 degrees about y axis
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		modified = true;

		if (SELECTED == -1)
		{

		}
		else
		{
			models[SELECTED]->addRotation(-5.0f, glm::vec3(0.0f, -0.1f, 0.0f));
		}
	}

	//SCALE
	//up
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
	{
		modified = true;
	

		if (SELECTED == -1)
		{

		}
		else
		{
			models[SELECTED]->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
		}
	}

	//down
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{
	
		if (SELECTED == -1)
		{

		}
		else
		{
			models[SELECTED]->addScale(glm::vec3(-0.01f, -0.01f, -0.01f));
		}
	}
}

void cursorPositionCallback(GLFWwindow * window, double xPos, double yPos)
{
	const float SENSITIVITY = 0.05f;

	xOffset = xPos - previousXPos;
	yOffset = previousYPos - yPos;

	previousXPos = xPos;
	previousYPos = yPos;

	// Limit speed of camera movement
	xOffset *= SENSITIVITY;
	yOffset *= SENSITIVITY;

	// Pan camera when holding the right mouse button
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		camera.panCamera(xOffset);
	}

	// Tilt camera when holding the middle mouse button
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
	{
		camera.tiltCamera(yOffset);
	}

	// Zoom camera when holding the left mouse button
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		camera.zoomCamera(yOffset);
	}
}



