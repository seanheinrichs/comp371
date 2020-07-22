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
void setModelColor(int modelIndex, Shader * modelShader);
float RandomFloat(float a, float b);

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

// Lighting Locations
glm::vec3 bensLightPos(0.0f, 3.0f, 5.0f);

//globals used for selecting render mode and models
GLenum MODE = GL_TRIANGLES;
int selected = 0;

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

	// Build and Compile Shader Program (set defaults)
	Shader modelShader("comp371/assignment1/src/Shaders/modelShader.vertex", "comp371/assignment1/src/Shaders/modelShader.fragment");
	Shader lightShader("comp371/assignment1/src/Shaders/lightShader.vertex", "comp371/assignment1/src/Shaders/lightShader.fragment");

	// [Models]

	Model* ben = new Model(true, false, false, true);
	createBensModel(ben);
	ben->bindArrayBuffer(true, ben);

	Model* sean = new Model(true, false, false, true);
	createSeansModel(sean);
	sean->bindArrayBuffer(true, sean);

	Model* wayne = new Model(true, false, false, true);
	createWaynesModel(wayne);
	wayne->bindArrayBuffer(true, wayne);

	Model* isa = new Model(true, false, false, true);
	createIsabellesModel(isa);
	isa->bindArrayBuffer(true, isa);

	Model* ziming = new Model(true, false, false, true);
	createZimingsModel(ziming);
	ziming->bindArrayBuffer(true, ziming);

	Model* light = new Model(true, false, false, true);
	createLightModel(light);
	light->bindArrayBuffer(true, light);

	// [Grid]

	Grid mainGrid = Grid();

	unsigned int grid_VAOs[3], grid_VBOs[3], grid_EBO;
	GLCall(glGenVertexArrays(3, grid_VAOs));
	GLCall(glGenBuffers(3, grid_VBOs));
	GLCall(glGenBuffers(1, &grid_EBO));

	// [Grid Mesh] 
	//GLCall(glBindVertexArray(grid_VAOs[0]));
	//GLCall(glBindBuffer(GL_ARRAY_BUFFER, grid_VBOs[0]));
	//GLCall(glBufferData(GL_ARRAY_BUFFER, mainGrid.meshVertices.size() * sizeof(glm::vec3), &mainGrid.meshVertices.front(), GL_STATIC_DRAW));
	//GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	//GLCall(glEnableVertexAttribArray(0));

	// [Grid Floor] 
	GLCall(glBindVertexArray(grid_VAOs[1]));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, grid_VBOs[1]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(mainGrid.floorVertices), mainGrid.floorVertices, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grid_EBO));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mainGrid.floorIndices), mainGrid.floorIndices, GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));
	GLCall(glEnableVertexAttribArray(1));

	// [Coordinate Axis]
	GLCall(glBindVertexArray(grid_VAOs[2]));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, grid_VBOs[2]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(mainGrid.axisVertices), mainGrid.axisVertices, GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));
	GLCall(glEnableVertexAttribArray(1));

	Model** models = new Model*[5];
	models[0] = ben;
	models[1] = sean;
	models[2] = isa;
	models[3] = ziming;
	models[4] = wayne;

	ben->translateToOrigin();
	sean->translateToOrigin();
	isa->translateToOrigin();
	wayne->translateToOrigin();
	ziming->translateToOrigin();
	light->translateToOrigin();
	
	ben->addScale(glm::vec3(0.2f, 0.2f, 0.2f));
	ben->addTranslation(glm::vec3(0.0f, 0.0f, -1.0f));
	
	sean->addScale(glm::vec3(0.2f, 0.2f, 0.2f));
	sean->addTranslation(glm::vec3(3.5f, 0.0f, -4.0f));

	wayne->addScale(glm::vec3(0.2f, 0.2f, 0.2f));
	wayne->addTranslation(glm::vec3(-4.0f, 0.0f, -4.0f));

	isa->addScale(glm::vec3(0.2f, 0.2f, 0.2f));
	isa->addTranslation(glm::vec3(3.5f, 0.0f, 4.0f));
	
	ziming->addScale(glm::vec3(0.2f, 0.2f, 0.2f));
	ziming->addTranslation(glm::vec3(-4.0f, 0.0f, 4.0f));

	light->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
	light->addTranslation(bensLightPos);

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

		// Start Using Model Shader
		modelShader.use();
		modelShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		modelShader.setVec3("lightPos", bensLightPos);
		modelShader.setVec3("viewPos", camera.position);

		// Recompute Camera Pipeline
		glm::mat4 model;
		modelShader.setMat4("model", model);

		glm::mat4 projection = glm::perspective(glm::radians(camera.fieldOfViewAngle), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		modelShader.setMat4("projection", projection);

		glm::mat4 view = camera.calculateViewMatrix();
		view = glm::rotate(view, glm::radians(rX), glm::vec3(0.0f, 0.0f, -1.0f));
		view = glm::rotate(view, glm::radians(rY), glm::vec3(-1.0f, 0.0f, 0.0f));
		modelShader.setMat4("view", view);

		// [Models]

		ben->bind();
		setModelColor(0, &modelShader);
		model = ben->getModelMatrix();
		modelShader.setMat4("model", model);
		GLCall(glDrawArrays(MODE, 0, ben->getVAVertexCount()));

		sean->bind();
		setModelColor(1, &modelShader);
		model = sean->getModelMatrix();
		modelShader.setMat4("model", model);
		GLCall(glDrawArrays(MODE, 0, sean->getVAVertexCount()));
		
		isa->bind();
		setModelColor(2, &modelShader);
		model = isa->getModelMatrix();
		modelShader.setMat4("model", model);
		GLCall(glDrawArrays(MODE, 0, isa->getVAVertexCount()));
		
		ziming->bind();
		setModelColor(3, &modelShader);
		model = ziming->getModelMatrix();
		modelShader.setMat4("model", model);;
		GLCall(glDrawArrays(MODE, 0, ziming->getVAVertexCount()));
		
		wayne->bind();
		setModelColor(4, &modelShader);
		model = wayne->getModelMatrix();
		modelShader.setMat4("model", model);
		GLCall(glDrawArrays(MODE, 0, wayne->getVAVertexCount() ));
		
		// [Grid Mesh]
		
		GLCall(glBindVertexArray(grid_VAOs[0]));
		modelShader.setVec3("modelColor", 1.0f, 1.0f, 0.0f);
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		modelShader.setMat4("model", model);
		glDrawArrays(GL_LINES, 0, mainGrid.meshVertices.size());

		// [Grid Floor]
		
		GLCall(glBindVertexArray(grid_VAOs[1]));
		modelShader.setVec3("modelColor", 0.2f, 0.3f, 0.3f);
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0005f));
		modelShader.setMat4("model", model);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		// [Objects Not Affected by Light Source]

		// Start Using Lighting Shader
		lightShader.use();
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("view", view);

		// [Coordinate Axis]
		glLineWidth(5.0f);
		GLCall(glBindVertexArray(grid_VAOs[2]));
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.05f, 0.0f));
		lightShader.setMat4("model", model);
		lightShader.setInt("fill", 0);
		glDrawArrays(GL_LINES, 0, 6);
		glLineWidth(1.0f);

		model = glm::mat4(1.0f);
		light->bind();
		model = light->getModelMatrix();
		lightShader.setMat4("model", model);
		lightShader.setInt("fill", -1);
		GLCall(glDrawArrays(GL_TRIANGLES, 0, light->getVAVertexCount()));

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
	light->deallocate();

	// Terminate Program 
	glfwTerminate();
	return 0;
}

void setModelColor(int modelIndex, Shader* modelShader)
{
	selected == modelIndex ? modelShader->setVec3("modelColor", 0.6f, 0.0f, 0.8f) : modelShader->setVec3("modelColor", 0.75f, 0.75f, 0.75f);
}

// Event handling functions
void processInput(GLFWwindow *window, Model** models)
{

	float cameraSpeed = 1.0 * deltaTime;

	// [Camera FPS Movement]

	// Press "G" to move FORWARD
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{
		camera.moveForward(cameraSpeed);
	}

	// Press "V" to move BACKWARDS
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
	{
		camera.moveBackward(cameraSpeed);
	}

	// Press "C" to move LEFT
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		camera.moveLeft(cameraSpeed);
	}

	// // Press "B" to move RIGHT
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
	{
		camera.moveRight(cameraSpeed);
	}

	// [World Rotation]

	// Press "LEFT ARROW" to rotate about the positive x-axis in a anti-clockwise direction
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		rX += 0.5f;
	}

	// Press "RIGHT ARROW" to rotate about the negative x-axis in a anti-clockwise direction
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		rX -= 0.5f;
	}

	// Press "UP ARROW" to rotate about the positive y-axis in a anti-clockwise direction
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		rY -= 0.5f;
	}

	// Press "DOWN ARROW" to rotate about the negative y-axis in a anti-clockwise direction
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		rY += 0.5f;
	}

	// Press "HOME" to reset to initial world position
	if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS)
	{
		rY = 0;
		rX = 0;
	}

	// [Render Mode]

	// Press "SHIFT + P" to change rendering to POINTS
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		MODE = GL_POINTS;
	}

	// Press "SHIFT + L" to change rendering to LINES
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		MODE = GL_LINES;
	}

	// Press "SHIFT + T" to change rendering to TRIANGLES
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		MODE = GL_TRIANGLES;
	}

	// [Model Selection]

	// Press "1" to select MODEL 0 (N 3)
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && (selected != 0 ))
	{
		selected = 0;
	}
	
	// Press "2" to select MODEL 1 (A 7)
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && (selected != 1))
	{
		selected = 1;
	}
	
	// Press "3" to select MODEL 2 (A 0)
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && (selected != 2))
	{
		selected = 2;
	}
	
	// Press "4" to select MODEL 3 (M 4)
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && (selected != 3))
	{
		selected = 3;
	}
	
	// Press "5" to select MODEL 4 (Y 7)
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS && (selected != 4))
	{
		selected = 4;
	}

	// [Translation]
	
	// Press "SHIFT + A" to move the selected model to the LEFT
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{	
		models[selected]->addTranslation(glm::vec3(-0.1f,0.0f,0.0f));
	}

	// Press "SHIFT + D" to move the selected model to the RIGHT
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		models[selected]->addTranslation(glm::vec3(0.1f, 0.0f, 0.0f));
	}

	// Press "SHIFT + W" to move the selected model UP
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		models[selected]->addTranslation(glm::vec3(0.0f, 0.1f, 0.0f));
	}

	// Press "SHIFT + S" to move the selected model DOWN
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		models[selected]->addTranslation(glm::vec3(0.0f, -0.1f, 0.0f));
	}

	// [Rotation]
	
	// Press 'A' to rotate the model to the left 5 degrees about y-axis
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		models[selected]->addRotation(5.0f,glm::vec3(0.0f, 1.0f, 0.0f));
	}

	// Press 'D' to rotate the model to the right 5 degrees about y-axis
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
	{
		models[selected]->addRotation(-5.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	// [Scale]
	
	// Press 'U' to scale UP the model
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
	{
		models[selected]->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
	}

	// Press 'J' to scale DOWN the model
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{
		models[selected]->addScale(glm::vec3(-0.01f, -0.01f, -0.01f));
	}

	// Press 'SPACE' to re-position the model at a random location on the grid
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		float a = -5.0f;
		float b = 5.0f;
		float x = RandomFloat(a, b);
		float z = RandomFloat(a, b);
		models[selected]->Reposition(glm::vec3(x, 0.0f, z));
	}

	// Press 'BACKSPACE' to reset to original position
	if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS)
	{
		if (selected == 0) {
			models[selected]->Reposition(glm::vec3(0.0f, 0.0f, -1.0f));
		}
		else if (selected == 1) {
			models[selected]->Reposition(glm::vec3(3.5f, 0.0f, -4.0f));
		}
		else if (selected == 2) {
			models[selected]->Reposition(glm::vec3(3.5f, 0.0f, 4.0f));
		}
		else if (selected == 3) {
			models[selected]->Reposition(glm::vec3(-4.0f, 0.0f, 4.0f));
		}
		else if (selected == 4) {
			models[selected]->Reposition(glm::vec3(-4.0f, 0.0f, -4.0f));
		}
		else {

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

//Method to generate random float between a & b
float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

